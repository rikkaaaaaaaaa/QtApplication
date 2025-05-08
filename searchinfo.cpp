#include "searchinfo.h"
#include "ui_searchinfo.h"

SearchInfo::SearchInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchInfo)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(6);        //初始化表格
    ui->tableWidget->setRowCount(1);           //初始化表格
    //ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
}

SearchInfo::~SearchInfo()
{
    delete ui;
}

int SearchInfo::DateSelection()//选择天数判断函数
{
    if(ui->TodayButton->isChecked())//今天按钮被勾选
    {
        SearchDate = 0;//日期赋值为0，今天
    }
    else if(ui->TomorrowButton->isChecked())//明天按钮被勾选
    {
        SearchDate = 1;//日期赋值为1，明天
    }
    else if(ui->DayAfterButton->isChecked())//后天按钮被勾选
    {
        SearchDate = 2;//日期赋值为2，后天
    }
    else
    {
        SearchDate = -1;//日期赋值为-1，报错
    }
    return SearchDate;
}

QString SearchInfo::m_getSearchInfoFromComboBox()
{
    SearchWhat = ui->comboBox->currentText();
}
void SearchInfo::on_pushButton_clicked()
{
    m_getSearchInfoFromComboBox();
    DateSelection();
    SearchInfomation = ui->lineEdit->text();
    if(SearchDate == 0)
    {
        if(SearchWhat == "车次号")
        {
            ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
            int t_tempSearchBusNumber;
            t_tempSearchBusNumber = SearchInfomation.toInt();
            for(int i = 0 ; i < m_SearchInfoTable.m_arrBusToday.size() ; i++)
            {
                if(t_tempSearchBusNumber == m_SearchInfoTable.m_arrBusToday[i].m_nBusNumber)
                {
                    QString t_strTempNumber     =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempDate       =  "今天（8月31日）";
                    QString t_strTempTime       =  m_SearchInfoTable.m_arrBusToday[i].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempTerminal   =  m_SearchInfoTable.m_arrBusToday[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSeats      =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSpareSeats =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_arrSeats.size());
                    ui->tableWidget ->setItem(0,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
                    ui->tableWidget ->setItem(0,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
                    ui->tableWidget ->setItem(0,2,new QTableWidgetItem(t_strTempTime));//将离开时间填入表格
                    ui->tableWidget ->setItem(0,3,new QTableWidgetItem(t_strTempTerminal));//将终点站填入表格
                    ui->tableWidget ->setItem(0,4,new QTableWidgetItem(t_strTempSeats));//将座位数填入表格
                    ui->tableWidget ->setItem(0,5,new QTableWidgetItem(t_strTempSpareSeats));//将空座位数填入表格
                }
            }

        }
        else if(SearchWhat == "终点站")
        {
            ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
            QString t_tempSearchTerminal = SearchInfomation;
            for(int i = 0 ; i < m_SearchInfoTable.m_arrBusToday.size() ; i++)
            {
                if(t_tempSearchTerminal == m_SearchInfoTable.m_arrBusToday[i].m_strTerminal)
                {
                    QString t_strTempNumber     =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempDate       =  "今天（8月31日）";
                    QString t_strTempTime       =  m_SearchInfoTable.m_arrBusToday[i].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempTerminal   =  m_SearchInfoTable.m_arrBusToday[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSeats      =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSpareSeats =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_arrSeats.size());
                    ui->tableWidget ->setItem(0,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
                    ui->tableWidget ->setItem(0,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
                    ui->tableWidget ->setItem(0,2,new QTableWidgetItem(t_strTempTime));//将离开时间填入表格
                    ui->tableWidget ->setItem(0,3,new QTableWidgetItem(t_strTempTerminal));//将终点站填入表格
                    ui->tableWidget ->setItem(0,4,new QTableWidgetItem(t_strTempSeats));//将座位数填入表格
                    ui->tableWidget ->setItem(0,5,new QTableWidgetItem(t_strTempSpareSeats));//将空座位数填入表格
                }
            }
        }
        else if(SearchWhat == "本人车票")
        {
            ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","乘客姓名", "身份证号","座位数号"});  //初始化表格
            QString t_tempSearchID = SearchInfomation;
            for(int i = 0 ; i < m_SearchInfoTable.m_arrBusToday.size() ; i++)
            {
                for(int j = 0 ; j < m_SearchInfoTable.m_arrBusToday[i].getPassengerArr().size() ; j++)
                {
                    if(t_tempSearchID == m_SearchInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerID())
                    {
                        QString t_strTempNumber     =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                        QString t_strTempDate       =  "今天（8月31日）";
                        QString t_strTempName       =  m_SearchInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerName();
                        //QString t_strTempTerminal   =  m_SearchInfoTable.m_arrBusToday[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                        QString t_strTempSeats      =  QString::number(m_SearchInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerSeatNumber());//类型转化，用QString类型接收，方便TableWidget接收
                        //QString t_strTempSpareSeats =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_arrSeats.size());
                        ui->tableWidget ->setItem(0,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
                        ui->tableWidget ->setItem(0,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
                        ui->tableWidget ->setItem(0,2,new QTableWidgetItem(t_strTempName));//将乘客姓名填入表格
                        ui->tableWidget ->setItem(0,3,new QTableWidgetItem(t_tempSearchID));//将身份证号填入表格
                        ui->tableWidget ->setItem(0,4,new QTableWidgetItem(t_strTempSeats));//将座位号填入表格
                        //ui->tableWidget ->setItem(0,5,new QTableWidgetItem(t_strTempSpareSeats));//将空座位数填入表格
                    }
                }

            }

        }
    }
    else if(SearchDate == 1)
    {
        if(SearchWhat == "车次号")
        {
            ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
            int t_tempSearchBusNumber;
            t_tempSearchBusNumber = SearchInfomation.toInt();
            for(int i = 0 ; i < m_SearchInfoTable.m_arrBusTomorrow.size() ; i++)
            {
                if(t_tempSearchBusNumber == m_SearchInfoTable.m_arrBusTomorrow[i].m_nBusNumber)
                {
                    QString t_strTempNumber     =  QString::number(m_SearchInfoTable.m_arrBusTomorrow[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempDate       =  "今天（8月31日）";
                    QString t_strTempTime       =  m_SearchInfoTable.m_arrBusTomorrow[i].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempTerminal   =  m_SearchInfoTable.m_arrBusTomorrow[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSeats      =  QString::number(m_SearchInfoTable.m_arrBusTomorrow[i].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSpareSeats =  QString::number(m_SearchInfoTable.m_arrBusTomorrow[i].m_arrSeats.size());
                    ui->tableWidget ->setItem(0,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
                    ui->tableWidget ->setItem(0,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
                    ui->tableWidget ->setItem(0,2,new QTableWidgetItem(t_strTempTime));//将离开时间填入表格
                    ui->tableWidget ->setItem(0,3,new QTableWidgetItem(t_strTempTerminal));//将终点站填入表格
                    ui->tableWidget ->setItem(0,4,new QTableWidgetItem(t_strTempSeats));//将座位数填入表格
                    ui->tableWidget ->setItem(0,5,new QTableWidgetItem(t_strTempSpareSeats));//将空座位数填入表格
                }
            }

        }
        else if(SearchWhat == "终点站")
        {
            ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
            QString t_tempSearchTerminal = SearchInfomation;
            for(int i = 0 ; i < m_SearchInfoTable.m_arrBusTomorrow.size() ; i++)
            {
                if(t_tempSearchTerminal == m_SearchInfoTable.m_arrBusTomorrow[i].m_strTerminal)
                {
                    QString t_strTempNumber     =  QString::number(m_SearchInfoTable.m_arrBusTomorrow[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempDate       =  "今天（8月31日）";
                    QString t_strTempTime       =  m_SearchInfoTable.m_arrBusTomorrow[i].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempTerminal   =  m_SearchInfoTable.m_arrBusTomorrow[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSeats      =  QString::number(m_SearchInfoTable.m_arrBusTomorrow[i].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSpareSeats =  QString::number(m_SearchInfoTable.m_arrBusTomorrow[i].m_arrSeats.size());
                    ui->tableWidget ->setItem(0,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
                    ui->tableWidget ->setItem(0,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
                    ui->tableWidget ->setItem(0,2,new QTableWidgetItem(t_strTempTime));//将离开时间填入表格
                    ui->tableWidget ->setItem(0,3,new QTableWidgetItem(t_strTempTerminal));//将终点站填入表格
                    ui->tableWidget ->setItem(0,4,new QTableWidgetItem(t_strTempSeats));//将座位数填入表格
                    ui->tableWidget ->setItem(0,5,new QTableWidgetItem(t_strTempSpareSeats));//将空座位数填入表格
                }
            }
        }
        else if(SearchWhat == "本人车票")
        {
            ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","乘客姓名", "身份证号","座位数号"});  //初始化表格
            QString t_tempSearchID = SearchInfomation;
            for(int i = 0 ; i < m_SearchInfoTable.m_arrBusToday.size() ; i++)
            {
                for(int j = 0 ; j < m_SearchInfoTable.m_arrBusToday[i].getPassengerArr().size() ; j++)
                {
                    if(t_tempSearchID == m_SearchInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerID())
                    {
                        QString t_strTempNumber     =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                        QString t_strTempDate       =  "今天（8月31日）";
                        QString t_strTempName       =  m_SearchInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerName();
                        //QString t_strTempTerminal   =  m_SearchInfoTable.m_arrBusToday[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                        QString t_strTempSeats      =  QString::number(m_SearchInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerSeatNumber());//类型转化，用QString类型接收，方便TableWidget接收
                        //QString t_strTempSpareSeats =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_arrSeats.size());
                        ui->tableWidget ->setItem(0,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
                        ui->tableWidget ->setItem(0,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
                        ui->tableWidget ->setItem(0,2,new QTableWidgetItem(t_strTempName));//将乘客姓名填入表格
                        ui->tableWidget ->setItem(0,3,new QTableWidgetItem(t_tempSearchID));//将身份证号填入表格
                        ui->tableWidget ->setItem(0,4,new QTableWidgetItem(t_strTempSeats));//将座位号填入表格
                        //ui->tableWidget ->setItem(0,5,new QTableWidgetItem(t_strTempSpareSeats));//将空座位数填入表格
                    }
                }

            }

        }
    }
    else if(SearchDate == 2)
    {
        if(SearchWhat == "车次号")
        {
            ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
            int t_tempSearchBusNumber;
            t_tempSearchBusNumber = SearchInfomation.toInt();
            for(int i = 0 ; i < m_SearchInfoTable.m_arrBusDayAfter.size() ; i++)
            {
                if(t_tempSearchBusNumber == m_SearchInfoTable.m_arrBusDayAfter[i].m_nBusNumber)
                {
                    QString t_strTempNumber     =  QString::number(m_SearchInfoTable.m_arrBusDayAfter[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempDate       =  "今天（8月31日）";
                    QString t_strTempTime       =  m_SearchInfoTable.m_arrBusDayAfter[i].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempTerminal   =  m_SearchInfoTable.m_arrBusDayAfter[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSeats      =  QString::number(m_SearchInfoTable.m_arrBusDayAfter[i].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSpareSeats =  QString::number(m_SearchInfoTable.m_arrBusDayAfter[i].m_arrSeats.size());
                    ui->tableWidget ->setItem(0,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
                    ui->tableWidget ->setItem(0,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
                    ui->tableWidget ->setItem(0,2,new QTableWidgetItem(t_strTempTime));//将离开时间填入表格
                    ui->tableWidget ->setItem(0,3,new QTableWidgetItem(t_strTempTerminal));//将终点站填入表格
                    ui->tableWidget ->setItem(0,4,new QTableWidgetItem(t_strTempSeats));//将座位数填入表格
                    ui->tableWidget ->setItem(0,5,new QTableWidgetItem(t_strTempSpareSeats));//将空座位数填入表格
                }
            }

        }
        else if(SearchWhat == "终点站")
        {
            ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
            QString t_tempSearchTerminal = SearchInfomation;
            for(int i = 0 ; i < m_SearchInfoTable.m_arrBusDayAfter.size() ; i++)
            {
                if(t_tempSearchTerminal == m_SearchInfoTable.m_arrBusDayAfter[i].m_strTerminal)
                {
                    QString t_strTempNumber     =  QString::number(m_SearchInfoTable.m_arrBusDayAfter[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempDate       =  "明天（9月1日）";
                    QString t_strTempTime       =  m_SearchInfoTable.m_arrBusDayAfter[i].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempTerminal   =  m_SearchInfoTable.m_arrBusDayAfter[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSeats      =  QString::number(m_SearchInfoTable.m_arrBusDayAfter[i].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
                    QString t_strTempSpareSeats =  QString::number(m_SearchInfoTable.m_arrBusDayAfter[i].m_arrSeats.size());
                    ui->tableWidget ->setItem(0,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
                    ui->tableWidget ->setItem(0,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
                    ui->tableWidget ->setItem(0,2,new QTableWidgetItem(t_strTempTime));//将离开时间填入表格
                    ui->tableWidget ->setItem(0,3,new QTableWidgetItem(t_strTempTerminal));//将终点站填入表格
                    ui->tableWidget ->setItem(0,4,new QTableWidgetItem(t_strTempSeats));//将座位数填入表格
                    ui->tableWidget ->setItem(0,5,new QTableWidgetItem(t_strTempSpareSeats));//将空座位数填入表格
                }
            }
        }
        else if(SearchWhat == "本人车票")
        {
            ui->tableWidget->setHorizontalHeaderLabels({"班次号", "发车日期","乘客姓名", "身份证号","座位数号"});  //初始化表格
            QString t_tempSearchID = SearchInfomation;
            for(int i = 0 ; i < m_SearchInfoTable.m_arrBusDayAfter.size() ; i++)
            {
                for(int j = 0 ; j < m_SearchInfoTable.m_arrBusDayAfter[i].getPassengerArr().size() ; j++)
                {
                    if(t_tempSearchID == m_SearchInfoTable.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerID())
                    {
                        QString t_strTempNumber     =  QString::number(m_SearchInfoTable.m_arrBusDayAfter[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                        QString t_strTempDate       =  "后天（9月2日）";
                        QString t_strTempName       =  m_SearchInfoTable.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerName();
                        //QString t_strTempTerminal   =  m_SearchInfoTable.m_arrBusToday[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                        QString t_strTempSeats      =  QString::number(m_SearchInfoTable.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerSeatNumber());//类型转化，用QString类型接收，方便TableWidget接收
                        //QString t_strTempSpareSeats =  QString::number(m_SearchInfoTable.m_arrBusToday[i].m_arrSeats.size());
                        ui->tableWidget ->setItem(0,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
                        ui->tableWidget ->setItem(0,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
                        ui->tableWidget ->setItem(0,2,new QTableWidgetItem(t_strTempName));//将乘客姓名填入表格
                        ui->tableWidget ->setItem(0,3,new QTableWidgetItem(t_tempSearchID));//将身份证号填入表格
                        ui->tableWidget ->setItem(0,4,new QTableWidgetItem(t_strTempSeats));//将座位号填入表格
                        //ui->tableWidget ->setItem(0,5,new QTableWidgetItem(t_strTempSpareSeats));//将空座位数填入表格
                    }
                }

            }

        }
    }
}

