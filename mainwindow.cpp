#include "mainwindow.h"

#include "importfile.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("D:/pics/Bus.png"));//设置程序图标
    ui->BusList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->BusList->setColumnCount(6);        //初始化表格
    ui->BusList->setRowCount(20);           //初始化表格
    ui->BusList->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AddNewBus_triggered()
{
    AddBus t_AddNewBus(this);       //新建一个AddBus对话框对象，用于接受界面表格中输入内容
    int ret = t_AddNewBus.exec();   //定义return为弹出窗口的返回值
    if(ret==QDialog::Accepted)      //确定按键被按下，进行保存
    {
        Bus tempBus;                //新建一个Bus类的暂时对象
        tempBus.m_Date = -1;        //新建一个选择变量赋哑元-1（用以选择Vector数列）

        tempBus.m_Date = t_AddNewBus.DateSelection();                       //获取日期，并赋值
        //tempBus.setSeatsArr(t_AddNewBus.m_unSeats);                         //设定座位数据集
        tempBus.m_nBusNumber          =   t_AddNewBus.m_nBusNumber;         //赋值，数据从AddBus中转交给MainWindow,让主窗口处理数据。
        tempBus.m_timeDepartureTime   =   t_AddNewBus.m_timeDepartureTime;  //赋值，数据从AddBus中转交给MainWindow,让主窗口处理数据。
        tempBus.m_strTerminal         =   t_AddNewBus.m_strTerminal;        //赋值，数据从AddBus中转交给MainWindow,让主窗口处理数据。
        tempBus.m_unSeats             =   t_AddNewBus.m_unSeats;            //赋值，数据从AddBus中转交给MainWindow,让主窗口处理数据。

        bool t_bUniqueBusNumber = 0;//bool变量，判断车次号是否唯一
        if(tempBus.m_Date == 0)//日期为今天时
        {
            if(m_BusInfoTable.m_arrBusToday.size() == 0)//如果数组中没有元素，则不会重复
            {
                t_bUniqueBusNumber = 1;//车次号是唯一的
            }
            else
            {
                for(int i = 0;i < m_BusInfoTable.m_arrBusToday.size();i++)//遍历今天车次号，确定不会重复
                {
                    if(tempBus.m_nBusNumber == m_BusInfoTable.m_arrBusToday[i].m_nBusNumber)
                    {
                        t_bUniqueBusNumber = 0;//有重复车牌号，赋值为假
                        break;//重复了，跳出循环
                    }
                    else
                    {
                        t_bUniqueBusNumber = 1;//没有重复的车次号
                    }
                }

            }

        }
        else if(tempBus.m_Date == 1)//日期为明天时
        {
            if(m_BusInfoTable.m_arrBusTomorrow.size() == 0)//如果数组中没有元素，则不会重复
            {
                t_bUniqueBusNumber = 1;//车次号是唯一的
            }
            else
            {
                for(int i = 0;i < m_BusInfoTable.m_arrBusTomorrow.size();i++)//遍历明天车次号，确定不会重复
                {
                    if(tempBus.m_nBusNumber == m_BusInfoTable.m_arrBusTomorrow[i].m_nBusNumber)
                    {
                        t_bUniqueBusNumber = 0;//有重复车牌号，赋值为假
                        break;//重复了，跳出循环
                    }
                    else
                    {
                        t_bUniqueBusNumber = 1;//没有重复的车次号
                    }

                }
            }
        }
        else if(tempBus.m_Date == 2)//日期为后天时
        {
            if(m_BusInfoTable.m_arrBusDayAfter.size() == 0)//如果数组中没有元素，则不会重复
            {
                t_bUniqueBusNumber = 1;//车次号是唯一的
            }
            else
            {
                for(int i = 0;i < m_BusInfoTable.m_arrBusDayAfter.size();i++)//遍历后天车次号，确定不会重复
                {
                    if(tempBus.m_nBusNumber == m_BusInfoTable.m_arrBusDayAfter[i].m_nBusNumber)
                    {
                        t_bUniqueBusNumber = 0;//有重复车牌号，赋值为假
                        break;//重复了，跳出循环
                    }
                    else
                    {
                        t_bUniqueBusNumber = 1;//没有重复的车次号
                    }
                }
            }
        }

        if(tempBus.m_nBusNumber!=0 && tempBus.m_strTerminal != "0" && tempBus.m_unSeats!=0 && tempBus.m_Date != -1 && t_bUniqueBusNumber)
        {
            tempBus.setSeatsArr(tempBus.m_unSeats);                           //生成一个座位号vector数组
            m_BusInfoTable.m_AddNewBus(tempBus,tempBus.m_Date);               //导入新添加的Bus
            ShowBusInfoTable(tempBus.m_Date);                                 //显示所有Bus的表格
            QMessageBox::information(this, "提示", "成功添加新巴士");            //提示信息，添加成功
        }
        else if(tempBus.m_nBusNumber!=0 && tempBus.m_strTerminal != "" && tempBus.m_unSeats==0)
        {
            QMessageBox::StandardButton t_Reply;
            t_Reply = QMessageBox::question(this, "询问", "你确定座位数为0吗？",  QMessageBox::Yes | QMessageBox::No);
            if (t_Reply == QMessageBox::Yes)
            {
                tempBus.setSeatsArr(tempBus.m_unSeats);                         //生成一个座位号vector数组
                m_BusInfoTable.m_AddNewBus(tempBus,tempBus.m_Date);             //导入新添加的Bus
                ShowBusInfoTable(tempBus.m_Date);                               //显示所有Bus的表格
            }
            else
            {
                QMessageBox::critical(this, "错误", "座位数为0，添加车辆失败！");
            }

        }
        else if(tempBus.m_nBusNumber == 0 && tempBus.m_strTerminal != "")
        {
            QMessageBox::critical(this, "错误", "无效的车次号，添加车辆失败！");
        }
        else if(tempBus.m_nBusNumber != 0 && tempBus.m_strTerminal == "")
        {
            QMessageBox::critical(this, "错误", "无效的终点站，添加车辆失败！");
        }
        else if(tempBus.m_nBusNumber == 0 && tempBus.m_strTerminal == "")
        {
            QMessageBox::critical(this, "错误", "无效的车次号&终点站，添加车辆失败！");
        }
        else if(tempBus.m_Date == -1)
        {
            QMessageBox::critical(this, "错误", "无效的日期，添加车辆失败！");
        }
        else if(!t_bUniqueBusNumber)
        {
            QMessageBox::critical(this, "错误", "车次号重复，添加车辆失败！");
        }
    }
}

void MainWindow::ShowBusInfoTable(int t_DateSelection)//显示函数体
{
    int i = t_DateSelection;//数组下标，根据日期访问对应数组
    int TodayBusAmount = m_BusInfoTable.m_arrBusToday.size();//今天Bus的数量，-1为数组中最后一个元素位置
    int TomorrowBusAmount = m_BusInfoTable.m_arrBusTomorrow.size();//明天Bus的数量，-1为数组中最后一个元素位置
    int DayAfterAmount = m_BusInfoTable.m_arrBusDayAfter.size();//后天Bus的数量，-1为数组中最后一个元素位置
    bool t_bCondition = 0;
    bool t_bSituation = 1;

    int j;//引入一个过程变量j，用以控制表格位置
    int k;//引入一个过程变量k，用以控制数组位置
    if(i == 0)
    {
        j = TodayBusAmount - 1;
        k = j;
        if(j >= 0 && k >= 0)
        {
            t_bCondition = 1;
            t_bSituation = 1;
        }
        else
        {
            t_bCondition = 1;
            t_bSituation = 0;
        }

    }
    else if(i == 1)
    {
        j = TodayBusAmount + TomorrowBusAmount ;//插入位置原应为TodayBusAmount ，但是空一行方便观察故 + 1
        k = TomorrowBusAmount - 1;
        if(j >= 0 && k >= 0)
        {
            t_bCondition = 1;
            t_bSituation = 1;
        }
        else
        {
            t_bCondition = 1;
            t_bSituation = 0;
        }
    }
    else if(i == 2)
    {
        j = TodayBusAmount + TomorrowBusAmount + DayAfterAmount + 1;//插入位置原为TodayBusAmount + TomorrowBusAmount + 1，但是空一行方便观察故 + 1
        k = DayAfterAmount - 1;
        if(j >= 0 && k >= 0)
        {
            t_bCondition = 1;
            t_bSituation = 1;
        }
        else
        {
            t_bCondition = 1;
            t_bSituation = 0;
        }
    }
    else
    {
        i = 0;
        j = 0;
        t_bCondition = 0;
        t_bSituation = 1;
    }
    if(t_bCondition && t_bSituation)
    {
        ui->BusList->insertRow(j);//在表格中第j行插入一行

        QString t_strTempNumber;//定义临时车次号变量
        QString t_strTempDate;//定义临时出发日期变量
        QString t_strTempTime;//定义临时离开时间变量
        QString t_strTempTerminal;//定义临时终点站变量
        QString t_strTempSeats;//定义临时座位数变量


        if(i == 0)
        {
            t_strTempNumber     =  QString::number(m_BusInfoTable.m_arrBusToday[k].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempDate       =  "今天（8月31日）";
            t_strTempTime       =  m_BusInfoTable.m_arrBusToday[k].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempTerminal   =  m_BusInfoTable.m_arrBusToday[k].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempSeats      =  QString::number(m_BusInfoTable.m_arrBusToday[k].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
        }
        else if(i == 1)
        {
            t_strTempNumber     =  QString::number(m_BusInfoTable.m_arrBusTomorrow[k].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempDate       =  "明天（9月1日）";
            t_strTempTime       =  m_BusInfoTable.m_arrBusTomorrow[k].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempTerminal   =  m_BusInfoTable.m_arrBusTomorrow[k].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempSeats      =  QString::number(m_BusInfoTable.m_arrBusTomorrow[k].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
        }
        else if(i == 2)
        {
            t_strTempNumber     =  QString::number(m_BusInfoTable.m_arrBusDayAfter[k].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempDate       =  "后天（9月2日）";
            t_strTempTime       =  m_BusInfoTable.m_arrBusDayAfter[k].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempTerminal   =  m_BusInfoTable.m_arrBusDayAfter[k].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
            t_strTempSeats      =  QString::number(m_BusInfoTable.m_arrBusDayAfter[k].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
        }

        ui->BusList ->setItem(j,0,new QTableWidgetItem(t_strTempNumber));//将车次号填入表格
        ui->BusList ->setItem(j,1,new QTableWidgetItem(t_strTempDate));//将出发时间填入表格
        ui->BusList ->setItem(j,2,new QTableWidgetItem(t_strTempTime));//将离开时间填入表格
        ui->BusList ->setItem(j,3,new QTableWidgetItem(t_strTempTerminal));//将终点站填入表格
        ui->BusList ->setItem(j,4,new QTableWidgetItem(t_strTempSeats));//将座位数填入表格
        ui->BusList ->setItem(j,5,new QTableWidgetItem(t_strTempSeats));//将空座位数填入表格
    }
    else if(t_bSituation && !t_bCondition)
    {
        QMessageBox::critical(this, "错误", "添加车辆信息错误！");
    }
    else if(!t_bSituation && t_bCondition)
    {

    }
    else
    {
        QMessageBox::critical(this, "错误", "错误！");
    }
}





void MainWindow::on_BuyTicket_triggered()
{
    BuyTicket t_NewBuyTicket(this);     //新建一个Passenger对话框对象，用于接受界面表格中输入内容
    t_NewBuyTicket.m_TicketBusInfoTable = m_BusInfoTable;
    t_NewBuyTicket.DateSelection();
    t_NewBuyTicket.m_importBusNumberToComboBox(m_BusInfoTable);
    int ret = t_NewBuyTicket.exec();    //定义return为弹出窗口的返回值
    t_NewBuyTicket.DateSelection();

    if(ret==QDialog::Accepted)          //确定按键被按下，进行保存
    {
        Passenger t_tempPassenger;      //创建一个暂时的乘客
        t_tempPassenger.m_setPassengerName("0");//初始化姓名
        t_tempPassenger.m_setPassengerID("0");//初始化身份证
        t_tempPassenger.m_setPassengerBusNumber(-1);//初始化车次号
        t_tempPassenger.m_setPassengerSeatNumber(-1);//初始化座位



        t_tempPassenger.m_setPassengerName(t_NewBuyTicket.m_getPassengerName());//获取填写的姓名
        t_tempPassenger.m_setPassengerID(t_NewBuyTicket.m_getPassengerID());//获取填写的身份证
        t_tempPassenger.m_setPassengerDate(t_NewBuyTicket.m_getPassengerDate());//获取填写的日期
        t_tempPassenger.m_setPassengerBusNumber(t_NewBuyTicket.m_getPassengerBusNumber());//获取填写的车次号
        t_tempPassenger.m_setPassengerSeatNumber(t_NewBuyTicket.m_getPassengerSeatNumber());//获取填写的座位号


        int i = t_NewBuyTicket.m_getPassengerDate();
        int j;//引入一个过程变量j，用以控制表格位置
        int k = 0;//引入一个过程变量k，用以控制数组位置
        int t_emptySeats;//空座位数

        if(i == 0)//购票日期为今天时
        {
            for(int k = 0; k < t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday.size();k++)//获取车次下标k
            {
                if(t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday[k].m_nBusNumber == t_NewBuyTicket.m_getPassengerBusNumber())
                {
                    break;
                }
            }

            j = k;
            t_emptySeats = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday[k].m_arrSeats.size();//获取空座位数
            t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday[k].AddPassenger(t_tempPassenger);//向车辆中添加乘客信息
        }
        else if(i == 1)//购票日期为明天时
        {
            for(int k = 0; k < t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow.size();k++)//获取车次下标k
            {
                if(t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow[k].m_nBusNumber == t_NewBuyTicket.m_getPassengerBusNumber())
                {
                    break;
                }
            }
            j = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday.size() + k + 1 ;

            t_emptySeats = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow[k].m_arrSeats.size();//获取空座位数
            t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow[k].AddPassenger(t_tempPassenger);//向车辆中添加乘客信息
        }
        else if(i == 2)//购票日期为后天时
        {
            for(int k = 0; k < t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusDayAfter.size();k++)//获取车次下标k
            {
                if(t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusDayAfter[k].m_nBusNumber == t_NewBuyTicket.m_getPassengerBusNumber())
                {
                    break;
                }
            }
            j = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday.size() + t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow.size() +
                k + 2;//插入位置原为TodayBusAmount + TomorrowBusAmount + 1，但是空一行方便观察故 + 1

            t_emptySeats = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusDayAfter[k].m_arrSeats.size();//获取空座位数
            t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusDayAfter[k].AddPassenger(t_tempPassenger);//向车辆中添加乘客信息

        }
        else//意外情况控制
        {
            j = -1;//意外情况控制
            t_emptySeats = -1;  //意外情况控制
        }
        QString t_tstrEmptySeats = QString::number(t_emptySeats);         //座位号转化
        ui->BusList ->setItem(j,5,new QTableWidgetItem(t_tstrEmptySeats));//将空座位数填入表格
        m_BusInfoTable = t_NewBuyTicket.m_TicketBusInfoTable;             //数据同步

    }
}



void MainWindow::on_Refresh_2_triggered()
{

    ui->BusList->clear();
    ui->BusList->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
    for(int i = 0; i <= 2; i++)
    {
        ShowBusInfoTable(i);
        ui->BusList->removeRow(20);
    }
    QMessageBox::information(this, "提示", "刷新成功！");
}


void MainWindow::on_ReturnTicket_triggered()
{
    ReturnTicket t_ReturnTicket(this);     //新建一个Passenger对话框对象，用于接受界面表格中输入内容
    t_ReturnTicket.m_TicketBusInfoTable = m_BusInfoTable;
    //t_ReturnTicket.DateSelection();
    t_ReturnTicket.m_importBusNumberToComboBox(m_BusInfoTable);
    int ret = t_ReturnTicket.exec();    //定义return为弹出窗口的返回值
    if(ret==QDialog::Accepted)          //确定按键被按下，进行保存
    {
        if(t_ReturnTicket.DateSelection() == 0)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusToday.size(); i++)
            {
                if(t_ReturnTicket.m_nPassengerBusNumber == m_BusInfoTable.m_arrBusToday[i].m_nBusNumber)
                {
                    //unsigned t =  m_BusInfoTable.m_arrBusToday[i].getPassengerArr().size();
                    for(int j = 0; j < m_BusInfoTable.m_arrBusToday[i].getPassengerArr().size(); j++)
                    {
                        if(t_ReturnTicket.m_strPassengerID == m_BusInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerID())
                        {
                            QMessageBox::StandardButton t_Reply;
                            t_Reply = QMessageBox::question(this, "询问", "尊敬的旅客，你确定要退掉车票吗？",  QMessageBox::Yes | QMessageBox::No);

                            if (t_Reply == QMessageBox::Yes)
                            {
                                unsigned t_tempSeats = t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerSeatNumber();
                                t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].getPassengerArr().remove(j);

                                if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.size() >= 2)
                                {
                                    int k = 0;
                                    for( ; t_tempSeats > t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats[k] &&
                                        t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats[k + 1]; k++)
                                    {
                                        break;

                                    }
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.insert(k,t_tempSeats);
                                }
                                else if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.size() == 1)
                                {
                                    if(t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats[0])
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.insert(0,t_tempSeats);
                                    }
                                    else
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.insert(1,t_tempSeats);
                                    }
                                }
                                else
                                {
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.insert(0,t_tempSeats);
                                }
                                QMessageBox::information(this, "提示", "您已成功退票！");
                            }
                            else
                            {
                                QMessageBox::information(this, "提示", "您已取消退票");
                            }

                        }
                        else
                        {
                            QMessageBox::critical(this, "错误", "未查询到您的身份信息");
                        }
                    }

                }
                else
                {
                    QMessageBox::critical(this, "错误", "错误的车辆信息，请检查日期！");

                }
            }
            m_BusInfoTable = t_ReturnTicket.m_TicketBusInfoTable;
        }
        else if (t_ReturnTicket.DateSelection() == 1)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusTomorrow.size(); i++)
            {
                if(t_ReturnTicket.m_nPassengerBusNumber == m_BusInfoTable.m_arrBusTomorrow[i].m_nBusNumber)
                {
                    //unsigned t =  m_BusInfoTable.m_arrBusTomorrow[i].getPassengerArr().size();
                    for(int j = 0; j < m_BusInfoTable.m_arrBusTomorrow[i].getPassengerArr().size(); j++)
                    {
                        if(t_ReturnTicket.m_strPassengerID == m_BusInfoTable.m_arrBusTomorrow[i].getPassengerArr()[j].m_getPassengerID())
                        {
                            QMessageBox::StandardButton t_Reply;
                            t_Reply = QMessageBox::question(this, "询问", "尊敬的旅客，你确定要退掉车票吗？",  QMessageBox::Yes | QMessageBox::No);

                            if (t_Reply == QMessageBox::Yes)
                            {
                                unsigned t_tempSeats = t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].getPassengerArr()[j].m_getPassengerSeatNumber();
                                t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].getPassengerArr().remove(j);

                                if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.size() >= 2)
                                {
                                    int k = 0;
                                    for( ; t_tempSeats > t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats[k] &&
                                           t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats[k + 1]; k++)
                                    {
                                        break;

                                    }
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.insert(k,t_tempSeats);
                                }
                                else if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.size() == 1)
                                {
                                    if(t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats[0])
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.insert(0,t_tempSeats);
                                    }
                                    else
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.insert(1,t_tempSeats);
                                    }
                                }
                                else
                                {
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.insert(0,t_tempSeats);
                                }
                                QMessageBox::information(this, "提示", "您已成功退票！");
                            }
                            else
                            {
                                QMessageBox::information(this, "提示", "您已取消退票");
                            }

                        }
                        else
                        {
                            QMessageBox::critical(this, "错误", "未查询到您的身份信息");
                        }
                    }

                }
                else
                {
                    QMessageBox::critical(this, "错误", "错误的车辆信息，请检查日期！");

                }
            }
            m_BusInfoTable = t_ReturnTicket.m_TicketBusInfoTable;
        }
        else if(t_ReturnTicket.DateSelection() == 2)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusDayAfter.size(); i++)
            {
                if(t_ReturnTicket.m_nPassengerBusNumber == m_BusInfoTable.m_arrBusDayAfter[i].m_nBusNumber)
                {
                    //unsigned t =  m_BusInfoTable.m_arrBusTomorrow[i].getPassengerArr().size();
                    for(int j = 0; j < m_BusInfoTable.m_arrBusDayAfter[i].getPassengerArr().size(); j++)
                    {
                        if(t_ReturnTicket.m_strPassengerID == m_BusInfoTable.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerID())
                        {
                            QMessageBox::StandardButton t_Reply;
                            t_Reply = QMessageBox::question(this, "询问", "尊敬的旅客，你确定要退掉车票吗？",  QMessageBox::Yes | QMessageBox::No);

                            if (t_Reply == QMessageBox::Yes)
                            {
                                unsigned t_tempSeats = t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerSeatNumber();
                                t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].getPassengerArr().remove(j);

                                if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.size() >= 2)
                                {
                                    int k = 0;
                                    for( ; t_tempSeats > t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats[k] &&
                                           t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats[k + 1]; k++)
                                    {
                                        break;

                                    }
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.insert(k,t_tempSeats);
                                }
                                else if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.size() == 1)
                                {
                                    if(t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats[0])
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.insert(0,t_tempSeats);
                                    }
                                    else
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.insert(1,t_tempSeats);
                                    }
                                }
                                else
                                {
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.insert(0,t_tempSeats);
                                }
                                QMessageBox::information(this, "提示", "您已成功退票！");
                            }
                            else
                            {
                                QMessageBox::information(this, "提示", "您已取消退票");
                            }

                        }
                        else
                        {
                            QMessageBox::critical(this, "错误", "未查询到您的身份信息");
                        }
                    }

                }
                else
                {
                    QMessageBox::critical(this, "错误", "错误的车辆信息，请检查日期！");

                }
            }
            m_BusInfoTable = t_ReturnTicket.m_TicketBusInfoTable;
        }
        else
        {
            QMessageBox::critical(this, "错误", "错误的日期信息，请检查日期！");
        }
    }

}



void MainWindow::on_DeleteBus_triggered()
{
    DeleteBus t_DeleteBus(this);     //新建一个对话框对象，用于接受界面表格中输入内容
    t_DeleteBus.m_DeleteBusInfo = m_BusInfoTable;
    t_DeleteBus.m_importBusNumberToComboBox(m_BusInfoTable);
    int ret = t_DeleteBus.exec();    //定义return为弹出窗口的返回值
    if(ret==QDialog::Accepted)          //确定按键被按下，进行保存
    {
        if(t_DeleteBus.DateSelection() == 0)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusToday.size(); i++)
            {
                if(t_DeleteBus.m_nDeleteBusNumber == m_BusInfoTable.m_arrBusToday[i].m_nBusNumber)
                {
                    QMessageBox::StandardButton t_Reply;
                    t_Reply = QMessageBox::question(this, "询问", "尊敬的管理员，你确定要删掉车辆吗？",  QMessageBox::Yes | QMessageBox::No);

                    if (t_Reply == QMessageBox::Yes)
                    {
                        t_DeleteBus.m_DeleteBusInfo.m_arrBusToday.remove(i);
                        QMessageBox::information(this, "提示", "您已成功移除车辆！");
                    }
                    else
                    {
                        QMessageBox::information(this, "提示", "您已取消移除车辆。");
                    }
                }
            }
        }
        else if(t_DeleteBus.DateSelection() == 1)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusTomorrow.size(); i++)
            {
                if(t_DeleteBus.m_nDeleteBusNumber == m_BusInfoTable.m_arrBusTomorrow[i].m_nBusNumber)
                {
                    QMessageBox::StandardButton t_Reply;
                    t_Reply = QMessageBox::question(this, "询问", "尊敬的管理员，你确定要删掉车辆吗？",  QMessageBox::Yes | QMessageBox::No);

                    if (t_Reply == QMessageBox::Yes)
                    {
                        t_DeleteBus.m_DeleteBusInfo.m_arrBusTomorrow.remove(i);
                        QMessageBox::information(this, "提示", "您已成功移除车辆！");
                    }
                    else
                    {
                        QMessageBox::information(this, "提示", "您已取消移除车辆。");
                    }
                }
            }
        }
        else if(t_DeleteBus.DateSelection() == 2)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusDayAfter.size(); i++)
            {
                if(t_DeleteBus.m_nDeleteBusNumber == m_BusInfoTable.m_arrBusDayAfter[i].m_nBusNumber)
                {
                    QMessageBox::StandardButton t_Reply;
                    t_Reply = QMessageBox::question(this, "询问", "尊敬的管理员，你确定要删掉车辆吗？",  QMessageBox::Yes | QMessageBox::No);

                    if (t_Reply == QMessageBox::Yes)
                    {
                        t_DeleteBus.m_DeleteBusInfo.m_arrBusDayAfter.remove(i);
                        QMessageBox::information(this, "提示", "您已成功移除车辆！");
                    }
                    else
                    {
                        QMessageBox::information(this, "提示", "您已取消移除车辆。");
                    }
                }
            }
        }
        else
        {
            QMessageBox::critical(this, "错误", "日期选择有误，请重试。");
        }
        m_BusInfoTable = t_DeleteBus.m_DeleteBusInfo;
    }

}



void MainWindow::on_actionOpenFile_triggered()
{
    BusInfoTable FileBusInfoTable;
    // ImportFile t_tempImportFile;
    // QString t_strCurPath = QDir::currentPath();
    // QString t_strTitle = "选择一个文件";
    // QString t_strFilter = "文本文件(*.txt);;所有文件(*.*)";
    // QString t_strFileName = QFileDialog::getOpenFileName(this, t_strTitle, t_strCurPath, t_strFilter);
    // if(t_strFileName.isEmpty())
    //     return;
    // t_tempImportFile.ImportBusInfoFile(t_strFileName);
    // // ShowShiftTable();
    QString path = QFileDialog::getOpenFileName(this,"打开","../");
    if(path.isEmpty() == false)
    {
        //创建文件对象
        QFile file(path);

        bool t_bcondition = file.open(QIODevice::ReadOnly); //只读模式打开
        if(t_bcondition == true)
        {
        //一行一行的读
            Bus t_tempBus;
            QByteArray array;
            while(file.atEnd() == false)
            {
                array = file.readLine();
                QString t_str = QString(array).toUtf8().data();
                //int i = 0;
                if(true)
                {
                    //array = file.readLine();
                    QString t_strTempDate ;
                    QString t_strTempNumber;
                    QString t_strTempTime;
                    QString t_strTempTerminal;
                    QString t_strTempSeats;
                    if(t_str == "今天（8月31日）\n")
                    {
                        QString t_strTempDate = "今天（8月31日）";
                        for(int k = 0; k < 5 ;k++)
                        {
                            array = file.readLine();

                            if(k == 0)
                            {
                                t_strTempNumber = QString(array).toUtf8().data();
                            }
                            else if(k == 1)
                            {
                                t_strTempTime = QString(array).toUtf8().data();
                            }
                            else if(k == 2)
                            {
                                t_strTempTerminal = QString(array).toUtf8().data();
                            }
                            else if(k == 3)
                            {
                                t_strTempSeats = QString(array).toUtf8().data();
                            }
                            else
                            {

                            }
                        }
                        t_tempBus.m_Date = 0;
                        t_tempBus.m_nBusNumber = t_strTempNumber.remove("\n").toInt();
                        t_tempBus.m_strTerminal = t_strTempTerminal.remove("\n");
                        t_tempBus.m_timeDepartureTime = QTime::fromString(t_strTempTime.remove("\n"),"hh:mm");
                        t_tempBus.m_unSeats = t_strTempSeats.remove("\n").toUInt();
                        t_tempBus.setSeatsArr(t_tempBus.m_unSeats);
                        FileBusInfoTable.m_arrBusToday.push_back(t_tempBus);
                        m_BusInfoTable = FileBusInfoTable;
                        ShowBusInfoTable(0);
                    }
                    else if(t_str == "明天（9月1日）\n")
                    {
                        QString t_strTempDate = "明天（9月1日）";
                        for(int k = 0; k < 5 ;k++)
                        {
                            array = file.readLine();

                            if(k == 0)
                            {
                                t_strTempNumber = QString(array).toUtf8().data();
                            }
                            else if(k == 1)
                            {
                                t_strTempTime = QString(array).toUtf8().data();
                            }
                            else if(k == 2)
                            {
                                t_strTempTerminal = QString(array).toUtf8().data();
                            }
                            else if(k == 3)
                            {
                                t_strTempSeats = QString(array).toUtf8().data();
                            }
                            else if(k == 4)
                            {
                                //t_strTempSeats = QString(array).toUtf8().data();
                            }
                            else
                            {

                            }
                        }
                        t_tempBus.m_Date = 1;
                        t_tempBus.m_nBusNumber = t_strTempNumber.remove("\n").toInt();
                        t_tempBus.m_strTerminal = t_strTempTerminal.remove("\n");
                        t_tempBus.m_timeDepartureTime = QTime::fromString(t_strTempTime.remove("\n"),"hh:mm");
                        t_tempBus.m_unSeats = t_strTempSeats.remove("\n").toUInt();
                        t_tempBus.setSeatsArr(t_tempBus.m_unSeats);
                        FileBusInfoTable.m_arrBusTomorrow.push_back(t_tempBus);
                        m_BusInfoTable = FileBusInfoTable;
                        ShowBusInfoTable(1);
                    }
                    else if(t_str == "后天（9月2日）\n")
                    {
                        QString t_strTempDate = "后天（9月2日）";
                        for(int k = 0; k < 5 ;k++)
                        {
                            array = file.readLine();

                            if(k == 0)
                            {
                                t_strTempNumber = QString(array).toUtf8().data();
                            }
                            else if(k == 1)
                            {
                                t_strTempTime = QString(array).toUtf8().data();
                            }
                            else if(k == 2)
                            {
                                t_strTempTerminal = QString(array).toUtf8().data();
                            }
                            else if(k == 3)
                            {
                                t_strTempSeats = QString(array).toUtf8().data();
                            }
                            else
                            {

                            }
                        }
                        t_tempBus.m_Date = 2;
                        t_tempBus.m_nBusNumber = t_strTempNumber.remove("\n").toInt();
                        t_tempBus.m_strTerminal = t_strTempTerminal.remove("\n");
                        t_tempBus.m_timeDepartureTime = QTime::fromString(t_strTempTime.remove("\n"),"hh:mm");
                        t_tempBus.m_unSeats = t_strTempSeats.remove("\n").toUInt();
                        t_tempBus.setSeatsArr(t_tempBus.m_unSeats);
                        FileBusInfoTable.m_arrBusDayAfter.push_back(t_tempBus);
                        m_BusInfoTable = FileBusInfoTable;
                        ShowBusInfoTable(2);
                    }
                    else
                    {

                    }
                }
                else
                {

                }

            }
            //ui->textEdit->setText(QString(array).toUtf8().data());
        }
        file.close();
        //获取文件信息



    }

}





void MainWindow::on_SearchInfo_triggered()
{
    SearchInfo t_Search(this);
    t_Search.m_SearchInfoTable = m_BusInfoTable;
    t_Search.exec();
}


void MainWindow::on_actionRefresh_triggered()
{
    ui->BusList->clear();
    ui->BusList->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
    for(int i = 0; i <= 2; i++)
    {
        ShowBusInfoTable(i);
        ui->BusList->removeRow(20);
    }
    QMessageBox::information(this, "提示", "刷新成功！");
}


void MainWindow::on_actionRefresh_2_triggered()
{
    ui->BusList->clear();
    ui->BusList->setHorizontalHeaderLabels({"班次号", "发车日期","发车时间", "终点站","座位数","空座位数"});  //初始化表格
    for(int i = 0; i <= 2; i++)
    {
        ShowBusInfoTable(i);
        ui->BusList->removeRow(20);
    }
    QMessageBox::information(this, "提示", "刷新成功！");
}


void MainWindow::on_actionBuyTicket_triggered()
{
    BuyTicket t_NewBuyTicket(this);     //新建一个Passenger对话框对象，用于接受界面表格中输入内容
    t_NewBuyTicket.m_TicketBusInfoTable = m_BusInfoTable;
    t_NewBuyTicket.DateSelection();
    t_NewBuyTicket.m_importBusNumberToComboBox(m_BusInfoTable);
    int ret = t_NewBuyTicket.exec();    //定义return为弹出窗口的返回值
    t_NewBuyTicket.DateSelection();

    if(ret==QDialog::Accepted)          //确定按键被按下，进行保存
    {
        Passenger t_tempPassenger;      //创建一个暂时的乘客
        t_tempPassenger.m_setPassengerName("0");//初始化姓名
        t_tempPassenger.m_setPassengerID("0");//初始化身份证
        t_tempPassenger.m_setPassengerBusNumber(-1);//初始化车次号
        t_tempPassenger.m_setPassengerSeatNumber(-1);//初始化座位



        t_tempPassenger.m_setPassengerName(t_NewBuyTicket.m_getPassengerName());//获取填写的姓名
        t_tempPassenger.m_setPassengerID(t_NewBuyTicket.m_getPassengerID());//获取填写的身份证
        t_tempPassenger.m_setPassengerDate(t_NewBuyTicket.m_getPassengerDate());//获取填写的日期
        t_tempPassenger.m_setPassengerBusNumber(t_NewBuyTicket.m_getPassengerBusNumber());//获取填写的车次号
        t_tempPassenger.m_setPassengerSeatNumber(t_NewBuyTicket.m_getPassengerSeatNumber());//获取填写的座位号


        int i = t_NewBuyTicket.m_getPassengerDate();
        int j;//引入一个过程变量j，用以控制表格位置
        int k = 0;//引入一个过程变量k，用以控制数组位置
        int t_emptySeats;//空座位数

        if(i == 0)//购票日期为今天时
        {
            for(int k = 0; k < t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday.size();k++)//获取车次下标k
            {
                if(t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday[k].m_nBusNumber == t_NewBuyTicket.m_getPassengerBusNumber())
                {
                    break;
                }
            }

            j = k;
            t_emptySeats = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday[k].m_arrSeats.size();//获取空座位数
            t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday[k].AddPassenger(t_tempPassenger);//向车辆中添加乘客信息
        }
        else if(i == 1)//购票日期为明天时
        {
            for(int k = 0; k < t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow.size();k++)//获取车次下标k
            {
                if(t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow[k].m_nBusNumber == t_NewBuyTicket.m_getPassengerBusNumber())
                {
                    break;
                }
            }
            j = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday.size() + k + 1 ;

            t_emptySeats = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow[k].m_arrSeats.size();//获取空座位数
            t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow[k].AddPassenger(t_tempPassenger);//向车辆中添加乘客信息
        }
        else if(i == 2)//购票日期为后天时
        {
            for(int k = 0; k < t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusDayAfter.size();k++)//获取车次下标k
            {
                if(t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusDayAfter[k].m_nBusNumber == t_NewBuyTicket.m_getPassengerBusNumber())
                {
                    break;
                }
            }
            j = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusToday.size() + t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusTomorrow.size() +
                k + 2;//插入位置原为TodayBusAmount + TomorrowBusAmount + 1，但是空一行方便观察故 + 1

            t_emptySeats = t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusDayAfter[k].m_arrSeats.size();//获取空座位数
            t_NewBuyTicket.m_TicketBusInfoTable.m_arrBusDayAfter[k].AddPassenger(t_tempPassenger);//向车辆中添加乘客信息

        }
        else//意外情况控制
        {
            j = -1;//意外情况控制
            t_emptySeats = -1;  //意外情况控制
        }
        QString t_tstrEmptySeats = QString::number(t_emptySeats);         //座位号转化
        ui->BusList ->setItem(j,5,new QTableWidgetItem(t_tstrEmptySeats));//将空座位数填入表格
        m_BusInfoTable = t_NewBuyTicket.m_TicketBusInfoTable;             //数据同步

    }
}


void MainWindow::on_actionReturnTicket_triggered()
{
    ReturnTicket t_ReturnTicket(this);     //新建一个Passenger对话框对象，用于接受界面表格中输入内容
    t_ReturnTicket.m_TicketBusInfoTable = m_BusInfoTable;
    //t_ReturnTicket.DateSelection();
    t_ReturnTicket.m_importBusNumberToComboBox(m_BusInfoTable);
    int ret = t_ReturnTicket.exec();    //定义return为弹出窗口的返回值
    if(ret==QDialog::Accepted)          //确定按键被按下，进行保存
    {
        if(t_ReturnTicket.DateSelection() == 0)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusToday.size(); i++)
            {
                if(t_ReturnTicket.m_nPassengerBusNumber == m_BusInfoTable.m_arrBusToday[i].m_nBusNumber)
                {
                    //unsigned t =  m_BusInfoTable.m_arrBusToday[i].getPassengerArr().size();
                    for(int j = 0; j < m_BusInfoTable.m_arrBusToday[i].getPassengerArr().size(); j++)
                    {
                        if(t_ReturnTicket.m_strPassengerID == m_BusInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerID())
                        {
                            QMessageBox::StandardButton t_Reply;
                            t_Reply = QMessageBox::question(this, "询问", "尊敬的旅客，你确定要退掉车票吗？",  QMessageBox::Yes | QMessageBox::No);

                            if (t_Reply == QMessageBox::Yes)
                            {
                                unsigned t_tempSeats = t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].getPassengerArr()[j].m_getPassengerSeatNumber();
                                t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].getPassengerArr().remove(j);

                                if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.size() >= 2)
                                {
                                    int k = 0;
                                    for( ; t_tempSeats > t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats[k] &&
                                           t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats[k + 1]; k++)
                                    {
                                        break;

                                    }
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.insert(k,t_tempSeats);
                                }
                                else if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.size() == 1)
                                {
                                    if(t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats[0])
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.insert(0,t_tempSeats);
                                    }
                                    else
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.insert(1,t_tempSeats);
                                    }
                                }
                                else
                                {
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusToday[i].m_arrSeats.insert(0,t_tempSeats);
                                }
                                QMessageBox::information(this, "提示", "您已成功退票！");
                            }
                            else
                            {
                                QMessageBox::information(this, "提示", "您已取消退票");
                            }

                        }
                        else
                        {
                            QMessageBox::critical(this, "错误", "未查询到您的身份信息");
                        }
                    }

                }
                else
                {
                    QMessageBox::critical(this, "错误", "错误的车辆信息，请检查日期！");

                }
            }
            m_BusInfoTable = t_ReturnTicket.m_TicketBusInfoTable;
        }
        else if (t_ReturnTicket.DateSelection() == 1)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusTomorrow.size(); i++)
            {
                if(t_ReturnTicket.m_nPassengerBusNumber == m_BusInfoTable.m_arrBusTomorrow[i].m_nBusNumber)
                {
                    //unsigned t =  m_BusInfoTable.m_arrBusTomorrow[i].getPassengerArr().size();
                    for(int j = 0; j < m_BusInfoTable.m_arrBusTomorrow[i].getPassengerArr().size(); j++)
                    {
                        if(t_ReturnTicket.m_strPassengerID == m_BusInfoTable.m_arrBusTomorrow[i].getPassengerArr()[j].m_getPassengerID())
                        {
                            QMessageBox::StandardButton t_Reply;
                            t_Reply = QMessageBox::question(this, "询问", "尊敬的旅客，你确定要退掉车票吗？",  QMessageBox::Yes | QMessageBox::No);

                            if (t_Reply == QMessageBox::Yes)
                            {
                                unsigned t_tempSeats = t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].getPassengerArr()[j].m_getPassengerSeatNumber();
                                t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].getPassengerArr().remove(j);

                                if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.size() >= 2)
                                {
                                    int k = 0;
                                    for( ; t_tempSeats > t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats[k] &&
                                           t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats[k + 1]; k++)
                                    {
                                        break;

                                    }
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.insert(k,t_tempSeats);
                                }
                                else if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.size() == 1)
                                {
                                    if(t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats[0])
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.insert(0,t_tempSeats);
                                    }
                                    else
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.insert(1,t_tempSeats);
                                    }
                                }
                                else
                                {
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusTomorrow[i].m_arrSeats.insert(0,t_tempSeats);
                                }
                                QMessageBox::information(this, "提示", "您已成功退票！");
                            }
                            else
                            {
                                QMessageBox::information(this, "提示", "您已取消退票");
                            }

                        }
                        else
                        {
                            QMessageBox::critical(this, "错误", "未查询到您的身份信息");
                        }
                    }

                }
                else
                {
                    QMessageBox::critical(this, "错误", "错误的车辆信息，请检查日期！");

                }
            }
            m_BusInfoTable = t_ReturnTicket.m_TicketBusInfoTable;
        }
        else if(t_ReturnTicket.DateSelection() == 2)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusDayAfter.size(); i++)
            {
                if(t_ReturnTicket.m_nPassengerBusNumber == m_BusInfoTable.m_arrBusDayAfter[i].m_nBusNumber)
                {
                    //unsigned t =  m_BusInfoTable.m_arrBusTomorrow[i].getPassengerArr().size();
                    for(int j = 0; j < m_BusInfoTable.m_arrBusDayAfter[i].getPassengerArr().size(); j++)
                    {
                        if(t_ReturnTicket.m_strPassengerID == m_BusInfoTable.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerID())
                        {
                            QMessageBox::StandardButton t_Reply;
                            t_Reply = QMessageBox::question(this, "询问", "尊敬的旅客，你确定要退掉车票吗？",  QMessageBox::Yes | QMessageBox::No);

                            if (t_Reply == QMessageBox::Yes)
                            {
                                unsigned t_tempSeats = t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].getPassengerArr()[j].m_getPassengerSeatNumber();
                                t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].getPassengerArr().remove(j);

                                if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.size() >= 2)
                                {
                                    int k = 0;
                                    for( ; t_tempSeats > t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats[k] &&
                                           t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats[k + 1]; k++)
                                    {
                                        break;

                                    }
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.insert(k,t_tempSeats);
                                }
                                else if(t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.size() == 1)
                                {
                                    if(t_tempSeats < t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats[0])
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.insert(0,t_tempSeats);
                                    }
                                    else
                                    {
                                        t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.insert(1,t_tempSeats);
                                    }
                                }
                                else
                                {
                                    t_ReturnTicket.m_TicketBusInfoTable.m_arrBusDayAfter[i].m_arrSeats.insert(0,t_tempSeats);
                                }
                                QMessageBox::information(this, "提示", "您已成功退票！");
                            }
                            else
                            {
                                QMessageBox::information(this, "提示", "您已取消退票");
                            }

                        }
                        else
                        {
                            QMessageBox::critical(this, "错误", "未查询到您的身份信息");
                        }
                    }

                }
                else
                {
                    QMessageBox::critical(this, "错误", "错误的车辆信息，请检查日期！");

                }
            }
            m_BusInfoTable = t_ReturnTicket.m_TicketBusInfoTable;
        }
        else
        {
            QMessageBox::critical(this, "错误", "错误的日期信息，请检查日期！");
        }
    }

}


void MainWindow::on_actionAddNewBus_triggered()
{
    AddBus t_AddNewBus(this);       //新建一个AddBus对话框对象，用于接受界面表格中输入内容
    int ret = t_AddNewBus.exec();   //定义return为弹出窗口的返回值
    if(ret==QDialog::Accepted)      //确定按键被按下，进行保存
    {
        Bus tempBus;                //新建一个Bus类的暂时对象
        tempBus.m_Date = -1;        //新建一个选择变量赋哑元-1（用以选择Vector数列）

        tempBus.m_Date = t_AddNewBus.DateSelection();                       //获取日期，并赋值
        //tempBus.setSeatsArr(t_AddNewBus.m_unSeats);                         //设定座位数据集
        tempBus.m_nBusNumber          =   t_AddNewBus.m_nBusNumber;         //赋值，数据从AddBus中转交给MainWindow,让主窗口处理数据。
        tempBus.m_timeDepartureTime   =   t_AddNewBus.m_timeDepartureTime;  //赋值，数据从AddBus中转交给MainWindow,让主窗口处理数据。
        tempBus.m_strTerminal         =   t_AddNewBus.m_strTerminal;        //赋值，数据从AddBus中转交给MainWindow,让主窗口处理数据。
        tempBus.m_unSeats             =   t_AddNewBus.m_unSeats;            //赋值，数据从AddBus中转交给MainWindow,让主窗口处理数据。

        bool t_bUniqueBusNumber = 0;//bool变量，判断车次号是否唯一
        if(tempBus.m_Date == 0)//日期为今天时
        {
            if(m_BusInfoTable.m_arrBusToday.size() == 0)//如果数组中没有元素，则不会重复
            {
                t_bUniqueBusNumber = 1;//车次号是唯一的
            }
            else
            {
                for(int i = 0;i < m_BusInfoTable.m_arrBusToday.size();i++)//遍历今天车次号，确定不会重复
                {
                    if(tempBus.m_nBusNumber == m_BusInfoTable.m_arrBusToday[i].m_nBusNumber)
                    {
                        t_bUniqueBusNumber = 0;//有重复车牌号，赋值为假
                        break;//重复了，跳出循环
                    }
                    else
                    {
                        t_bUniqueBusNumber = 1;//没有重复的车次号
                    }
                }

            }

        }
        else if(tempBus.m_Date == 1)//日期为明天时
        {
            if(m_BusInfoTable.m_arrBusTomorrow.size() == 0)//如果数组中没有元素，则不会重复
            {
                t_bUniqueBusNumber = 1;//车次号是唯一的
            }
            else
            {
                for(int i = 0;i < m_BusInfoTable.m_arrBusTomorrow.size();i++)//遍历明天车次号，确定不会重复
                {
                    if(tempBus.m_nBusNumber == m_BusInfoTable.m_arrBusTomorrow[i].m_nBusNumber)
                    {
                        t_bUniqueBusNumber = 0;//有重复车牌号，赋值为假
                        break;//重复了，跳出循环
                    }
                    else
                    {
                        t_bUniqueBusNumber = 1;//没有重复的车次号
                    }

                }
            }
        }
        else if(tempBus.m_Date == 2)//日期为后天时
        {
            if(m_BusInfoTable.m_arrBusDayAfter.size() == 0)//如果数组中没有元素，则不会重复
            {
                t_bUniqueBusNumber = 1;//车次号是唯一的
            }
            else
            {
                for(int i = 0;i < m_BusInfoTable.m_arrBusDayAfter.size();i++)//遍历后天车次号，确定不会重复
                {
                    if(tempBus.m_nBusNumber == m_BusInfoTable.m_arrBusDayAfter[i].m_nBusNumber)
                    {
                        t_bUniqueBusNumber = 0;//有重复车牌号，赋值为假
                        break;//重复了，跳出循环
                    }
                    else
                    {
                        t_bUniqueBusNumber = 1;//没有重复的车次号
                    }
                }
            }
        }

        if(tempBus.m_nBusNumber!=0 && tempBus.m_strTerminal != "0" && tempBus.m_unSeats!=0 && tempBus.m_Date != -1 && t_bUniqueBusNumber)
        {
            tempBus.setSeatsArr(tempBus.m_unSeats);                           //生成一个座位号vector数组
            m_BusInfoTable.m_AddNewBus(tempBus,tempBus.m_Date);               //导入新添加的Bus
            ShowBusInfoTable(tempBus.m_Date);                                 //显示所有Bus的表格
            QMessageBox::information(this, "提示", "成功添加新巴士");            //提示信息，添加成功
        }
        else if(tempBus.m_nBusNumber!=0 && tempBus.m_strTerminal != "" && tempBus.m_unSeats==0)
        {
            QMessageBox::StandardButton t_Reply;
            t_Reply = QMessageBox::question(this, "询问", "你确定座位数为0吗？",  QMessageBox::Yes | QMessageBox::No);
            if (t_Reply == QMessageBox::Yes)
            {
                tempBus.setSeatsArr(tempBus.m_unSeats);                         //生成一个座位号vector数组
                m_BusInfoTable.m_AddNewBus(tempBus,tempBus.m_Date);             //导入新添加的Bus
                ShowBusInfoTable(tempBus.m_Date);                               //显示所有Bus的表格
            }
            else
            {
                QMessageBox::critical(this, "错误", "座位数为0，添加车辆失败！");
            }

        }
        else if(tempBus.m_nBusNumber == 0 && tempBus.m_strTerminal != "")
        {
            QMessageBox::critical(this, "错误", "无效的车次号，添加车辆失败！");
        }
        else if(tempBus.m_nBusNumber != 0 && tempBus.m_strTerminal == "")
        {
            QMessageBox::critical(this, "错误", "无效的终点站，添加车辆失败！");
        }
        else if(tempBus.m_nBusNumber == 0 && tempBus.m_strTerminal == "")
        {
            QMessageBox::critical(this, "错误", "无效的车次号&终点站，添加车辆失败！");
        }
        else if(tempBus.m_Date == -1)
        {
            QMessageBox::critical(this, "错误", "无效的日期，添加车辆失败！");
        }
        else if(!t_bUniqueBusNumber)
        {
            QMessageBox::critical(this, "错误", "车次号重复，添加车辆失败！");
        }
    }
}


void MainWindow::on_actionDeleteBus_triggered()
{
    DeleteBus t_DeleteBus(this);     //新建一个对话框对象，用于接受界面表格中输入内容
    t_DeleteBus.m_DeleteBusInfo = m_BusInfoTable;
    t_DeleteBus.m_importBusNumberToComboBox(m_BusInfoTable);
    int ret = t_DeleteBus.exec();    //定义return为弹出窗口的返回值
    if(ret==QDialog::Accepted)          //确定按键被按下，进行保存
    {
        if(t_DeleteBus.DateSelection() == 0)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusToday.size(); i++)
            {
                if(t_DeleteBus.m_nDeleteBusNumber == m_BusInfoTable.m_arrBusToday[i].m_nBusNumber)
                {
                    QMessageBox::StandardButton t_Reply;
                    t_Reply = QMessageBox::question(this, "询问", "尊敬的管理员，你确定要删掉车辆吗？",  QMessageBox::Yes | QMessageBox::No);

                    if (t_Reply == QMessageBox::Yes)
                    {
                        t_DeleteBus.m_DeleteBusInfo.m_arrBusToday.remove(i);
                        QMessageBox::information(this, "提示", "您已成功移除车辆！");
                    }
                    else
                    {
                        QMessageBox::information(this, "提示", "您已取消移除车辆。");
                    }
                }
            }
        }
        else if(t_DeleteBus.DateSelection() == 1)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusTomorrow.size(); i++)
            {
                if(t_DeleteBus.m_nDeleteBusNumber == m_BusInfoTable.m_arrBusTomorrow[i].m_nBusNumber)
                {
                    QMessageBox::StandardButton t_Reply;
                    t_Reply = QMessageBox::question(this, "询问", "尊敬的管理员，你确定要删掉车辆吗？",  QMessageBox::Yes | QMessageBox::No);

                    if (t_Reply == QMessageBox::Yes)
                    {
                        t_DeleteBus.m_DeleteBusInfo.m_arrBusTomorrow.remove(i);
                        QMessageBox::information(this, "提示", "您已成功移除车辆！");
                    }
                    else
                    {
                        QMessageBox::information(this, "提示", "您已取消移除车辆。");
                    }
                }
            }
        }
        else if(t_DeleteBus.DateSelection() == 2)
        {
            for(int i = 0; i < m_BusInfoTable.m_arrBusDayAfter.size(); i++)
            {
                if(t_DeleteBus.m_nDeleteBusNumber == m_BusInfoTable.m_arrBusDayAfter[i].m_nBusNumber)
                {
                    QMessageBox::StandardButton t_Reply;
                    t_Reply = QMessageBox::question(this, "询问", "尊敬的管理员，你确定要删掉车辆吗？",  QMessageBox::Yes | QMessageBox::No);

                    if (t_Reply == QMessageBox::Yes)
                    {
                        t_DeleteBus.m_DeleteBusInfo.m_arrBusDayAfter.remove(i);
                        QMessageBox::information(this, "提示", "您已成功移除车辆！");
                    }
                    else
                    {
                        QMessageBox::information(this, "提示", "您已取消移除车辆。");
                    }
                }
            }
        }
        else
        {
            QMessageBox::critical(this, "错误", "日期选择有误，请重试。");
        }
        m_BusInfoTable = t_DeleteBus.m_DeleteBusInfo;
    }
}


void MainWindow::on_actionCheckPassenger_triggered()
{

}


void MainWindow::on_BusList_cellDoubleClicked(int row, int column)
{
    QMessageBox::StandardButton t_Reply;
    t_Reply = QMessageBox::question(this, "询问", "你的身份是管理员吗？",  QMessageBox::Yes | QMessageBox::No);

    if (t_Reply == QMessageBox::Yes)
    {

        if(column == 0)
        {
            QString t_strDate;
            int t_nBusNumber;
            int t_nDate;
            t_strDate = ui->BusList->item(row,1)->text();
            t_nBusNumber = ui->BusList->item(row,0)->text().toInt();
            if(ui->BusList->item(row,4)->text()== ui->BusList->item(row,5)->text())
            {
                QMessageBox::information(this, "提示", "还没有旅客信息，请尝试刷新");
            }
            else if(ui->BusList->item(row,0)->text().isEmpty())
            {
                QMessageBox::information(this, "提示", "没有车辆信息。");
            }
            else
            {
                QMessageBox::information(this, "提示", "乘客信息如下");
                if(t_strDate == "今天（8月31日）")
                {
                    t_nDate = 0;
                    for(int i = 0; i < m_BusInfoTable.m_arrBusToday.size(); i++)
                    {
                        if(t_nBusNumber == m_BusInfoTable.m_arrBusToday[i].m_nBusNumber)
                        {
                            CheckPassenger t_CheckPassenger(this);       //新建一个AddBus对话框对象，用于接受界面表格中输入内容
                            t_CheckPassenger.ShowPassenger(m_BusInfoTable , t_nDate , i );                            //写入
                            t_CheckPassenger.exec();   //定义return为弹出窗口的返回值

                        }
                    }
                }
                else if (t_strDate == "明天（9月1日）")
                {
                    t_nDate = 1;
                    for(int i = 0; i < m_BusInfoTable.m_arrBusTomorrow.size(); i++)
                    {
                        if(t_nBusNumber == m_BusInfoTable.m_arrBusTomorrow[i].m_nBusNumber)
                        {
                            CheckPassenger t_CheckPassenger(this);       //新建一个对话框对象，用于接受界面表格中输入内容
                            t_CheckPassenger.ShowPassenger(m_BusInfoTable , t_nDate , i );                            //写入
                            t_CheckPassenger.exec();   //定义return为弹出窗口的返回值

                        }
                    }
                }
                else if(t_strDate == "后天（9月2日）")
                {
                    t_nDate = 2;
                    for(int i = 0; i < m_BusInfoTable.m_arrBusDayAfter.size(); i++)
                    {
                        if(t_nBusNumber == m_BusInfoTable.m_arrBusDayAfter[i].m_nBusNumber)
                        {
                            CheckPassenger t_CheckPassenger(this);       //新建一个对话框对象，用于接受界面表格中输入内容
                            t_CheckPassenger.ShowPassenger(m_BusInfoTable , t_nDate , i );                            //写入
                            t_CheckPassenger.exec();   //定义return为弹出窗口的返回值

                        }
                    }
                }
                else
                {

                }
            }
        }
        else
        {
            //啥也不干
        }
    }
    else
    {
        QMessageBox::information(this, "提示", "无权限");
    }

}


void MainWindow::on_actionSave_triggered()
{
    SaveJSON t_SaveFile;
    t_SaveFile.m_FileBusInfo = m_BusInfoTable;
    t_SaveFile.SaveAsJson();


    QString path = QFileDialog::getSaveFileName(this, "保存文件",QApplication::applicationDirPath(),"suffix(*.json)");
    QFile BusInfoFile;
    BusInfoFile.setFileName(path);
    if (!BusInfoFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "can't open , error!";
        return;

    }

    QTextStream t_Stream(&BusInfoFile);

    t_Stream << t_SaveFile.BusInfoDocument.toJson();// 写入文件
    BusInfoFile.close();
    QMessageBox::information(this, "提示", "文件写入成功");

}


void MainWindow::on_actionSavetxt_triggered()
{
    BusInfoTable WriteBusInfo = m_BusInfoTable;
    QString path = QFileDialog::getSaveFileName(this,"write","../");
    if(path.isEmpty() == false)
    {
        QFile file;            //创建对象
        file.setFileName(path);
        //打开文件，只写
        bool t_bcondition = file.open(QIODevice::WriteOnly);
        if(t_bcondition == true)
        {
            //获取内容
            for(int i = 0; i < WriteBusInfo.m_arrBusToday.size();i++)
            {
                QString t_strTempNumber     =  QString::number(WriteBusInfo.m_arrBusToday[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                QString t_strTempDate       =  "今天（8月31日）";
                QString t_strTempTime       =  WriteBusInfo.m_arrBusToday[i].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
                QString t_strTempTerminal   =  WriteBusInfo.m_arrBusToday[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                QString t_strTempSeats      =  QString::number(WriteBusInfo.m_arrBusToday[i].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
                QString t_strTempSpareSeats =  QString::number(WriteBusInfo.m_arrBusToday[i].m_arrSeats.size());
                QString t_str;
                for(int j = 0; j < 6 ; j++)
                {
                    if(j == 0)
                    {
                        t_str = t_strTempDate;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 1)
                    {
                        t_str = t_strTempNumber;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 2)
                    {
                        t_str = t_strTempTime;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 3)
                    {
                        t_str = t_strTempTerminal;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 4)
                    {
                        t_str = t_strTempSeats;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 5)
                    {
                        t_str = t_strTempSpareSeats;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                        file.write("00000000");
                        file.write("\n");
                    }
                }
            }
            //把读取到的文本写进文件file对象中
            //由于文件写函数是qbytearray类型的数据，所以需要在写之前将str转换成bytearray类型
            //在qt中有直接转换的函数，toutf8（）；
            for(int i = 0; i < WriteBusInfo.m_arrBusTomorrow.size();i++)
            {
                QString t_strTempNumber     =  QString::number(WriteBusInfo.m_arrBusTomorrow[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
                QString t_strTempDate       =  "明天（9月1日）";
                QString t_strTempTime       =  WriteBusInfo.m_arrBusTomorrow[i].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
                QString t_strTempTerminal   =  WriteBusInfo.m_arrBusTomorrow[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
                QString t_strTempSeats      =  QString::number(WriteBusInfo.m_arrBusTomorrow[i].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
                QString t_strTempSpareSeats =  QString::number(WriteBusInfo.m_arrBusTomorrow[i].m_arrSeats.size());
                QString t_str;
                for(int j = 0; j < 6 ; j++)
                {
                    if(j == 0)
                    {
                        t_str = t_strTempDate;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 1)
                    {
                        t_str = t_strTempNumber;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 2)
                    {
                        t_str = t_strTempTime;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 3)
                    {
                        t_str = t_strTempTerminal;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 4)
                    {
                        t_str = t_strTempSeats;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                    }
                    else if(j == 5)
                    {
                        t_str = t_strTempSpareSeats;
                        file.write(t_str.toUtf8());
                        file.write("\n");
                        file.write("00000000");
                        file.write("\n");
                    }
                }
            }

        }
        for(int i = 0; i < WriteBusInfo.m_arrBusDayAfter.size();i++)
        {
            QString t_strTempNumber     =  QString::number(WriteBusInfo.m_arrBusDayAfter[i].m_nBusNumber);//类型转化，用QString类型接收，方便TableWidget接收
            QString t_strTempDate       =  "后天（9月2日）";
            QString t_strTempTime       =  WriteBusInfo.m_arrBusDayAfter[i].m_timeDepartureTime.toString("hh:mm");//类型转化，用QString类型接收，方便TableWidget接收
            QString t_strTempTerminal   =  WriteBusInfo.m_arrBusDayAfter[i].m_strTerminal;//类型转化，用QString类型接收，方便TableWidget接收
            QString t_strTempSeats      =  QString::number(WriteBusInfo.m_arrBusDayAfter[i].m_unSeats);//类型转化，用QString类型接收，方便TableWidget接收
            QString t_strTempSpareSeats =  QString::number(WriteBusInfo.m_arrBusDayAfter[i].m_arrSeats.size());
            QString t_str;
            for(int j = 0; j < 6 ; j++)
            {
                if(j == 0)
                {
                    t_str = t_strTempDate;
                    file.write("00000000");
                    file.write("\n");
                    file.write(t_str.toUtf8());
                    file.write("\n");
                }
                else if(j == 1)
                {
                    t_str = t_strTempNumber;
                    file.write(t_str.toUtf8());
                    file.write("\n");
                }
                else if(j == 2)
                {
                    t_str = t_strTempTime;
                    file.write(t_str.toUtf8());
                    file.write("\n");
                }
                else if(j == 3)
                {
                    t_str = t_strTempTerminal;
                    file.write(t_str.toUtf8());
                    file.write("\n");
                }
                else if(j == 4)
                {
                    t_str = t_strTempSeats;
                    file.write(t_str.toUtf8());
                    file.write("\n");
                }
                else if(j == 5)
                {
                    t_str = t_strTempSpareSeats;
                    file.write(t_str.toUtf8());
                    file.write("\n");
                    file.write("00000000");
                    file.write("\n");
                }
            }
        }
        file.close();
    }

}

