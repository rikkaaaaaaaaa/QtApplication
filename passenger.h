//在Bus类下，通过vector存储Passenger结构体，Passenger结构体中存储数据：姓名、身份证号、座号。
//上级是Bus类，无下级
//目录编码2-1-1-1     [X-Y-Z-A-B:类型(数据1/界面2)-一级分支-二级分支-三级分支-四级分支]



#ifndef PASSENGER_H
#define PASSENGER_H


#include <QDialog>
#include <QString>

class Passenger
{
public:
    Passenger();
    //接口分离，通过函数操作变量，保证封装完整性

    void m_setPassengerName(QString);            //设置名字
    QString m_getPassengerName()const;           //获取名字
    QString m_getNameFromWidget();               //从表格中获取乘客姓名


    void m_setPassengerID(QString);              //设置身份证
    QString m_getPassengerID()const;             //获取身份证
    QString m_getIDFromWidget();                 //从表格中获取乘客身份证

    void m_setPassengerDate(int);                //设置日期
    int m_getPassengerDate()const;               //获取日期


    void m_setPassengerBusNumber(int);           //设置车次号
    int m_getPassengerBusNumber()const;          //获取车次号


    void m_setPassengerSeatNumber(int);          //设置座位号
    int m_getPassengerSeatNumber()const;         //获取座位号

private:
    QString m_strPassengerName;                  //姓名
    QString m_strPassengerID;                    //身份证号码
    int m_nPassengerDate;                        //选择日期
    int m_nPassengerBusNumber;                   //乘客选择车次号
    int m_nPassengerSeatNumber;                  //座位号
};

#endif // PASSENGER_H


