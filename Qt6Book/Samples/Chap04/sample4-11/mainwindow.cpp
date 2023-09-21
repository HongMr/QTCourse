#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMenu>
#include <QListWidgetItem>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tBtnListInit->setDefaultAction(ui->actListInit);
    ui->tBtnListClear->setDefaultAction(ui->actListClear);
    ui->tBtnListInsert->setDefaultAction(ui->actListInsert);
    ui->tBtnListAppend->setDefaultAction(ui->actListAppend);
    ui->tBtnListDelete->setDefaultAction(ui->actListDelete);

    ui->tBtnSelAll->setDefaultAction(ui->actSelAll);
    ui->tBtnSelNone->setDefaultAction(ui->actSelNone);
    ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);

    QMenu *menuSelection = new QMenu(this);
    menuSelection->addAction(ui->actSelAll);
    menuSelection->addAction(ui->actSelNone);
    menuSelection->addAction(ui->actSelInvs);

    ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tBtnSelectItem->setMenu(menuSelection);

    QToolButton *aBtn = new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);
    aBtn->setText("选择选项");
    aBtn->setIcon(QIcon(":/icons/images/list.png"));
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->addWidget(aBtn);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actQuit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actListInit_triggered()
{
    QListWidgetItem *aItem;

    ui->listWidget->clear();

    QIcon aIcon;
    aIcon.addFile(":/icons/images/citiy_1.png");

    bool chk = ui->chkListEditable->isChecked();

    for(int i = 0; i < 10;i++)
    {
        aItem = new QListWidgetItem();
        aItem->setText("Item"+QString::number(i));
        aItem->setIcon(aIcon);
        aItem->setCheckState(Qt::Checked);

        if (chk)
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
        else
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        ui->listWidget->addItem(aItem);
    }
}


void MainWindow::on_actListClear_triggered()
{
     ui->listWidget->clear();
}


void MainWindow::on_actListInsert_triggered()
{
     ui->listWidget->clear();

    // QIcon aIcon;
    // aIcon.addFile(":/icons/images/citiy_1.png");
    QIcon aIcon(":/icons/images/citiy_1.png");
     bool chk = ui->chkListEditable->isChecked();


    QListWidgetItem *aItem = new QListWidgetItem();
    aItem->setText("Item Inserted");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);

    if (chk)
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
    else
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    ui->listWidget->insertItem(ui->listWidget->currentRow(),aItem);

}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if (current != NULL)
    {
        if(previous == NULL)
            str = "当前项:"+current->text();
        else
            str = "前一项:"+previous->text()+"当前项:"+current->text();
    }
    ui->editCutItemText->setText(str);

    ui->plainTextEdit->appendPlainText("currentItemChanged()信号被发射");
}


void MainWindow::on_chkBoxSorting_clicked(bool checked)
{
    ui->listWidget->setSortingEnabled(checked);
}


void MainWindow::on_toolButton_6_clicked()
{
    ui->listWidget->sortItems(Qt::AscendingOrder);
}


void MainWindow::on_toolButton_7_clicked()
{
    ui->listWidget->sortItems(Qt::DescendingOrder);
}


void MainWindow::on_tBtnClearText_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_tBtnAddLine_clicked()
{
    ui->plainTextEdit->appendPlainText("");
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("ui->plainTextEdit:"+item->text());
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);

    QMenu * menuList = new QMenu(this);
    menuList->addAction(ui->actListInit);
    menuList->addAction(ui->actListClear);
    menuList->addAction(ui->actListInsert);
    menuList->addAction(ui->actListAppend);
    menuList->addAction(ui->actListDelete);
    menuList->addSeparator();
    menuList->addAction(ui->actSelAll);
    menuList->addAction(ui->actSelNone);
    menuList->addAction(ui->actSelInvs);

    menuList->exec(QCursor::pos());

    delete menuList;
}

