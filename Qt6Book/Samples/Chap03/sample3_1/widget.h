#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
class TPerson;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    TPerson *boy;
    TPerson *girl;
private slots:
    void do_ageChanged(int value);
    void do_spinChanged(int arg1);
    void on_btnBoyInc_clicked();

    void on_btnGitlInc_clicked();

    void on_btnClear_clicked();

    void on_btnClassInfo_clicked();

private:
    Ui::Widget *ui;


private:
    //鼠标按下时执行的事件处理函数
    void mousePressEvent(QMouseEvent *event);
    //鼠标抬起时执行的事件处理函数
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标移动时执行的事件处理函数
    void mouseMoveEvent(QMouseEvent *event);
private:
    bool m_drag;//标记是否可以拖拽
    QPoint m_pos;//记录鼠标和label的相对位置
};
#endif // WIDGET_H






