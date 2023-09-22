#include "tmylabel.h"

TMyLabel::TMyLabel(QWidget *parent):QLabel(parent)
{

}
void TMyLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit doubleClicked();
}
