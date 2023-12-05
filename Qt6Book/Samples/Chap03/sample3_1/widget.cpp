#include "widget.h"
#include "tperson.h"
#include "ui_widget.h"
#include <QMetaProperty>

#include <iostream>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    qDebug()<<"aaaaaaaaaa";
    ui->setupUi(this);
    qDebug()<<"11111111111";
    boy = new TPerson("小明",this);
    boy->setProperty("sex","boy");
    boy->setProperty("age",12);
    boy->setProperty("score",86);
    girl = new TPerson("小丽",this);

    girl->setProperty("sex","girl");
    girl->setAge(20);
    ui->spinBoy->setProperty("isBoy",true);
    ui->spinGirl->setProperty("isBoy",false);

    connect(boy,SIGNAL(ageChaged(int)),ui->spinBoy,SLOT(setValue(int)));
    connect(girl,SIGNAL(ageChaged(int)),ui->spinGirl,SLOT(setValue(int)));

    connect(boy,SIGNAL(ageChaged(int)),this,SLOT(do_ageChanged(int)));
    connect(girl,SIGNAL(ageChaged(int)),this,SLOT(do_ageChanged(int)));

    connect(ui->spinBoy,SIGNAL(valueChanged(int)),this,SLOT(do_spinChanged(int)));
    connect(ui->spinGirl,SIGNAL(valueChanged(int)),this,SLOT(do_spinChaged(int)));

    m_drag = false;

    ui->moveLabel->raise();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_ageChanged(int value)
{
    //Q_UNUSED(value);
    TPerson *person = qobject_cast<TPerson *>(sender());
    QString str = QString("%1,%2, 年龄=%3")
                            .arg(person->property("name").toString())
                            .arg(person->property("sex").toString())
                            .arg(value);
    ui->plainTextEdit->appendPlainText(str);
}

void Widget::do_spinChanged(int arg1)
{
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    //spinBoy
    if(spinBox->property("isBoy").toBool())
        boy->setAge(arg1);
    else
        girl->setAge(arg1);
}


void Widget::on_btnBoyInc_clicked()
{
    boy->incAge();
}


void Widget::on_btnGitlInc_clicked()
{
    girl->incAge();
}


void Widget::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}


void Widget::on_btnClassInfo_clicked()
{
    const QMetaObject *meta = boy->metaObject();
    ui->plainTextEdit->appendPlainText(QString("类名称：%1\n").arg(meta->className()));
    ui->plainTextEdit->appendPlainText("属性：");
    for(int i = meta->propertyOffset();i < meta->propertyCount(); i++)
    {
        const char *propName = meta->property(i).name();
        QString propValue = boy->property(propName).toString();
        ui->plainTextEdit->appendPlainText(QString("属性名称=%1,属性值=%2").arg(propName).arg(propValue));
    }
    ui->plainTextEdit->appendPlainText("\n类信息(classInfo):");

#if 0
    for(int i = meta->classInfoOffset();i < meta->classInfoCount();i++)
    {

        QMetaClassInfo classInfo = meta->classInfo();
    }
#endif
}


//鼠标按下时执行的事件处理函数
void Widget::mousePressEvent(QMouseEvent *event)
{
    std::cout<<"subio 1111111"<<std::endl;
    //是否为鼠标左键按下
    if(event->button() == Qt::LeftButton){
         std::cout<<"subio 2222"<<std::endl;
        //获取label所在矩形区域
        //QRect rect = ui->moveLabel->frameRect();
        QRect rect = ui->frame->frameRect();
        //坐标值平移,让rect和鼠标坐标系一致
        rect.translate(ui->frame->pos());
        //判断鼠标点击位置是否在rect范围中
        if(rect.contains(event->pos())==true){
            std::cout<<"subio 3333"<<std::endl;
            m_drag = true;//标记可以执行拖拽操作
            m_pos = ui->moveLabel->pos()-event->pos();//记录lable和鼠标相对位置
            //m_pos = ui->btnMove->pos()-event->pos();//记录lable和鼠标相对位置
        }
    }
}
//鼠标抬起时执行的事件处理函数
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_drag = false;
    }
}

//鼠标移动时执行的事件处理函数
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_drag == true){
        //计算label移动的新位置
        QPoint newPos = m_pos + event->pos();
        //设置label移动范围:不能超出父窗口
        //QSize s1 = size();//获取窗口大小
        QSize s1 = ui->frame->size();//获取frame大小
        QSize s2 = ui->moveLabel->size();//获取label大小
        //x:最小值(0)最大值(窗口宽-label宽)
        if(newPos.x() < 0){
            newPos.setX(0);
        }
        else if(newPos.x() > s1.width()-s2.width()){
            newPos.setX(s1.width()-s2.width());
        }
        //y:最小值(0)最大值(窗口高-label高)
        if(newPos.y() < 0){
            newPos.setY(0);
        }
        else if(newPos.y() > s1.height()-s2.height()){
            newPos.setY(s1.height()-s2.height());
        }

        //移动label到新位置
        ui->moveLabel->move(newPos);
    }
}





