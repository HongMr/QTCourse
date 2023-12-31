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
    void on_btnInitItems_clicked();

    void on_btnClearItems_clicked();


    void on_chkEditable_clicked(bool checked);

    void on_btnInitCities_clicked();

    void on_combItems_currentTextChanged(const QString &arg1);

    void on_combItems_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
