//主窗口，界面+管理数据，最上级，所有数据都要回到mainwindow管理
//目录编号mainwindow     [X-Y-Z-A-B:类型(数据1/界面2)-一级分支-二级分支-三级分支-四级分支]

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include "buyticket.h"
#include "returnticket.h"
#include "deletebus.h"
#include "checkpassenger.h"
#include "savejson.h"
#include "searchinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    BusInfoTable m_BusInfoTable;       //新建BusInfoTable类对象
    BuyTicket m_BuyTicket;             //新建BuyTicket类对象
    void ShowBusInfoTable(int);        //新建显示接口函数

private slots:
    // void on_AddNewBus_clicked();    //槽函数



    // void on_BuyTicket_clicked();

    // void on_Refresh_clicked();

    // void on_ReturnTicket_clicked();

    void on_AddNewBus_triggered();

    void on_DeleteBus_triggered();

    void on_BuyTicket_triggered();

    void on_ReturnTicket_triggered();

    void on_actionOpenFile_triggered();

    void on_Refresh_2_triggered();

    void on_SearchInfo_triggered();

    void on_actionRefresh_triggered();

    void on_actionRefresh_2_triggered();

    void on_actionBuyTicket_triggered();

    void on_actionReturnTicket_triggered();

    void on_actionAddNewBus_triggered();

    void on_actionDeleteBus_triggered();

    void on_actionCheckPassenger_triggered();

    void on_BusList_cellDoubleClicked(int row, int column);

    void on_actionSave_triggered();

    void on_actionSavetxt_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
