#include "passenger.h"

Passenger::Passenger()
{

}




void Passenger::m_setPassengerName(QString t_tempStrName)//设置名字，传入一个临时的string类型变量作为形参
{
    m_strPassengerName = t_tempStrName;//将输入的名字传入
}
QString Passenger::m_getPassengerName()const//获取名字
{
    return m_strPassengerName;
}



void Passenger::m_setPassengerID(QString t_tempID)//设置身份证，传入一个临时的string类型变量作为形参
{
    m_strPassengerID = t_tempID;//将输入的身份证号码传入
}
QString Passenger::m_getPassengerID()const//获取身份证
{
    return m_strPassengerID;
}



void Passenger::m_setPassengerSeatNumber(int t_tempnSeatNumber)//设置座位号，传入一个临时的int类型变量作为形参
{
    m_nPassengerSeatNumber = t_tempnSeatNumber;//将输入的座位号传入
}
int Passenger::m_getPassengerSeatNumber()const//获取座位号
{
    return m_nPassengerSeatNumber;//获取座位号
}


void Passenger::m_setPassengerBusNumber(int t_tempBusNumber)//设置车次号，传入一个临时的int类型变量作为形参
{
    m_nPassengerBusNumber = t_tempBusNumber;//将输入的车次号传入
}
int Passenger::m_getPassengerBusNumber()const//获取车次号
{
    return m_nPassengerBusNumber;//获取车次号
}


void Passenger::m_setPassengerDate(int t_tempDate)//设置日期，传入一个临时的int类型变量作为形参
{
    m_nPassengerDate = t_tempDate;//将输入的日期传入
}
int Passenger::m_getPassengerDate()const//获取日期
{
    return m_nPassengerBusNumber;//获取日期
}




