#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    enum FieldColNum{colName = 0,colSex,colBirth,colNation,colScore,colPartyM};
    enum CellType{ctName=1000,ctSex,ctBirth,ctNation,ctPartyM,ctScore};
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSetHeader_clicked();

    void on_btnSetRow_clicked();

    void on_btnInitData_clicked();

    void on_btnInsertRow_clicked();

    void on_btnAddRow_clicked();

private:
    Ui::MainWindow *ui;
private:
    void createItemsARow(int rowNo,QString name,QString sex,QDate birth,QString nation,bool isPM,int score);
};
#endif // MAINWINDOW_H
