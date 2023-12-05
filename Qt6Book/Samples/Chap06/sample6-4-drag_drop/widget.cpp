#include "widget.h"
#include "./ui_widget.h"
#include <QMimeData>
#include <QFileInfo>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->plainTextEdit->setAcceptDrops(false);
    ui->label->setAcceptDrops(false);

    ui->label->setScaledContents(true);//根据控件大小缩放图片
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    QSize sz = ui->plainTextEdit->size();
    ui->plainTextEdit->move(5,5);
    ui->label->move(5,sz.height()+10);
    ui->plainTextEdit->resize(this->width() - 10,sz.height());
    ui->label->resize(this->width() - 10,this->height()-sz.height()-20);
    event->accept();
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("dragEnterEvent事件，mimeData的format:");
    for(auto &item:event->mimeData()->formats())
        ui->plainTextEdit->appendPlainText(item);

     ui->plainTextEdit->appendPlainText("dragEnterEvent事件，mimeData的 urls:");
    for(auto &item:event->mimeData()->urls())
        ui->plainTextEdit->appendPlainText(item.path());

    if(event->mimeData()->hasUrls())
    {
        QString fileName = event->mimeData()->urls().at(0).fileName();
        QFileInfo fileInfo(fileName);
        QString ex = fileInfo.suffix().toUpper();
        if (ex == "JPG")
            event->acceptProposedAction();//我们接受这个东西进门

        else
            event->ignore();
    }
}

void Widget::dropEvent(QDropEvent *event)
{
    QString fullpath = event->mimeData()->urls().at(0).path();
    fullpath = fullpath.right(fullpath.length()-1);
    QPixmap pixmap(fullpath);
    ui->label->setPixmap(pixmap);
    event->accept();
}
