#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QActionGroup>
#include <QSpinBox>
#include <QFontComboBox>
#include <QLabel>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //解决中英文按钮互斥性问题
    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actLang_CN);
    actionGroup->addAction(ui->actLang_EN);
    actionGroup->setExclusive(true);

    //创建一些无法通过UI直接设计的组件
    QSpinBox *spinFontSize = new QSpinBox(this);
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->textEdit->font().pointSize());
    spinFontSize->setMinimumWidth(50);
    ui->toolBar->addWidget(spinFontSize);

    //创建字体按钮
    QFontComboBox *comboFontBox = new QFontComboBox();
    comboFontBox->setMinimumWidth(150);
    comboFontBox->setFont(ui->textEdit->font());
    ui->toolBar->addWidget(comboFontBox);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actClose);

    //状态栏
    labFile = new QLabel(this);
    labFile->setMinimumWidth(150);
    labFile->setText("文件名: ");
    ui->statusbar->addWidget(labFile);

    //添加进度条
    progressbar = new QProgressBar(this);
    progressbar->setMinimum(5);
    progressbar->setMaximum(50);
    progressbar->setValue(ui->textEdit->font().pointSize());

    ui->statusbar->addWidget(progressbar);

    //写在最右边
    labInfo = new QLabel("Permanent");
    ui->statusbar->addPermanentWidget(labInfo);

    connect(spinFontSize,&QSpinBox::valueChanged,this,&MainWindow::on_fontSize_changed);
    connect(comboFontBox,&QFontComboBox::currentFontChanged,this,&MainWindow::on_fontchanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actFile_New_triggered()
{
    ui->textEdit->clear();
    ui->textEdit->document()->setModified(false);
    labFile->setText("文件名：新建一个文件");
}


void MainWindow::on_actFile_Open_triggered()
{
    labFile->setText("正在打开一个文件");
}


void MainWindow::on_actFile_Save_triggered()
{
    ui->textEdit->document()->setModified(false);
    labFile->setText("正在保存文件");
}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actEdit_Copy->setEnabled(b);
    ui->actEdit_Cut->setEnabled(b);
    ui->actEdit_Paste->setEnabled(ui->textEdit->canPaste());
}


void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt =  ui->textEdit->currentCharFormat();
    ui->actFont_Bold->setChecked(fmt.font().bold());
    ui->actFont_Italic->setChecked(fmt.font().italic());
    ui->actFont_UnderLine->setChecked(fmt.font().underline());
}


void MainWindow::on_actFont_Bold_triggered(bool checked)
{
    QTextCharFormat fmt =  ui->textEdit->currentCharFormat();
    if(checked)
    {
        fmt.setFontWeight(QFont::Bold);
    }
    else
        fmt.setFontWeight(QFont::Normal);

    ui->textEdit->setCurrentCharFormat(fmt);
}


void MainWindow::on_actFont_Italic_toggled(bool arg1)
{
    QTextCharFormat fmt =  ui->textEdit->currentCharFormat();
    fmt.setFontItalic(arg1);
    ui->textEdit->setCurrentCharFormat(fmt);
}


void MainWindow::on_actFont_UnderLine_triggered(bool checked)
{
    QTextCharFormat fmt =  ui->textEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->textEdit->setCurrentCharFormat(fmt);
}

void MainWindow::on_fontSize_changed(int fontSize)
{
    QTextCharFormat fmt =  ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(fontSize);
    ui->textEdit->setCurrentCharFormat(fmt);
    progressbar->setValue(fontSize);
}

void MainWindow::on_fontchanged(const QFont &font)
{
    QTextCharFormat fmt =  ui->textEdit->currentCharFormat();
    fmt.setFont(font);
    ui->textEdit->setCurrentCharFormat(fmt);
    labInfo->setText("字体名称： "+font.family());
}

