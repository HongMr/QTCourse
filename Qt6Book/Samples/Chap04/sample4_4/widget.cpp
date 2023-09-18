#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置单价的小数点1位
    ui->dSpinPrice->setDecimals(1);

    this->connect(ui->spinNum,&QSpinBox::valueChanged,
                  this,&Widget::on_btnCal_clicked);

    this->connect(ui->dSpinPrice,&QDoubleSpinBox::valueChanged,
            this,&Widget::on_btnCal_clicked);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnCal_clicked()
{
    int num = ui->spinNum->value();

    float price = ui->dSpinPrice->value();
    float total = num*price;

    ui->dSpinTotal->setValue(total);
}


void Widget::on_spinDec_valueChanged(int arg1)
{
    ui->spinBin->setValue(arg1);
    ui->spinHex->setValue(arg1);
}


void Widget::on_spinBin_valueChanged(int arg1)
{
    ui->spinDec->setValue(arg1);
    ui->spinHex->setValue(arg1);
}


void Widget::on_spinHex_valueChanged(int arg1)
{
    ui->spinDec->setValue(arg1);
    ui->spinBin->setValue(arg1);
}

