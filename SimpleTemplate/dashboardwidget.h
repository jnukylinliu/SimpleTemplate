#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include <QColor>

class DashboardWidget : public QWidget {
    Q_OBJECT
    Q_PROPERTY(double minValue READ minValue WRITE setMinValue DESIGNABLE true)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue DESIGNABLE true)
    Q_PROPERTY(double value READ value WRITE setValue DESIGNABLE true)
    Q_PROPERTY(QString unit READ unit WRITE setUnit DESIGNABLE true)
    Q_PROPERTY(QColor dialColor READ dialColor WRITE setDialColor DESIGNABLE true)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor DESIGNABLE true)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor DESIGNABLE true)

public:
    explicit DashboardWidget(QWidget *parent = nullptr);

    // Getter / Setter
    double minValue() const { return m_minValue; }
    double maxValue() const { return m_maxValue; }
    double value() const { return m_value; }
    QString unit() const { return m_unit; }
    QColor dialColor() const { return m_dialColor; }
    QColor pointerColor() const { return m_pointerColor; }
    QColor textColor() const { return m_textColor; }

public slots:
    void setMinValue(double v);
    void setMaxValue(double v);
    void setValue(double v);
    void setUnit(const QString &u);
    void setDialColor(const QColor &c);
    void setPointerColor(const QColor &c);
    void setTextColor(const QColor &c);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    double m_minValue;
    double m_maxValue;
    double m_value;
    QString m_unit;
    QColor m_dialColor;
    QColor m_pointerColor;
    QColor m_textColor;
};

#endif // DASHBOARDWIDGET_H
