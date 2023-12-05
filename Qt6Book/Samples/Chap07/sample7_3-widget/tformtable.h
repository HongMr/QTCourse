#ifndef TFORMTABLE_H
#define TFORMTABLE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "tdialogheaders.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class TFormTable; }
QT_END_NAMESPACE

class TFormTable : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *labCellPos;
    QLabel *labCellText;

    QStandardItemModel *m_model;
    QItemSelectionModel *m_selection;

    TDialogHeaders *dlgHeaders = nullptr;
public:
    TFormTable(QWidget *parent = nullptr);
    ~TFormTable();

private slots:
    void on_actTab_SetSize_triggered();

    void on_actTab_SetHeader_triggered();

    void on_actTab_Locate_triggered();
    void on_setCellText(int row,int column,QString &text);
    void on_tableView_clicked(const QModelIndex &index);
    void do_model_currentChanged(const QModelIndex &current, const QModelIndex &previous);
signals:
    void cellIndexChanged(int rowNo,int colNo);
private:
    Ui::TFormTable *ui;
};
#endif // TFORMTABLE_H
