#pragma once
#include <QObject>
#include <QtCharts>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDateTime>

QT_CHARTS_USE_NAMESPACE

    class CryptoVolumeChart : public QObject
{
    Q_OBJECT
public:
    explicit CryptoVolumeChart(QWidget *container, const QString &symbol, QObject *parent = nullptr);

private slots:
    void fetchData();
    void onReplyFinished(QNetworkReply *reply);

private:
    QWidget *container;
    QString symbol;

    QChart *chart;
    QBarSeries *series;
    QBarSet *barSet;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QVector<QPair<qreal, double>> dataPoints; // 时间戳和成交量
    qint64 startTime;

    QTimer timer;
    QNetworkAccessManager manager;
};
