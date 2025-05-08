#ifndef ADDBUS_H
#define ADDBUS_H

#include <QDialog>
#include <QTime>
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddBus;
}

class AddBus : public QDialog
{
    Q_OBJECT

public:
    explicit AddBus(QWidget *parent = nullptr);
    ~AddBus();

    int m_nBusNumber;               //定义班次号，班次号属于公开信息，可以不用private
    QTime m_timeDepartureTime;      //定义发车时间
    QString m_strTerminal;          //终点站
    unsigned m_unSeats;             //设置非负的座位数，需要在构造函数中初始化
    QVector <unsigned> m_arrSeats;  //设置座位数据集
    int m_DateSelection;            //选择的日期

    int m_getBusNumber();           //获取车次号
    QTime m_getDepartureTime();     //获取日期
    QString m_getTerminal();        //获取终点站
    unsigned m_getSeats();          //获取座位数
    int DateSelection();            //判断选择的日期

private slots:
    void on_buttonBox_accepted();   //当添加完车辆信息并确定后

private:
    Ui::AddBus *ui;
};

#endif // ADDBUS_H




// //在Bus类下，通过vector存储Passenger结构体，Passenger结构体中存储数据：姓名、身份证号、座号。
// //上级是Bus类，无下级
// //目录编码1-1-1-1     [X-Y-Z-A-B:类型(数据1/界面2)-一级分支-二级分支-三级分支-四级分支]

// #ifndef PASSENGER_H
// #define PASSENGER_H
// #include<QString>

// //创建Passenger的结构体
// struct Passenger
// {
// public:

//     Passenger();                        //默认构造函数

//     //接口分离，通过函数操作变量，保证封装完整性

//     void m_setName(QString);            //设置名字
//     QString m_getName()const;           //获取名字

//     void m_setID(unsigned long);        //设置身份证
//     unsigned long m_getID()const;       //获取身份证

//     void m_setSeatNumber(int);          //设置座位号
//     int m_getSeatNumber()const;         //获取座位号


// private:
//     QString m_strName;                  //姓名
//     unsigned long m_unsignedlongID;     //身份证号码
//     int m_nSeatNumber;                  //座位号
// };

// #endif // PASSENGER_H
