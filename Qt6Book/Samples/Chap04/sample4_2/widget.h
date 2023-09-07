#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnFrontBack_clicked();

    void on_btnLeftRight_clicked();

    void on_btnFirstLast_clicked();

    void on_btnSection_clicked();

    void on_btnClear_clicked();

    void on_btnIsNullIsEmpty_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
