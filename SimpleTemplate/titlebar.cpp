#include "titlebar.h"
#include "ui_titlebar.h"

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);

    this->setStyleSheet("border-bottom: 1px solid #444444;");
    // 将 UI 中的按钮信号转发为自定义信号

    connect(ui->btnMinimize, &QPushButton::clicked, this, [=]() {
        window()->showMinimized();
    });

    connect(ui->btnMaximize, &QPushButton::clicked, this, [=]() {
        window()->isMaximized() ? window()->showNormal() : window()->showMaximized();
    });

    connect(ui->btnClose, &QPushButton::clicked, this, [=]() {
        window()->close();
    });

}

void TitleBar::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event); // 先绘制默认内容

  //  QPainter painter(this);
  //  painter.setPen(QPen(QColor("#444444"), 1)); // 底部线颜色和宽度
    //painter.drawLine(0, height()-1, width(), height()-1); // 底部一条横线
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        // 记录鼠标在窗口中的位置偏移
        m_dragPosition = event->globalPos() - window()->frameGeometry().topLeft();
        event->accept();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        window()->move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_dragging = false;
}



TitleBar::~TitleBar()
{
    delete ui;
}
