#include "checkpassenger.h"
#include "ui_checkpassenger.h"

CheckPassenger::CheckPassenger(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CheckPassenger)
{
    ui->setupUi(this);
}
void CheckPassenger::ShowPassenger(BusInfoTable t_CheckInfo, int t_nDate ,int i)
{
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"日期","车次号","姓名","身份证号","座位号"});

    // ui->tableWidget.
    int j = 0;
    for( ; j < t_CheckInfo.m_arrBusToday[i].getPassengerArr().size() ; j++)
    {
        ui->tableWidget->insertRow(j);//在表格中第j行插入一行

        QString t_strTempNumber;//定义临时车次号变量
        QString t_strTempDate;//定义临时出发日期变量
        QString t_strTempName;//定义临时离开时间变量
        QString t_strTempID;//定义临时终点站变量
        QString t_strTempSeats;//定义临时座位数变量


        if(t_nDate == 0)
        {
            t_strTempNumber     =  QString::number(t_CheckInfo.m_arrBusToday[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempDate       =  "今天（8月31日）";
            t_strTempName       =  t_CheckInfo.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerName();//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempID         =  t_CheckInfo.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerID();//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempSeats      =  QString::number(t_CheckInfo.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerSeatNumber());//类型转化，用QString类型接收，方便TableWidget接收
        }
        else if(t_nDate == 1)
        {
            t_strTempNumber     =  QString::number(t_CheckInfo.m_arrBusTomorrow[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempDate       =  "明天（9月1日）";
            t_strTempName       =  t_CheckInfo.m_arrBusTomorrow[i].getPassengerArr()[j].m_getPassengerName();//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempID         =  t_CheckInfo.m_arrBusTomorrow[i].getPassengerArr()[j].m_getPassengerID();//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempSeats      =  QString::number(t_CheckInfo.m_arrBusTomorrow[i].getPassengerArr()[j].m_getPassengerSeatNumber());//类型转化，用QString类型接收，方便TableWidget接收

        }
        else if(t_nDate == 2)
        {
            t_strTempNumber     =  QString::number(t_CheckInfo.m_arrBusDayAfter[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempDate       =  "后天（9月2日）";
            t_strTempName       =  t_CheckInfo.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerName();//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempID         =  t_CheckInfo.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerID();//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempSeats      =  QString::number(t_CheckInfo.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerSeatNumber());//类型转化，用QString类型接收，方便TableWidget接收

        }

        ui->tableWidget ->setItem(j,0,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
        ui->tableWidget ->setItem(j,1,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
        ui->tableWidget ->setItem(j,2,new QTableWidgetItem(t_strTempName));//将离开时间填入表格
        ui->tableWidget ->setItem(j,3,new QTableWidgetItem(t_strTempID));//将终点站填入表格
        ui->tableWidget ->setItem(j,4,new QTableWidgetItem(t_strTempSeats));//将座位数填入表格


    }


}

CheckPassenger::~CheckPassenger()
{
    delete ui;
}
