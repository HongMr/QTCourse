#include "dialog.h"
#include "./ui_dialog.h"
#include <QFileDialog>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_8_clicked()
{
    QString curDir = QCoreApplication::applicationDirPath();
    QString aFile = QFileDialog::getOpenFileName(this,"打开一个文件",curDir,"所有文件(*.*)");
    ui->editFile->setText(aFile);
}


void Dialog::on_pushButton_9_clicked()
{
    QString curDir = QCoreApplication::applicationDirPath();
    QString aDir = QFileDialog::getExistingDirectory(this,"选择一个目录",curDir);
    ui->editDir->setText(aDir);
}


void Dialog::on_pushButton_10_clicked()
{
    ui->plainTextEdit->clear();
}


void Dialog::on_pushButton_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::applicationDirPath();
    ui->plainTextEdit->appendPlainText(str);
}

void Dialog::showBtnInfo(QObject *btn)
{
    QPushButton *theBtn = static_cast<QPushButton*>(btn);
    ui->plainTextEdit->appendPlainText(theBtn->text());
    ui->plainTextEdit->appendPlainText(theBtn->toolTip()+":\n");
}


void Dialog::on_pushButton_2_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::applicationFilePath();
    ui->plainTextEdit->appendPlainText(str);
}


void Dialog::on_pushButton_3_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::setApplicationName("MyAppTest");
    QString str = QCoreApplication::applicationName();
    ui->plainTextEdit->appendPlainText(str);
}


void Dialog::on_pushButton_4_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::setApplicationName("MyAppTest");
    QString str = QCoreApplication::applicationName();
    ui->plainTextEdit->appendPlainText(str+"\n");
}


void Dialog::on_pushButton_5_clicked()
{
    showBtnInfo(sender());
    QStringList strList = QCoreApplication::libraryPaths();
    for(auto &item:strList)
        ui->plainTextEdit->appendPlainText(item);

    ui->plainTextEdit->appendPlainText("");
}


void Dialog::on_pushButton_6_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::setOrganizationName("AXB");
    QString str = QCoreApplication::organizationName();
    ui->plainTextEdit->appendPlainText(str+"\n");
}


void Dialog::on_pushButton_7_clicked()
{
    QCoreApplication::exit();
}

//静态函数copy
void Dialog::on_pushButton_11_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    QFileInfo fileInfo(sous);
    QString newFile = fileInfo.path()+"/"+fileInfo.baseName()+"--副本."+fileInfo.suffix();
    QFile::copy(sous,newFile);
    ui->plainTextEdit->appendPlainText("源文件:"+sous);
    ui->plainTextEdit->appendPlainText("副本："+newFile+"\n");
}

//成员函数copy
void Dialog::on_pushButton_16_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    QFileInfo fileInfo(sous);
    QString newFile = fileInfo.path()+"/"+fileInfo.baseName()+"--副本."+fileInfo.suffix();
    QFile file(sous);
    file.copy(newFile);
    ui->plainTextEdit->appendPlainText("源文件:"+sous);
    ui->plainTextEdit->appendPlainText("成员函数副本："+newFile+"\n");
}

//静态函数exists
void Dialog::on_pushButton_12_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    bool the = QFile::exists(sous);
    ui->plainTextEdit->appendPlainText("源文件:"+sous);
    if (the)
        ui->plainTextEdit->appendPlainText("存在\n");
    else
        ui->plainTextEdit->appendPlainText("不存在！！！\n");

}

//成员函数 exists
void Dialog::on_pushButton_17_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    QFile file(sous);

    bool the = file.exists();
    ui->plainTextEdit->appendPlainText("成员函数源文件:"+sous);
    if (the)
        ui->plainTextEdit->appendPlainText("存在\n");
    else
        ui->plainTextEdit->appendPlainText("不存在！！！\n");
}

//静态函数 remove
void Dialog::on_pushButton_14_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    if(QFile::exists(sous))
    {
        QFile::remove(sous);
        ui->plainTextEdit->appendPlainText("删除文件：\n"+sous+"\n");
    }
    else
        ui->plainTextEdit->appendPlainText("文件不存在！！！\n");
}

//成员函数 remove
void Dialog::on_pushButton_18_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    QFile file(sous);
    if(file.exists())
    {
        file.remove();
        ui->plainTextEdit->appendPlainText("删除文件：\n"+sous+"\n");
    }
    else
        ui->plainTextEdit->appendPlainText("文件不存在！！！\n");
}


void Dialog::on_pushButton_13_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    QFileInfo fileInfo(sous);
    QString newFile = fileInfo.path()+"/"+fileInfo.baseName()+"--修改的版本."+fileInfo.suffix();
    QFile::rename(sous,newFile);
    ui->plainTextEdit->appendPlainText("源文件:"+sous);
    ui->plainTextEdit->appendPlainText("修改后："+newFile+"\n");
}


void Dialog::on_pushButton_19_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    QFileInfo fileInfo(sous);
    QString newFile = fileInfo.path()+"/"+fileInfo.baseName()+"--修改的版本."+fileInfo.suffix();
    QFile file(sous);


    file.rename(newFile);
    ui->plainTextEdit->appendPlainText("源文件:"+sous);
    ui->plainTextEdit->appendPlainText("修改后："+newFile+"\n");
}


void Dialog::on_pushButton_15_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    if(QFile::exists(sous))
    {
        QFile::moveToTrash(sous);
        ui->plainTextEdit->appendPlainText("删除文件：\n"+sous+"\n");
    }
    else
        ui->plainTextEdit->appendPlainText("文件不存在！！！\n");
}


void Dialog::on_pushButton_20_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    QFile file(sous);
    if(file.exists())
    {
        file.moveToTrash();
        ui->plainTextEdit->appendPlainText("删除文件：\n"+sous+"\n");
    }
    else
        ui->plainTextEdit->appendPlainText("文件不存在！！！\n");
}

