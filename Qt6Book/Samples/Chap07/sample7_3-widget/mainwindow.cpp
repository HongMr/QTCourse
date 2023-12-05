#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tformdoc.h"
#include <QPainter>

#include "tformtable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //指定tabWidget为主要的Widget，占用MainWindow中的centralwidget
    setCentralWidget(ui->tabWidget);

    //设置看不见
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);

    //设置最大化
    //setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actWidgetInsite_triggered()
{
    TFormDoc *formDoc = new TFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(formDoc,
                          QString::asprintf("Doc %d",ui->tabWidget->count()));

    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);

    connect(formDoc,&TFormDoc::titleChanged,this,&MainWindow::do_changeTabTitle);
}

void MainWindow::do_changeTabTitle(QString str)
{
    int index = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(index,str);
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->widget(index)->close();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,ui->mainToolBar->height(),
                       width(),height()-ui->mainToolBar->height() - ui->statusbar->height(),
                       QPixmap(":/icon/images/R-C.jpg"));

}

void MainWindow::on_actWidget_triggered()
{
    TFormDoc *formDoc = new TFormDoc();
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    formDoc->setWindowTitle("基于QWidget的窗口，无parent");

    formDoc->setWindowOpacity(0.8);//透明度，值越大就不透明;
    formDoc->show();
}

void MainWindow::on_actWindowInsite_triggered()
{
    TFormTable *formTable = new TFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(formTable,
                                    QString::asprintf("Table %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void MainWindow::on_actWindow_triggered()
{
    TFormTable *formTable = new TFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("独立的window");
    formTable->show();
}

