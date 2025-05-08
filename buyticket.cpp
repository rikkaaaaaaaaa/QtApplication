
#include "buyticket.h"
#include "ui_buyticket.h"

BuyTicket::BuyTicket(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BuyTicket)
{
    ui->setupUi(this);
}

BuyTicket::~BuyTicket()
{
    delete ui;
}




QString BuyTicket::m_getPassengerName()const//获取名字
{
    return m_strPassengerName;
}



QString BuyTicket::m_getPassengerID()const//获取身份证
{
    return m_strPassengerID;
}



void BuyTicket::m_setPassengerSeatNumber(int t_tempnSeatNumber)//设置座位号，传入一个临时的int类型变量作为形参
{
    m_nPassengerSeatNumber = t_tempnSeatNumber;//将输入的座位号传入
}
int BuyTicket::m_getPassengerSeatNumber()const//获取座位号
{
    return m_nPassengerSeatNumber;//获取座位号
}


void BuyTicket::m_setPassengerBusNumber(int t_tempBusNumber)//设置车次号，传入一个临时的int类型变量作为形参
{
    m_nPassengerBusNumber = t_tempBusNumber;//将输入的车次号传入
}
int BuyTicket::m_getPassengerBusNumber()const//获取车次号
{
    return m_nPassengerBusNumber;//获取车次号
}


void BuyTicket::m_setPassengerDate(int t_tempDate)//设置日期，传入一个临时的int类型变量作为形参
{
    m_nPassengerDate = t_tempDate;//将输入的日期传入
}
int BuyTicket::m_getPassengerDate()const//获取日期
{
    return m_nPassengerDate;//获取日期
}

int BuyTicket::m_getBusNumberFromWidget()//获取车次号函数
{
    QString t_Number  = ui->BusChoice->currentText();//将ComboBox选中的内容转化为文本并用一个临时变量承接
    int t_TransNumber = t_Number.toInt();//转换文本为Int格式
    return t_TransNumber;//返回转化后的值
}

int BuyTicket::m_getSeatNumberFromWidget()//获取车次号函数
{
    QString t_Number  = ui->SeatChoice->currentText();//将ComboBox选中的内容转化为文本并用一个临时变量承接
    int t_TransNumber = t_Number.toInt();//转换文本为Int格式
    return t_TransNumber;//返回转化后的值
}

QString BuyTicket::m_getNameFromWidget()//获取姓名函数
{
    QString t_String  = ui->NameEdit->text();//将NameEdit的内容转化为文本并用一个临时变量承接

    return t_String;//返回值
}

QString BuyTicket::m_getIDFromWidget()//获取身份证函数
{
    QString t_String  = ui->IDEdit->text();//将IDEdit的内容转化为文本并用一个临时变量承接

    return t_String;//返回值
}


int BuyTicket::DateSelection()//选择天数判断函数
{
    if(ui->TodayButton->isChecked())//今天按钮被勾选
    {
        m_nPassengerDate = 0;//日期赋值为0，今天
    }
    else if(ui->TomorrowButton->isChecked())//明天按钮被勾选
    {
        m_nPassengerDate = 1;//日期赋值为1，明天
    }
    else if(ui->DayAfterButton->isChecked())//后天按钮被勾选
    {
        m_nPassengerDate = 2;//日期赋值为2，后天
    }
    else
    {
        m_nPassengerDate = -1;//日期赋值为-1，报错
    }
    return m_nPassengerDate;
}

void BuyTicket::m_importBusNumberToComboBox(BusInfoTable t_tempBusInfoTable)//向下拉框中引入数据
{
    ui->BusChoice->clear();//清空下拉框中数据
    // if(m_getPassengerDate() == 0)//如果日期为今天
    // {
        QVector <Bus> t_Busarr_0 = t_tempBusInfoTable.m_arrBusToday;//创建一个临时的Bus类数组引入Bus类数据
        for(int i = 0;i < t_Busarr_0.size() ; i++ )//循环赋值
        {
            QString t_tempBusNumber = QString::number(t_Busarr_0[i].m_nBusNumber);//转化为String类型方便addItem接收
            m_TodayTicketBusNumber.push_back(t_tempBusNumber);//用数组接收相关车次号信息
            ui->BusChoice->addItem(t_tempBusNumber);//向下拉框中导入数据
            // for(int j = 0; j < t_Busarr[i].m_arrSeats.size();j++)//循环赋值，将Bus中Seat数据集导出来
            // {
            //     QString t_tempBusSeat = QString::number(t_Busarr[i].m_arrSeats[j]);//创建临时变量转化座位号为QString
            //     ui->SeatChoice->addItem(t_tempBusSeat);//导入下拉框
            // }

        }

    // }

    // if(m_getPassengerDate() == 1)//如果日期为明天
    // {
        QVector <Bus> t_Busarr_1 = t_tempBusInfoTable.m_arrBusTomorrow;//创建一个临时的Bus类数组引入Bus类数据
        for(int i = 0;i < t_Busarr_1.size() ; i++ )//循环赋值
        {
            QString t_tempBusNumber = QString::number(t_Busarr_1[i].m_nBusNumber);//转化为String类型方便addItem接收
            m_TomorrowTicketBusNumber.push_back(t_tempBusNumber);//用数组接收相关车次号信息
            ui->BusChoice->addItem(t_tempBusNumber);//向下拉框中导入数据
            // for(int j = 0; j < t_Busarr_1[i].m_arrSeats.size();j++)//循环赋值，将Bus中Seat数据集导出来
            // {
            //     QString t_tempBusSeat = QString::number(t_Busarr_1[i].m_arrSeats[j]);//创建临时变量转化座位号为QString
            //     ui->SeatChoice->addItem(t_tempBusSeat);//导入下拉框
            // }

        }

    // }

    // if(m_getPassengerDate() == 2)//如果日期为后天
    // {
        QVector <Bus> t_Busarr_2 = t_tempBusInfoTable.m_arrBusDayAfter;//创建一个临时的Bus类数组引入Bus类数据
        for(int i = 0;i < t_Busarr_2.size() ; i++ )//循环赋值
        {
            QString t_tempBusNumber = QString::number(t_Busarr_2[i].m_nBusNumber);//转化为String类型方便addItem接收
            m_DayAfterTicketBusNumber.push_back(t_tempBusNumber);//用数组接收相关车次号信息
            ui->BusChoice->addItem(t_tempBusNumber);//向下拉框中导入数据
            // for(int j = 0; j < t_Busarr[i].m_arrSeats.size();j++)//循环赋值，将Bus中Seat数据集导出来
            // {
            //     QString t_tempBusSeat = QString::number(t_Busarr[i].m_arrSeats[j]);//创建临时变量转化座位号为QString
            //     ui->SeatChoice->addItem(t_tempBusSeat);//导入下拉框
            // }

        }

    // }
}

// void BuyTicket::m_importSeatNumberToComboBox()//向下拉框中引入数据
// {
//     ui->BusChoice->clear();//清空下拉框中数据
//     if(m_getPassengerDate() == 0)//如果日期为今天
//     {
//         QVector <Bus> t_Busarr = t_tempBusInfoTable.m_arrBusToday;//创建一个临时的Bus类数组引入Bus类数据
//         for(int i = 0;i < t_Busarr.size() ; i++ )//循环赋值
//         {
//             QString t_tempBusNumber = QString::number(t_Busarr[i].m_nBusNumber);//转化为String类型方便addItem接收
//             ui->BusChoice->addItem(t_tempBusNumber);//向下拉框中导入数据
//         }

//     }

//     if(m_getPassengerDate() == 1)//如果日期为明天
//     {
//         QVector <Bus> t_Busarr = t_tempBusInfoTable.m_arrBusTomorrow;//创建一个临时的Bus类数组引入Bus类数据
//         for(int i = 0;i < t_Busarr.size() ; i++ )//循环赋值
//         {
//             QString t_tempBusNumber = QString::number(t_Busarr[i].m_nBusNumber);
//             ui->BusChoice->addItem(t_tempBusNumber);//向下拉框中导入数据
//         }

//     }

//     if(m_getPassengerDate() == 2)//如果日期为后天
//     {
//         QVector <Bus> t_Busarr = t_tempBusInfoTable.m_arrBusDayAfter;//创建一个临时的Bus类数组引入Bus类数据
//         for(int i = 0;i < t_Busarr.size() ; i++ )//循环赋值
//         {
//             QString t_tempBusNumber = QString::number(t_Busarr[i].m_nBusNumber);//转化为String类型方便addItem接收
//             ui->BusChoice->addItem(t_tempBusNumber);//向下拉框中导入数据
//         }

//     }
// }


void BuyTicket::on_buttonBox_accepted()//当添加完乘客信息并确定后
{
    this->m_nPassengerDate = DateSelection();//通过获取函数将日期导入成员变量
    this->m_strPassengerName = m_getNameFromWidget();//通过获取函数将离开时间导入成员变量
    this->m_strPassengerID = m_getIDFromWidget();//通过获取函数将终点站导入成员变量
    this->m_nPassengerBusNumber = m_getBusNumberFromWidget();//通过获取函数将车次号导入成员变量
    this->m_nPassengerSeatNumber = m_getSeatNumberFromWidget();//通过获取函数将座位数导入成员变量
    if(DateSelection() == 0)
    {
        for(int index = 0; index < m_nPassengerSeatNumber; index++)
        {
            if(m_TicketBusInfoTable.m_arrBusToday[m_nBusIndex].m_arrSeats[index] == m_nPassengerSeatNumber)
            {
                m_TicketBusInfoTable.m_arrBusToday[m_nBusIndex].m_arrSeats.remove(index);//在座位数据集中移除已购买的座位
                break;
            }
        }


    }
    else if(DateSelection() == 1)
    {
        for(int index = 0; index < m_nPassengerSeatNumber; index++)
        {
            if(m_TicketBusInfoTable.m_arrBusTomorrow[m_nBusIndex].m_arrSeats[index] == m_nPassengerSeatNumber)
            {
                m_TicketBusInfoTable.m_arrBusTomorrow[m_nBusIndex].m_arrSeats.remove(index);//在座位数据集中移除已购买的座位
                break;
            }
        }
        //m_TicketBusInfoTable.m_arrBusTomorrow[m_nBusIndex].m_arrSeats.remove(m_nPassengerSeatNumber - 1);//在座位数据集中移除已购买的座位
    }
    else if(DateSelection() == 2)
    {
        for(int index = 0; index < m_nPassengerSeatNumber; index++)
        {
            if(m_TicketBusInfoTable.m_arrBusDayAfter[m_nBusIndex].m_arrSeats[index] == m_nPassengerSeatNumber)
            {
                m_TicketBusInfoTable.m_arrBusDayAfter[m_nBusIndex].m_arrSeats.remove(index);//在座位数据集中移除已购买的座位
                break;
            }
        }
        //m_TicketBusInfoTable.m_arrBusDayAfter[m_nBusIndex].m_arrSeats.remove(m_nPassengerSeatNumber - 1);//在座位数据集中移除已购买的座位
    }

}



void BuyTicket::on_TodayButton_clicked()
{
    ui->BusChoice->clear();//清空下拉框中数据

    for(int i = 0;i < m_TodayTicketBusNumber.size() ; i++ )//循环赋值
    {
        ui->BusChoice->addItem(m_TodayTicketBusNumber[i]);//导入车次号数据进入下拉框
    }
    if(m_TodayTicketBusNumber.size() == 0)
    {
        QMessageBox::critical(this, "错误", "还未导入车辆数据，无法购票");
        ui->buttonBox->setEnabled(false);
    }
}


void BuyTicket::on_TomorrowButton_clicked()
{
    ui->BusChoice->clear();//清空下拉框中数据

    for(int i = 0;i < m_TomorrowTicketBusNumber.size() ; i++ )//循环赋值
    {
        ui->BusChoice->addItem(m_TomorrowTicketBusNumber[i]);//导入车次号数据进入下拉框
    }
    if(m_TomorrowTicketBusNumber.size() == 0)
    {
        QMessageBox::critical(this, "错误", "还未导入车辆数据，无法购票");
        ui->buttonBox->setEnabled(false);
    }
}


void BuyTicket::on_DayAfterButton_clicked()
{
    ui->BusChoice->clear();//清空下拉框中数据

    for(int i = 0;i < m_DayAfterTicketBusNumber.size() ; i++ )//循环赋值
    {
        ui->BusChoice->addItem(m_DayAfterTicketBusNumber[i]);//导入车次号数据进入下拉框
    }
    if(m_DayAfterTicketBusNumber.size() == 0)
    {
        QMessageBox::critical(this, "错误", "还未导入车辆数据，无法购票");
        ui->buttonBox->setEnabled(false);
    }
}


// void BuyTicket::on_BusChoice_currentTextChanged(const QString &arg1)
// {
//     ui->SeatChoice->clear();//清空下拉框中数据
//     if(DateSelection() == 0)
//     {
//         int i = ui->BusChoice->currentIndex();
//         for(int j = 0;j < m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.size(); ++j)
//         {
//             QString t_tempSeatNumber = QString::number(m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats[j]);
//             ui->SeatChoice->addItem(t_tempSeatNumber);
//         }
//     }

// }


void BuyTicket::on_BusChoice_activated(int index)//BusChoice改变时，要填充好对应的座位数据集
{
    ui->SeatChoice->clear();//清空下拉框中数据
    if(DateSelection() == 0)
    {
        if(m_TicketBusInfoTable.m_arrBusToday[index].m_arrSeats.size() == 0)
        {
            ui->SeatChoice->setEnabled(false);
            ui->buttonBox->setEnabled(false);
            QMessageBox::critical(this, "错误", "该车票已售罄，请选择其他车辆购买");
        }
        else
        {
            ui->SeatChoice->setEnabled(true);
            for(int j = 0;j < m_TicketBusInfoTable.m_arrBusToday[index].m_arrSeats.size(); ++j)//今天时，填充今天对应Bus的数据
            {
                QString t_tempSeatNumber = QString::number(m_TicketBusInfoTable.m_arrBusToday[index].m_arrSeats[j]);
                ui->SeatChoice->addItem(t_tempSeatNumber);
            }
        }

    }
    else if(DateSelection() == 1)
    {
        if(m_TicketBusInfoTable.m_arrBusTomorrow[index].m_arrSeats.size() == 0)
        {
            ui->SeatChoice->setEnabled(false);
            QMessageBox::critical(this, "错误", "该车票已售罄，请选择其他车辆购买");
        }
        else
        {
            ui->SeatChoice->setEnabled(true);
            for(int j = 0;j < m_TicketBusInfoTable.m_arrBusTomorrow[index].m_arrSeats.size(); ++j)//今天时，填充今天对应Bus的数据
            {
                QString t_tempSeatNumber = QString::number(m_TicketBusInfoTable.m_arrBusTomorrow[index].m_arrSeats[j]);
                ui->SeatChoice->addItem(t_tempSeatNumber);
            }
        }

    }
    else if(DateSelection() == 2)
    {
        if(m_TicketBusInfoTable.m_arrBusDayAfter[index].m_arrSeats.size() == 0)
        {
            ui->SeatChoice->setEnabled(false);
            QMessageBox::critical(this, "错误", "该车票已售罄，请选择其他车辆购买");
        }
        else
        {
            ui->SeatChoice->setEnabled(true);
            for(int j = 0;j < m_TicketBusInfoTable.m_arrBusDayAfter[index].m_arrSeats.size(); ++j)//今天时，填充今天对应Bus的数据
            {
                QString t_tempSeatNumber = QString::number(m_TicketBusInfoTable.m_arrBusDayAfter[index].m_arrSeats[j]);
                ui->SeatChoice->addItem(t_tempSeatNumber);
            }
        }

    }

    m_nBusIndex = index;
}


// void BuyTicket::on_SeatChoice_activated(int index)
// {
//     if(DateSelection() == 0)
//     {
//         m_nPassengerSeatNumber = m_TicketBusInfoTable.m_arrBusToday[m_nBusIndex].m_arrSeats[index];

//     }
//     else if(DateSelection() == 1)
//     {
//         m_nPassengerSeatNumber = m_TicketBusInfoTable.m_arrBusTomorrow[m_nBusIndex].m_arrSeats[index];
//     }
//     else if(DateSelection() == 2)
//     {
//         m_nPassengerSeatNumber = m_TicketBusInfoTable.m_arrBusDayAfter[m_nBusIndex].m_arrSeats[index];
//     }

// }

