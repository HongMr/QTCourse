#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->slider,&QSlider::valueChanged,this,&Widget::do_valueChanged);
    connect(ui->dial,&QDial::valueChanged,this,&Widget::do_valueChanged);
    connect(ui->scrollBar,&QSlider::valueChanged,this,&Widget::do_valueChanged);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}


void Widget::on_chkBox_Visible_clicked(bool checked)
{
    ui->progressBar->setTextVisible(checked);
}


void Widget::on_chkBox_Inverted_clicked(bool checked)
{
    ui->progressBar->setInvertedAppearance(checked);
}


void Widget::on_radioButton_clicked()
{
    ui->progressBar->setFormat("%p%");
}


void Widget::on_radioButton_2_clicked()
{
    ui->progressBar->setFormat("%v");
}

