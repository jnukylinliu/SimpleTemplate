#pragma once
#include <QObject>
#include <QtCharts>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDateTime>

QT_CHARTS_USE_NAMESPACE

    class CryptoChart : public QObject
{
    Q_OBJECT
public:
    explicit CryptoChart(QWidget *container, const QString &symbol, QObject *parent = nullptr);

private slots:
    void fetchPrice();
    void onReplyFinished(QNetworkReply *reply);

private:
    QWidget *container;
    QString symbol; // 交易对，如 BTCUSDT
    QList<QPointF> dataPoints; // 缓存最近点数
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

    qint64 startTime;

    QTimer timer;
    QNetworkAccessManager manager;
};
