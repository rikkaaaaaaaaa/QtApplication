//Bus.cpp
//Bus类中存储班次号、发车时间（QDatetime）、终点城市、座位数量、座位数据集（创建vector存储所有位置编号）
//上级BusInfoTable类，下级Passenger结构体
//目录编码1-1-1      [X-Y-Z-A-B:类型(数据1/界面2)-一级分支-二级分支-三级分支-四级分支]

#include "bus.h"

Bus::Bus()
{

}


void Bus::setBusNumber(int t_tempBusNumber)
{
    m_nBusNumber = t_tempBusNumber;
}
void Bus::setDepartureTime(QTime t_tempTime)
{
    m_timeDepartureTime = t_tempTime;
}
void Bus::setTerminal(QString t_tempCity)
{
    m_strTerminal = t_tempCity;
}
void Bus::setSeats(unsigned t_tempSeats)
{
    m_unSeats = t_tempSeats;
}
void Bus::setSeatsArr(unsigned t_tempSeats)
{
    for(unsigned i = 0;i < t_tempSeats;i++)
    {
        m_arrSeats.push_back(i + 1);
    }
}

void Bus::AddPassenger(Passenger t_tempPassenger)
{
    m_arrPassenger.push_back(t_tempPassenger);
}

QVector<Passenger> Bus::getPassengerArr()
{
    return m_arrPassenger;
}
