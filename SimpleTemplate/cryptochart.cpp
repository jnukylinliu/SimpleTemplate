#include "cryptochart.h"
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

CryptoChart::CryptoChart(QWidget *container, const QString &symbol, QObject *parent)
    : QObject(parent), container(container), symbol(symbol)
{
    series = new QLineSeries(this);

    chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(symbol);

    axisX = new QValueAxis;
    axisX->setRange(0, 60);
    axisX->setTitleText("Time (s)");

    axisY = new QValueAxis;
    axisY->setRange(0, 100000);
    axisY->setTitleText("Price (USDT)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (!container->layout())
        container->setLayout(new QVBoxLayout);
    container->layout()->addWidget(chartView);

    startTime = QDateTime::currentMSecsSinceEpoch();

    // 定时器轮询
    connect(&timer, &QTimer::timeout, this, &CryptoChart::fetchPrice);
    connect(&manager, &QNetworkAccessManager::finished, this, &CryptoChart::onReplyFinished);
    timer.start(1000); // 每秒请求一次
}

void CryptoChart::fetchPrice()
{
    QString url = QString("https://api.binance.com/api/v3/ticker/price?symbol=%1").arg(symbol);
    manager.get(QNetworkRequest(QUrl(url)));
}

void CryptoChart::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        reply->deleteLater();
        return;
    }

    QJsonObject obj = doc.object();
    double price = obj.value("price").toString().toDouble(); // 价格本身就是 USDT

    qint64 now = QDateTime::currentMSecsSinceEpoch();
    qreal t = (now - startTime) / 1000.0;

    // ---------- 使用成员变量 dataPoints ----------
    dataPoints.append(QPointF(t, price));

    // 保留最近60秒
    while (!dataPoints.isEmpty() && dataPoints.first().x() < t - 60)
        dataPoints.removeFirst();

    series->replace(dataPoints);

    // 横轴显示最近60秒
    axisX->setRange(qMax(0.0, t - 60), t);

    // 纵轴自适应 USDT
    qreal minY = dataPoints.first().y();
    qreal maxY = dataPoints.first().y();
    for (const QPointF &pt : dataPoints) {
        minY = qMin(minY, pt.y());
        maxY = qMax(maxY, pt.y());
    }
    qreal range = maxY - minY;
    if (range < 1e-6) range = minY * 0.01;
    axisY->setRange(minY - range, maxY + range);

    reply->deleteLater();
}
