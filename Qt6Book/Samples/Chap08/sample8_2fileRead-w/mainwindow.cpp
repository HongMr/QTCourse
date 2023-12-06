#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QSaveFile>
#include <QException>
#include <QMessageBox>

QString MainWindow::getFile(bool save)
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString aFileName;
    if (save)
        aFileName = QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    else
        aFileName = QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);


    if (aFileName.isEmpty()) return aFileName;

    QFileInfo fileInfo(aFileName);
    QDir::setCurrent(fileInfo.absoluteFilePath());
    return aFileName;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actOpen_IODevice_triggered()
{
    QString aFileName = getFile(false);

    //用只读方式打开文件
    QFile aFile(aFileName);
    if(!aFile.exists()) return ;

    if(!aFile.open(QIODevice::ReadOnly|QIODevice::Text)) return;

    ui->textEditDevice->appendPlainText(aFile.readAll());
    aFile.close();

}


void MainWindow::on_actSave_IODevice_triggered()
{
    QFile aFile(getFile(true));
    if(!aFile.open(QIODevice::WriteOnly|QIODevice::Text)) return;

    QString str = ui->textEditDevice->toPlainText();
    aFile.write(str.toUtf8(),str.toUtf8().length());
    aFile.close();
}


void MainWindow::on_actSave_TextSafe_triggered()
{
    QSaveFile aFile(getFile(true));
    if(!aFile.open(QIODevice::WriteOnly|QIODevice::Text)) return;

    aFile.setDirectWriteFallback(false);
    try{
        QString str = ui->textEditDevice->toPlainText();
        aFile.write(str.toUtf8(),str.toUtf8().length());
        aFile.commit();
    }catch(QException &e){
        QMessageBox::warning(this,"异常","保存文件过程方式错误");
        aFile.cancelWriting();
    };
}


void MainWindow::on_actOpen_TextStream_triggered()
{
    QString aFileName = getFile(false);

    //用只读方式打开文件
    QFile aFile(aFileName);
    if(!aFile.exists()) return ;

    if(!aFile.open(QIODevice::ReadOnly|QIODevice::Text)) return;

    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);
    while(!aStream.atEnd())
    {
        QString str = aStream.readLine();
        ui->textEditStream->appendPlainText(str);
    }

     aFile.close();
}

#include <QTextBlock>

void MainWindow::on_actSave_TextStream_triggered()
{
     QSaveFile aFile(getFile(true));
     if(!aFile.open(QIODevice::WriteOnly|QIODevice::Text)) return;

     aFile.setDirectWriteFallback(false);
     try{
        QTextStream aStream(&aFile);
        aStream.setAutoDetectUnicode(true);
        QTextDocument *doc = ui->textEditStream->document();
        for(int i = 0; i < doc->blockCount();++i){
            aStream<<doc->findBlockByNumber(i).text();
            aStream<<"\n";
        }


        aFile.commit();
     }catch(QException &e){
        QMessageBox::warning(this,"异常","保存文件过程方式错误");
        aFile.cancelWriting();
     };
}

