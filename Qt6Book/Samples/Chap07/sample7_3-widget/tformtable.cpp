#include "tformtable.h"
#include "./ui_tformtable.h"
#include "tdialogsize.h"

#include "tdialoglocate.h"

TFormTable::TFormTable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TFormTable)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(4,4,this);
    QStringList header;
    header<<"姓名"<<"性别"<<"学位"<<"部门";
    m_model->setHorizontalHeaderLabels(header);


    m_selection = new QItemSelectionModel(m_model);

    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionModel(m_selection);

    setCentralWidget(ui->tableView);

    labCellPos = new QLabel("当前单元格:",this);
    labCellPos->setMinimumWidth(200);

    labCellText = new QLabel("单元格内容：",this);
    labCellText->setMinimumWidth(200);

    ui->statusbar->addWidget(labCellPos);
    ui->statusbar->addWidget(labCellText);

    connect(m_selection,&QItemSelectionModel::currentChanged,this,&TFormTable::do_model_currentChanged);
}

TFormTable::~TFormTable()
{
    delete ui;
}


void TFormTable::on_actTab_SetSize_triggered()
{
    TDialogSize *dlgTableSize = new TDialogSize();
    //设置自定义窗口为固定大小
    dlgTableSize->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    dlgTableSize->setRowColumn(m_model->rowCount(),m_model->columnCount());

    int ret = dlgTableSize->exec();//模态运行自定义窗口
    if (ret == QDialog::Accepted)
    {
        m_model->setColumnCount(dlgTableSize->columnCount());
        m_model->setRowCount(dlgTableSize->rowCount());
    }

    delete dlgTableSize;
}

void TFormTable::on_actTab_SetHeader_triggered()
{
    if (dlgHeaders == nullptr)
        dlgHeaders = new TDialogHeaders(this);

    QStringList strList;
    for(int i = 0; i <m_model->columnCount();++i)
        strList.append(m_model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
    dlgHeaders->setHeaderList(strList);


    int result = dlgHeaders->exec();
    if (result == QDialog::Accepted)
    {
        m_model->setHorizontalHeaderLabels(dlgHeaders->headerList());
    }

}


void TFormTable::on_actTab_Locate_triggered()
{
    TDialogLocate *dlgLocate = new TDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);

    dlgLocate->setWindowFlag(Qt::WindowStaysOnTopHint);

    //初始化对话框
    dlgLocate->setSpinRange(m_model->rowCount(),m_model->columnCount());
    QModelIndex curIndex = m_selection->currentIndex();
    if (curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(),curIndex.column());

    connect(dlgLocate,&TDialogLocate::changeCellText,this,&TFormTable::on_setCellText);

    connect(dlgLocate,&TDialogLocate::changActionEnable,ui->actTab_Locate,&QAction::setEnabled);
    connect(this,&TFormTable::cellIndexChanged,dlgLocate,&TDialogLocate::setSpinValue);
    dlgLocate->show();
    //非模态
    dlgLocate->setModal(false);
}

void TFormTable::on_setCellText(int row, int column, QString &text)
{
    QModelIndex index = m_model->index(row,column);
    m_selection->clearSelection();
    m_selection->setCurrentIndex(index,QItemSelectionModel::Select);
    m_model->setData(index,text,Qt::DisplayRole);
}


void TFormTable::on_tableView_clicked(const QModelIndex &index)
{
    emit cellIndexChanged(index.row(),index.column());
}

void TFormTable::do_model_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (current.isValid())
    {
        labCellPos->setText(QString::asprintf("当前单元格:%d行, %d列",
                                              current.row(),current.column()));

        QStandardItem *aItem = m_model->itemFromIndex(current);
        labCellText->setText("单元格内容："+aItem->text());
    }
}

