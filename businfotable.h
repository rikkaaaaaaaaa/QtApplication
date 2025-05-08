//BusInfoTable.h
//创建BusInfoTable类,vector存储Bus类信息，
//无上级，下一级别Bus类
//目录编码1-1     [X-Y-Z-A-B:类型(数据1/界面2)-一级分支-二级分支-三级分支-四级分支]
#ifndef BUSINFOTABLE_H
#define BUSINFOTABLE_H
#include<QVector>
#include"bus.h"
class BusInfoTable
{
public:
    BusInfoTable();                 /*构造函数*/
    void m_AddNewBus(Bus,int);          /*接口函数，导入TempBus信息*/

    //QVector <QVector<Bus>> m_arrBus;
    QVector <Bus> m_arrBusToday;    /*QVector存储今天Bus信息*/
    QVector <Bus> m_arrBusTomorrow; /*QVector存储明天Bus信息*/
    QVector <Bus> m_arrBusDayAfter; /*QVector存储后天Bus信息*/
};

#endif // BUSINFOTABLE_H
