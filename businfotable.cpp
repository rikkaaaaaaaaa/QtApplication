//BusInfoTable.cpp
//创建BusInfoTable类,vector存储Bus类信息，
//无上级，下一级别Bus类
//目录编码1-1     [X-Y-Z-A-B:类型(数据1/界面2)-一级分支-二级分支-三级分支-四级分支]

#include "businfotable.h"


BusInfoTable::BusInfoTable()/*构造函数*/
{
    // m_arrBus.push_back(m_arrBusToday);
    // m_arrBus.push_back(m_arrBusTomorrow);
    // m_arrBus.push_back(m_arrBusDayAfter);
    // m_arrBus[0] = m_arrBusToday;
    // m_arrBus[1] = m_arrBusTomorrow;
    // m_arrBus[2] = m_arrBusDayAfter;
    // //构造函数中初始化存储三天Bus信息的数组的数组
    //问题：Vector是深拷贝，拷贝的是数据而不是地址，一块内存不能从两处访问
}

void BusInfoTable::m_AddNewBus(Bus t_tempBus, int t_nSelection)/*接口函数导入新巴士*/
{
    if(t_nSelection == 0)//当出发日期为今天时
    {
        m_arrBusToday.push_back(t_tempBus);//在今天的Bus数组里添加一个Bus
    }
    else if(t_nSelection == 1)//当出发日期为明天时
    {
        m_arrBusTomorrow.push_back(t_tempBus);//在明天的Bus数组里添加一个Bus
    }
    else if(t_nSelection == 2)//当出发日期为后天时
    {
        m_arrBusDayAfter.push_back(t_tempBus);//在后天的Bus数组里添加一个Bus
    }
    else
    {
        QMessageBox::critical(0, "错误", "日期选择错误，添加车辆失败！");//意外情况控制
    }
}
