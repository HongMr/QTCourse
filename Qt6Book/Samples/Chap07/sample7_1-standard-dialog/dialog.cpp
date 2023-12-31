#include "dialog.h"
#include "./ui_dialog.h"

#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QProgressDialog>
#include <QInputDialog>

#include <QElapsedTimer>
#include <QMessageBox>

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


void Dialog::on_btnOpen_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();//当前应用的目录
    QString fileName = QFileDialog::getOpenFileName(this,"选择一个文件",curPath,
                                "文本文件(*.txt);;图片(*.jpg *.gif *.png);;所有文件(*.*)");

    if (!fileName.isEmpty())
        ui->plainTextEdit->appendPlainText(fileName);
}


void Dialog::on_btnOpenMulti_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();//当前应用的目录
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"选择多个文件",curPath,
                                "文本文件(*.txt);;图片(*.jpg *.gif *.png);;所有文件(*.*)");

    for(auto fileName:fileNames)
        ui->plainTextEdit->appendPlainText(fileName);

}


void Dialog::on_btnSelDir_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();//当前应用的目录

    QString selectedDir = QFileDialog::getExistingDirectory(this,"选择一个目录");
    if (!selectedDir.isEmpty()){
        ui->plainTextEdit->appendPlainText(selectedDir);
    }
}


void Dialog::on_btnSave_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();//当前应用的目录

    QString fileName = QFileDialog::getSaveFileName(this,"保存文件",curPath,
                                                    "文本文件(*.txt);;图片(*.jpg *.gif *.png);;所有文件(*.*)");

    if (!fileName.isEmpty())
        ui->plainTextEdit->appendPlainText(fileName);
}


void Dialog::on_btnColor_clicked()
{
    QPalette pal = ui->plainTextEdit->palette();
    QColor initColor = pal.color(QPalette::Text);
    QColor color = QColorDialog::getColor(initColor,this,"选择颜色");

    if (color.isValid())
    {
        pal.setColor(QPalette::Text,color);
        ui->plainTextEdit->setPalette(pal);
    }
}


void Dialog::on_btnFont_clicked()
{
    QFont initFont = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok,initFont);
    if (ok)
        ui->plainTextEdit->setFont(font);
}


void Dialog::on_btnProgress_clicked()
{

    QProgressDialog dlgProgress("正在复制文件...","取消",0,200,this);
    dlgProgress.setWindowTitle("复制文件");
    dlgProgress.setWindowModality(Qt::WindowModal);
    connect(&dlgProgress,&QProgressDialog::canceled,[&]{ui->plainTextEdit->appendPlainText("进度已取消");});
    QElapsedTimer msCounter;
    for(int i = 0 ; i < 200; i++)
    {
        dlgProgress.setValue(i);
        dlgProgress.setLabelText(QString::asprintf("正在复制文件，第%d",i));
        msCounter.start();

        while(true)
        {
            if(msCounter.elapsed() > 30)
                break;
        }
        if (dlgProgress.wasCanceled())
            break;
    }


}


void Dialog::on_btnInputString_clicked()
{
    QString dlgTitle = "输入文字对话框";
    QString txtLabel = "请输入文件名";
    QString initInput = "新建文件.txt";
    QLineEdit::EchoMode echoMode = QLineEdit::Normal;

    bool ok = false;

    QString text = QInputDialog::getText(this,dlgTitle,txtLabel,echoMode,initInput,&ok);
    if (ok && !text.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(text);
    }

}


void Dialog::on_btnInputInt_clicked()
{
    QString dlgTitle = "输入整数对话框";
    QString txtLabel = "设置文本框字体大小";
    int defaultValue = ui->plainTextEdit->font().pointSize();
    int minValue = 6;
    int maxValue = 60;
    int stepValue = 1;
    bool ok = false;

    int inputValue = QInputDialog::getInt(this,dlgTitle,txtLabel,defaultValue,minValue,maxValue,stepValue,&ok);
    if (ok)
    {
        QString str = QString("文本框字体大小被设置为：%1").arg(inputValue);

        ui->plainTextEdit->appendPlainText(str);

        QFont font = ui->plainTextEdit->font();
        font.setPointSize(inputValue);
        ui->plainTextEdit->setFont(font);
    }
}


void Dialog::on_btnInputFloat_clicked()
{
    QString dlgTitle = "输入浮点数对话框";
    QString txtLabel = "输入一个浮点数";
    float defaultValue = 3.13;
    float minValue = 0;
    float maxValue = 10000;
    int decimals = 2;//精度

    bool ok = false;
    float inputValue = QInputDialog::getDouble(this,dlgTitle,txtLabel,defaultValue,minValue,maxValue,decimals,&ok);
    if (ok)
    {
        QString str = QString::asprintf("请输入一个浮点数:%.2f",inputValue);
        ui->plainTextEdit->appendPlainText(str);
    }
}


void Dialog::on_btnInputItem_clicked()
{
    QStringList items;
    items<<"优"<<"良"<<"中"<<"差";
    QString dlgTitle = "输入项对话框";
    QString txtLabel = "请选择一个级别";

    int curIndex = 0;
    bool editable = false;
    bool ok = false;

    QString text = QInputDialog::getItem(this,dlgTitle,txtLabel,items,curIndex,editable,&ok);
    if (ok && !text.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(text);
    }
}


void Dialog::on_btnMsgQuestion_clicked()
{
    QString dlgTitle = "Question消息框";
    QString strInfo = "文件已被修改，是否保存?";

    int result = QMessageBox::question(this,dlgTitle,strInfo,QMessageBox::Yes|QMessageBox::No|
                                                       QMessageBox::Cancel|QMessageBox::NoButton);
    if (result == QMessageBox::Yes)
    {
        ui->plainTextEdit->appendPlainText("Question消息框：Yes被选中");
    }
    else if (result == QMessageBox::No)
    {
        ui->plainTextEdit->appendPlainText("Question消息框： No 被选中");
    }
    else if (result == QMessageBox::Cancel)
    {
        ui->plainTextEdit->appendPlainText("Question消息框： Cancel 被选中");
    }
    else if (result == QMessageBox::NoButton)
    {
        ui->plainTextEdit->appendPlainText("Question消息框： 没有按钮被选中");
    }
}


void Dialog::on_btnMsgInformation_clicked()
{
    QString dlgTitle = "Information 消息框";
    QString strInfo = "文件已经打开，请检查";

    QMessageBox::information(this,dlgTitle,strInfo);
}


void Dialog::on_btnMsgWarning_clicked()
{
    QString dlgTitle = "Warning 消息框";
    QString strInfo = "文件已经打开，请检查";

    QMessageBox::warning(this,dlgTitle,strInfo);
}

void Dialog::on_btnMsgCritical_clicked()
{
    QString dlgTitle = "Critical 消息框";
    QString strInfo = "文件已被修改！！";

    QMessageBox::critical(this,dlgTitle,strInfo);
}

void Dialog::on_btnMsgAbout_clicked()
{
    QString dlgTitle = "About 消息框";
    QString strInfo = "XXX 版本1.01";

    QMessageBox::about(this,dlgTitle,strInfo);
}


void Dialog::on_btnMsgAboutQt_clicked()
{
    QString dlgTitle = "AboutQt 消息框";
    QMessageBox::aboutQt(this,dlgTitle);
}

