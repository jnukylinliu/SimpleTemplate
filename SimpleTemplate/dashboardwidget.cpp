#include "DashboardWidget.h"
#include <QPainter>
#include <QtMath>

DashboardWidget::DashboardWidget(QWidget *parent)
    : QWidget(parent),
    m_minValue(0),
    m_maxValue(120),
    m_value(0),
    m_unit("km/h"),
    m_dialColor(QColor(40, 40, 40)),
    m_pointerColor(QColor(255, 80, 80)),
    m_textColor(Qt::white)
{
    setMinimumSize(200, 200);
}

void DashboardWidget::setMinValue(double v) { m_minValue = v; update(); }
void DashboardWidget::setMaxValue(double v) { m_maxValue = v; update(); }
void DashboardWidget::setValue(double v) { m_value = qBound(m_minValue, v, m_maxValue); update(); }
void DashboardWidget::setUnit(const QString &u) { m_unit = u; update(); }
void DashboardWidget::setDialColor(const QColor &c) { m_dialColor = c; update(); }
void DashboardWidget::setPointerColor(const QColor &c) { m_pointerColor = c; update(); }
void DashboardWidget::setTextColor(const QColor &c) { m_textColor = c; update(); }

void DashboardWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    int side = qMin(width(), height());
    p.translate(width() / 2, height() / 2);
    p.scale(side / 200.0, side / 200.0);

    // 背景
    p.setPen(Qt::NoPen);
    p.setBrush(m_dialColor);
    p.drawEllipse(-90, -90, 180, 180);

    // 刻度
    p.setPen(QPen(m_textColor, 2));
    for (int i = 0; i <= 12; ++i) {
        p.save();
        double angle = 210 - i * 20;
        p.rotate(angle);
        p.drawLine(0, -80, 0, -90);
        p.restore();
    }

    // 数字刻度
    p.setPen(m_textColor);
    QFont font = p.font();
    font.setPointSize(8);
    p.setFont(font);
    for (int i = 0; i <= 12; ++i) {
        double value = m_minValue + i * (m_maxValue - m_minValue) / 12.0;
        double angle = 210 - i * 20;
        double rad = qDegreesToRadians(angle);
        double x = 70 * qCos(rad);
        double y = -70 * qSin(rad);
        QRectF rect(x - 10, y - 6, 20, 12);
        p.drawText(rect, Qt::AlignCenter, QString::number((int)value));
    }

    // 指针
    p.save();
    double ratio = (m_value - m_minValue) / (m_maxValue - m_minValue);
    double pointerAngle = 210 - ratio * 240;
    p.rotate(pointerAngle);
    QPolygonF pointer;
    pointer << QPointF(0, -70) << QPointF(-5, 0) << QPointF(5, 0);
    p.setBrush(m_pointerColor);
    p.setPen(Qt::NoPen);
    p.drawPolygon(pointer);
    p.restore();

    // 中心圆
    p.setBrush(Qt::white);
    p.drawEllipse(-5, -5, 10, 10);

    // 单位文本
    font.setPointSize(10);
    p.setFont(font);
    p.setPen(m_textColor);
    p.drawText(QRectF(-40, 30, 80, 20), Qt::AlignCenter, m_unit);
}
