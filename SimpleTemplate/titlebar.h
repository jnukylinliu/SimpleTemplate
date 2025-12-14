#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
    void paintEvent(QPaintEvent *event) override;
    Ui::TitleBar *ui; // 暴露 ui，让 MainWindow 访问按钮

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_dragging = false;      // 是否正在拖动
    QPoint m_dragPosition;        // 鼠标点击时相对于窗口左上角的偏移


signals:
    void minimizeClicked();
    void maximizeClicked();
    void closeClicked();
};

#endif // TITLEBAR_H
