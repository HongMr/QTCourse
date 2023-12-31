#include "widget.h"
#include "./ui_widget.h"
#include <Qpainter>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    grabKeyboard();
}

Widget::~Widget()
{
    delete ui;
}



void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;

    QPoint pt = event->pos();//相对widget的位置
    QPointF relaPt = event->position();
    QPointF winPt = event->scenePosition();
    QPointF globPt = event->globalPos();//相对屏幕的绝对位置

    QString str = QString::asprintf("pos()=(%d,%d)",pt.x(),pt.y());
    str += QString::asprintf("\nposition()=(%.0f,%.0f)",relaPt.x(),relaPt.y());
    str += QString::asprintf("\nscenePosition()=(%.0f,%.0f)",winPt.x(),winPt.y());
    str += QString::asprintf("\nglobalPos()=(%.0f,%.0f)",globPt.x(),globPt.y());

    ui->labelMove->setText(str);
    ui->labelMove->adjustSize();
    ui->labelMove->move(event->pos());
    QWidget::mousePressEvent(event);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    QPoint pt = ui->btnMove->pos();
    if((event->key() == Qt::Key_A) ||(event->key() == Qt::Key_Left))
        ui->btnMove->move(pt.x()-20,pt.y());

    if((event->key() == Qt::Key_D) ||(event->key() == Qt::Key_Right))
        ui->btnMove->move(pt.x()+20,pt.y());

    if((event->key() == Qt::Key_W) ||(event->key() == Qt::Key_Up))
        ui->btnMove->move(pt.x(),pt.y()-20);

    if((event->key() == Qt::Key_S) ||(event->key() == Qt::Key_Down))
        ui->btnMove->move(pt.x(),pt.y()+20);

    QWidget::keyPressEvent(event);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),this->height(),
                       QPixmap(":/pics/pictures/v1.jpg"));
}

void Widget::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton result = QMessageBox::question(
                                            this,"消息框","确定要退出吗?",
                                            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

    if(result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}
