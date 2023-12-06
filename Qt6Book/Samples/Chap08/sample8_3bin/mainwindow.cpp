#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnFile_clicked()
{
    m_filename = QFileDialog::getSaveFileName(this,"选择一个文件",QApplication::applicationDirPath(),
                                              "数据流文件(*.stream)");

    if(!m_filename.isEmpty())
    {
        ui->editFilename->setText(m_filename);
        ui->actSaveAll->setEnabled(true);
        ui->actReadAll->setEnabled(true);

        ui->groupBox_2->setEnabled(true);
    }
}


void MainWindow::on_btnFont_In_clicked()
{
    QFont font = ui->btnFont_In->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok,font,this);
    if(ok)
        ui->btnFont_In->setFont(font);

}


void MainWindow::on_btnColor_In_clicked()
{
    QPalette plet = ui->btnColor_In->palette();
    QColor color = plet.buttonText().color();
    color = QColorDialog::getColor(color);
    if(color.isValid())
    {
        plet.setColor(QPalette::ButtonText,color);
        ui->btnColor_In->setPalette(plet);
    }
}


void MainWindow::on_btnInt8_Write_clicked()
{
    qint8 value = ui->spinBox_int8->value();
    writeByStream(value);
}


void MainWindow::on_btnInt8_Read_clicked()
{
    qint8 value;
    readByStream(value);
    ui->editInt8->setText(QString("%1").arg(value));
}


void MainWindow::on_btnUint8_Write_clicked()
{
    quint8 value = ui->spinBox_uint8->value();
    writeByStream(value);
}


void MainWindow::on_btnUint8_Read_clicked()
{
    quint8 value;
    readByStream(value);
    ui->editUint8->setText(QString("%1").arg(value));
}


void MainWindow::on_btnInt16_Write_clicked()
{
    qint16 value = ui->spinBox_int16->value();
    writeByStream(value);
}


void MainWindow::on_btnInt16_Read_clicked()
{
    qint16 value;
    readByStream(value);
    ui->editInt16->setText(QString("%1").arg(value));
}


void MainWindow::on_btnUint16_Write_clicked()
{
    quint16 value = ui->spinBox_uint16->value();
    writeByStream(value);
}


void MainWindow::on_btnUint16_Read_clicked()
{
    quint16 value;
    readByStream(value);
    ui->editUint16->setText(QString("%1").arg(value));
}


void MainWindow::on_btnInt32_Write_clicked()
{
    qint32 value = ui->spinBox_int32->value();
    writeByStream(value);
}


void MainWindow::on_btnInt32_Read_clicked()
{
    qint32 value;
    readByStream(value);
    ui->editInt32->setText(QString("%1").arg(value));
}


void MainWindow::on_btnInt64_Write_clicked()
{
    qint64 value = ui->spinBox_int64->value();
    writeByStream(value);
}


void MainWindow::on_btnInt64_Read_clicked()
{
    qint64 value;
    readByStream(value);
    ui->editInt64->setText(QString("%1").arg(value));
}


void MainWindow::on_btnBool_Write_clicked()
{
    bool value = ui->chkBox_In->isChecked();
    writeByStream(value);
}

void MainWindow::on_btnBool_Read_clicked()
{
    bool value;
    readByStream(value);
    ui->chkBox_Out->setChecked(value);
}

