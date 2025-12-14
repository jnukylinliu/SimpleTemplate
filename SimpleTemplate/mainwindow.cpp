#include "mainwindow.h"
#include "ui_mainwindow.h"

CryptoChart *btcChart;
CryptoChart *ethChart;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dashboard(nullptr)
{
    ui->setupUi(this);

    // ui->widget_2->setMinValue(0);
    // ui->widget_2->setMaxValue(200);
    // ui->widget_2->setUnit("km/h");
    // ui->widget_2->setDialColor(Qt::gray);
    // ui->widget_2->setPointerColor(Qt::red);
    // ui->widget_2->setTextColor(Qt::white);
    // ui->widget_2->setValue(80);
    MainWindowInit();

    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    ui->titlebar->installEventFilter(this);


    btcChart = new CryptoChart(ui->widget_btc, "BTCUSDT");
    ethChart = new CryptoChart(ui->widget_eth, "ETHUSDT");

    CryptoVolumeChart *btcVol = new CryptoVolumeChart(ui->widget_btc_vol, "BTCUSDT");
    CryptoVolumeChart *ethVol = new CryptoVolumeChart(ui->widget_eth_vol, "ETHUSDT");

}


void MainWindow::MainWindowInit()
{

    // 获取屏幕几何尺寸
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // 计算70%大小
    int w = screenWidth * 0.7;
    int h = screenHeight * 0.7;

    // 设置窗口大小
    resize(w, h);

    // 居中显示
    move((screenWidth - w) / 2, (screenHeight - h) / 2);
}


MainWindow::~MainWindow()
{
    delete ui;
}
