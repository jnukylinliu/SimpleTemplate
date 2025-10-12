#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dashboard(nullptr)
{
    ui->setupUi(this);
    ui->widget_2->setMinValue(0);
    ui->widget_2->setMaxValue(200);
    ui->widget_2->setUnit("km/h");
    ui->widget_2->setDialColor(Qt::gray);
    ui->widget_2->setPointerColor(Qt::red);
    ui->widget_2->setTextColor(Qt::white);
    ui->widget_2->setValue(80);


}

MainWindow::~MainWindow()
{
    delete ui;
}
