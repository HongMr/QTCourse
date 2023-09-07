#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnFrontBack_clicked()
{
    ui->plainTextEdit->appendPlainText("front().back()函数测试");
    QString str1 = ui->comboBoxStr1->currentText();
    ui->plainTextEdit->appendPlainText(str1);

    ui->plainTextEdit->appendPlainText("front ="+QString(str1.front()));
    ui->plainTextEdit->appendPlainText("back ="+QString(str1.back()));
}


void Widget::on_btnLeftRight_clicked()
{
    ui->plainTextEdit->appendPlainText("left().right()函数测试");
    QString str1 = ui->comboBoxStr1->currentText();
    ui->plainTextEdit->appendPlainText(str1);

    ui->plainTextEdit->appendPlainText("left ="+QString(str1.left(2)));
    ui->plainTextEdit->appendPlainText("right ="+QString(str1.right(9)));
}


void Widget::on_btnFirstLast_clicked()
{
    ui->plainTextEdit->appendPlainText("first().last()函数测试");
    QString str1 = ui->comboBoxStr1->currentText();
    QString str2 = ui->comboBoxStr2->currentText();
    ui->plainTextEdit->appendPlainText("str1:"+str1);
    ui->plainTextEdit->appendPlainText("str2:"+str2);

    int N = str1.lastIndexOf(str2);
    QString strFirst = str1.first(N+1);
    QString strLast = str1.last(str1.size()-N-1);
    ui->plainTextEdit->appendPlainText("first路径名称 ="+strFirst);
    ui->plainTextEdit->appendPlainText("lase文件名称 ="+strLast);
}


void Widget::on_btnSection_clicked()
{
    ui->plainTextEdit->appendPlainText("section函数测试");
    QString str1 = ui->comboBoxStr1->currentText();
    QString str2 = ui->comboBoxStr2->currentText();

    int N = ui->spinBox->value();

    QString strSection = str1.section(str2,N,N);
    ui->plainTextEdit->appendPlainText(strSection);

}


void Widget::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}


void Widget::on_btnIsNullIsEmpty_clicked()
{
    ui->plainTextEdit->appendPlainText("isNUll和isEmpt函数测试");
    QString str1,str2="";

}

