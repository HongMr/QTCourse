#include "tformdoc.h"
#include "ui_tformdoc.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QFontDialog>

TFormDoc::TFormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TFormDoc)
{
    ui->setupUi(this);

    QToolBar *locToolBar = new QToolBar("文档",this);
    locToolBar->addAction(ui->actOpen);
    locToolBar->addAction(ui->actFont);

    locToolBar->addSeparator();//分隔符
    locToolBar->addAction(ui->actCut);
    locToolBar->addAction(ui->actCopy);
    locToolBar->addAction(ui->actPaste);
    locToolBar->addAction(ui->actRedo);
    locToolBar->addAction(ui->actUndo);

    locToolBar->addSeparator();//分隔符
    locToolBar->addAction(ui->actClose);

    //设置风格
    locToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(locToolBar);
    layout->addWidget(ui->plainTextEdit);
    this->setLayout(layout);
}

TFormDoc::~TFormDoc()
{
    delete ui;
}
#include <QFileDialog>
void TFormDoc::on_actOpen_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this,"打开一个文件",curPath,
                                                      "C程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)" );
    if (aFileName.isEmpty())
        return ;

    QFile aFile(aFileName);
    if (aFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        ui->plainTextEdit->clear();
        QTextStream aStream(&aFile);
        while(!aStream.atEnd())
        {
            QString str = aStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
        }
        aFile.close();

        QFileInfo fileInfo(aFileName);
        QString shortName = fileInfo.fileName();
        setWindowTitle(shortName);

        emit titleChanged(shortName);
    }
}


void TFormDoc::on_actFont_triggered()
{
    QFont font = ui->plainTextEdit->font();
    bool ok = false;

    font = QFontDialog::getFont(&ok,font);
    if (ok)
        ui->plainTextEdit->setFont(font);
}

