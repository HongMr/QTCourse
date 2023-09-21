#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>
#include <QDate>

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


void MainWindow::on_btnSetHeader_clicked()
{
    ui->tableWidget->clear();
    QStringList headerText;
    headerText<<"姓名"<<"性别"<<"出生日期"<<"名族"<<"分数"<<"是否党员";
    ui->tableWidget->setColumnCount(headerText.size());

    //ui->tableWidget->setHorizontalHeaderLabels(headerText);
    for(int i = 0;i < ui->tableWidget->columnCount();++i)
    {
        QTableWidgetItem *headerItem = new QTableWidgetItem(headerText.at(i));
        //headerItem->setText(headerText.at(i));
        QFont font = headerItem->font();

        font.setBold(true);
        font.setPointSize(11);
        headerItem->setFont(font);
        headerItem->setForeground(QBrush(Qt::red));
        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
    }
}


void MainWindow::on_btnSetRow_clicked()
{

    ui->tableWidget->setRowCount(ui->spinRowCount->value());
}


void MainWindow::on_btnInitData_clicked()
{
    ui->tableWidget->clearContents();
    QDate birth(2000,2,2);
    for(int i = 0; i < ui->tableWidget->rowCount();++i)
    {
        QString strName = QString("学生%1").arg(i);
        QString strSex = (i%2)?"男生":"女生";
        bool isParty = (i%2)?false:true;
        int score = QRandomGenerator::global()->bounded(60,100);
        createItemsARow(i,strName,strSex,birth,"汉族",isParty,score);

        birth = birth.addDays(20);
    }
}

void MainWindow::createItemsARow(int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score)
{
    uint studID = 202310000;
    //姓名
    QTableWidgetItem *item = new QTableWidgetItem(name,ctName);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    studID += rowNo;
    item->setData(Qt::UserRole,QVariant(studID));
    ui->tableWidget->setItem(rowNo,colName,item);

    //性别
    QIcon icon;
    if(sex == "男生")
        icon.addFile(":/icons/images/man.png");
    else
        icon.addFile(":/icons/images/welman1.png");

    item = new QTableWidgetItem(sex,ctSex);
    item->setIcon(icon);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,colSex,item);

    //出生日期
    item = new QTableWidgetItem(birth.toString("yyyy-MM-dd"),ctBirth);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,colBirth,item);
    //名族
    item = new QTableWidgetItem(nation,ctNation);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,colNation,item);
    //是否党员
    item = new QTableWidgetItem("党员",ctPartyM);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    if(isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);

    item->setBackground(QBrush(Qt::yellow));

    ui->tableWidget->setItem(rowNo,colPartyM,item);
    //分数
    item = new QTableWidgetItem(QString::number(score),ctScore);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,colScore,item);
}


void MainWindow::on_btnInsertRow_clicked()
{
    int curRow = ui->tableWidget->currentRow();
    ui->tableWidget->insertRow(curRow);
    createItemsARow(curRow,"新学生","男生",QDate::fromString("2000-01-01","yyyy-MM-dd"),"汉族",false,89);
}


void MainWindow::on_btnAddRow_clicked()
{
    int curRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(curRow);
    createItemsARow(curRow,"新学生","女生",QDate::fromString("2005-01-01","yyyy-MM-dd"),"汉族",true,89);
}

