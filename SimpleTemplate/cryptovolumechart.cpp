#include "cryptovolumechart.h"
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

CryptoVolumeChart::CryptoVolumeChart(QWidget *container, const QString &symbol, QObject *parent)
    : QObject(parent), container(container), symbol(symbol)
{
    barSet = new QBarSet(symbol);
    series = new QBarSeries();
    series->append(barSet);

    chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(symbol + " Volume");

    axisX = new QValueAxis;
    axisX->setTitleText("Time (s)");
    axisX->setRange(0, 60);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis;
    axisY->setTitleText("Volume");
    axisY->setRange(0, 1); // 初始值，后续自适应
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (!container->layout())
        container->setLayout(new QVBoxLayout);
    container->layout()->addWidget(chartView);

    startTime = QDateTime::currentMSecsSinceEpoch();

    connect(&timer, &QTimer::timeout, this, &CryptoVolumeChart::fetchData);
    connect(&manager, &QNetworkAccessManager::finished, this, &CryptoVolumeChart::onReplyFinished);

    timer.start(1000); // 每秒轮询
}

void CryptoVolumeChart::fetchData()
{
    // Binance Kline 1分钟最新成交量
    QString url = QString("https://api.binance.com/api/v3/ticker/24hr?symbol=%1").arg(symbol);
    manager.get(QNetworkRequest(QUrl(url)));
}

void CryptoVolumeChart::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) { reply->deleteLater(); return; }

    QJsonObject obj = doc.object();
    double volume = obj.value("quoteVolume").toString().toDouble(); // 24h成交量 USDT

    qint64 now = QDateTime::currentMSecsSinceEpoch();
    qreal t = (now - startTime) / 1000.0;

    dataPoints.append({t, volume});

    // 保留最近60秒
    while (!dataPoints.isEmpty() && dataPoints.first().first < t - 60)
        dataPoints.removeFirst();

    // 更新柱状图
    barSet->remove(0, barSet->count());
    for (const auto &pt : dataPoints)
        *barSet << pt.second;

    // 横轴显示最近60秒
    axisX->setRange(qMax(0.0, t - 60), t);

    // 纵轴自适应
    double minY = dataPoints.first().second;
    double maxY = dataPoints.first().second;
    for (const auto &pt : dataPoints) {
        minY = qMin(minY, pt.second);
        maxY = qMax(maxY, pt.second);
    }
    double range = maxY - minY;
    if (range < 1e-6) range = maxY * 0.01;
    axisY->setRange(minY - range, maxY + range);

    reply->deleteLater();
}
