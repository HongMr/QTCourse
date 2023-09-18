#include "widget.h"
#include "ui_widget.h"
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //定时器
    m_timer = new QTimer(this);
    m_counter = new QElapsedTimer();
    m_timer->stop();
    m_timer->setTimerType(Qt::CoarseTimer);
    ui->radioCoarse->setChecked(true);

    connect(m_timer,&QTimer::timeout,this,&Widget::do_timer_timeout);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_timer_timeout()
{
    QApplication::beep();
    QTime curTime = QTime::currentTime();
    ui->lcdHour->display(curTime.hour());
    ui->lcdMin->display(curTime.minute());
    ui->lcdSec->display(curTime.second());

    if(m_timer->isSingleShot())
    {
        int tmMSec = m_counter->elapsed();
        QString str = QString("流逝的时间:%1毫秒").arg(tmMSec);
        ui->labelElapsed->setText(str);

        ui->btnStart->setEnabled(true);
        ui->btnOneShot->setEnabled(true);
        ui->btnStop->setEnabled(false);
    }
}


void Widget::on_btnStart_clicked()
{
    m_timer->setInterval(ui->spinBoxIntv->value());
    if(ui->radioContinue->isChecked())
        m_timer->setSingleShot(false);
    else
        m_timer->setSingleShot(true);

    if(ui->radioPrecise->isChecked())
        m_timer->setTimerType(Qt::PreciseTimer);
    else if (ui->radioCoarse->isChecked())
        m_timer->setTimerType(Qt::CoarseTimer);
    else
        m_timer->setTimerType(Qt::VeryCoarseTimer);

    m_timer->start();
    m_counter->start();

    ui->btnStart->setEnabled(false);
    ui->btnOneShot->setEnabled(false);
    ui->btnStop->setEnabled(true);
}


void Widget::on_btnStop_clicked()
{
    m_timer->stop();
    int tmMsec = m_counter->elapsed();
    int ms = tmMsec%1000;
    int s = tmMsec/1000;
    QString str = QString("流逝的时间:%1秒,%1毫秒").arg(s).arg(ms);
    ui->labelElapsed->setText(str);

    ui->btnStart->setEnabled(true);
    ui->btnOneShot->setEnabled(true);
    ui->btnStop->setEnabled(false);
}


void Widget::on_btnOneShot_clicked()
{

}

