#include "tfloatspindelegate.h"
#include <QDoubleSpinBox>
TFloatSpinDelegate::TFloatSpinDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}
QWidget *TFloatSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(500000);
    return editor;
}

void TFloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = dynamic_cast<QDoubleSpinBox*>(editor);
    int value = index.model()->data(index,Qt::EditRole).toDouble();
    spinBox->setValue(value);
}

void TFloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = dynamic_cast<QDoubleSpinBox*>(editor);
    int value = spinBox->value();
    model->setData(index,value,Qt::EditRole);
}

void TFloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
