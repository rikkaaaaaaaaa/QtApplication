/**************************************************************************************************
    2．创建和管理描述特定班次的座位信息的对象（售票时实现）；
    //在Bus类下，通过vector存储Passenger结构体，Passenger结构体中存储数据：姓名、身份证号、座号。
    3．办理售票，在班次中添加旅客信息(即座位号)，座位号不能重复；
    //创建ManageTicket类，SellTicket函数,创建一个vector，每卖出一张票，
    //pushback一个数，通过遍历vector所有数据与预选座位号比较，相等就报警不存储数据，不相等就存储
    4．办理退票，在班次中删除旅客信息；
    //在ManageTicket类中创建CancelTicket函数，删除2中vector中对应数据，删除3中vector对应数据
***************************************************************************************************/


#ifndef BUYTICKET_H
#define BUYTICKET_H

#include <QDialog>
#include "BusInfoTable.h"
#include "passenger.h"

namespace Ui {
class BuyTicket;
}

class BuyTicket : public QDialog
{
    Q_OBJECT

public:
    explicit BuyTicket(QWidget *parent = nullptr);
    ~BuyTicket();

    QString m_getPassengerName()const;           //获取名字
    QString m_getPassengerID()const;             //获取身份证

    void m_setPassengerBusNumber(int);           //设置车次号
    int m_getPassengerBusNumber()const;          //获取车次号
    void m_importBusNumberToComboBox(BusInfoTable);       //将当天的BusVector中Bus和Bus中Seat数据集导入ComboBox
    int m_getBusNumberFromWidget();              //从表格中获取目标车号

    void m_setPassengerDate(int);                //设置日期
    int m_getPassengerDate()const;               //获取日期

    void m_setPassengerSeatNumber(int);          //设置座位号
    int m_getPassengerSeatNumber()const;         //获取座位号
    //void m_importSeatNumberToComboBox();       //将当天的Bus中Seat数据集导入ComboBox
    int m_getSeatNumberFromWidget();             //从表格中获取座位号

    QString m_getNameFromWidget();               //从表格中获取乘客姓名
    QString m_getIDFromWidget();                 //从表格中获取乘客身份证
    int DateSelection();                           //判断选择的日期
    QVector<QString> m_TodayTicketBusNumber;       //今天购票可选车数组
    QVector<QString> m_TomorrowTicketBusNumber;    //明天购票可选车数组
    QVector<QString> m_DayAfterTicketBusNumber;    //后天购票可选车数组

    BusInfoTable m_TicketBusInfoTable;

private slots:
    void on_buttonBox_accepted();
    void on_TodayButton_clicked();
    void on_TomorrowButton_clicked();
    void on_DayAfterButton_clicked();
    void on_BusChoice_activated(int index);
private:
    Ui::BuyTicket *ui;
    // int m_nPassengerBusNumber;                   //乘客选择车次号
    // int m_nPassengerSeatNumber;                  //座位号
    QString m_strPassengerName;                  //姓名
    QString m_strPassengerID;                    //身份证号码
    int m_nPassengerDate;                        //选择日期
    int m_nPassengerBusNumber;                   //乘客选择车次号
    int m_nBusIndex;                             //选择巴士在数组中的下标
    int m_nPassengerSeatNumber;                  //座位号


};

#endif // BUYTICKET_H
