#include "tperson.h"
#include <QDebug>

TPerson::TPerson(QString name,QObject *parent)
    : QObject{parent},m_name{name}
{

}

TPerson::~TPerson()
{
    qDebug()<<"TPerson 类的对象被删除";
}

int TPerson::age()
{
    return m_age;

}

void TPerson::setAge(quint8 ageValue)
{
    if(m_age != ageValue)
    {
        m_age = ageValue;
        qDebug()<<"TPerson setAge"<<"m_age = "<<m_age;
        emit ageChanged(m_age);
    }

}

void TPerson::incAge()
{
    ++m_age;
    qDebug()<<"TPerson incAge"<<"m_age = "<<m_age;
    emit ageChanged(m_age);
}
