//Bus.h
//Bus类中存储班次号、发车时间（QDatetime）、终点城市、座位数量、座位数据集（创建vector存储所有位置编号）
//上级BusInfoTable类，下级Passenger结构体
//目录编码1-1-1      [X-Y-Z-A-B:类型(数据1/界面2)-一级分支-二级分支-三级分支-四级分支]

#ifndef BUS_H
#define BUS_H
#include<QTime>
#include<QString>
#include<QVector>
#include <QDialog>
#include <QMessageBox>
#include"passenger.h"
#include"addbus.h"
class Bus//Bus类定义
{
public:
    Bus();//构造函数

    void setBusNumber(int);         //设置车次号
    void setDepartureTime(QTime);   //设置出发时间
    void setTerminal(QString);      //设置终点站
    void setSeats(unsigned);        //设置座位数
    void setSeatsArr(unsigned);     //设置座位数据集
    void AddPassenger(Passenger);   //添加乘客接口函数
    QVector <Passenger> getPassengerArr();




    int m_nBusNumber;               //定义班次号，班次号属于公开信息，可以不用private
    int m_Date;                     //定义发车日期
    QTime m_timeDepartureTime;      //定义发车时间
    QString m_strTerminal;          //终点站
    unsigned m_unSeats;             //设置非负的座位数
    QVector <unsigned> m_arrSeats;  //设置座位数据集

private:
    QVector <Passenger> m_arrPassenger;//私有数据乘客信息
};

#endif // BUS_H
