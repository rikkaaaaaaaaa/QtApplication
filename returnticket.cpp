#include "returnticket.h"
#include "ui_returnticket.h"


ReturnTicket::ReturnTicket(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReturnTicket)
{
    ui->setupUi(this);
}

ReturnTicket::~ReturnTicket()
{
    delete ui;
}

int ReturnTicket::DateSelection()//选择天数判断函数
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

void ReturnTicket::m_importBusNumberToComboBox(BusInfoTable t_tempBusInfoTable)//向下拉框中引入数据
{
    ui->comboBox->clear();//清空下拉框中数据
    QVector <Bus> t_Busarr_0 = t_tempBusInfoTable.m_arrBusToday;//创建一个临时的Bus类数组引入Bus类数据
    for(int i = 0;i < t_Busarr_0.size() ; i++ )//循环赋值
    {
        QString t_tempBusNumber = QString::number(t_Busarr_0[i].m_nBusNumber);//转化为String类型方便addItem接收
        m_TodayTicketBusNumber.push_back(t_tempBusNumber);//用数组接收相关车次号信息
        ui->comboBox->addItem(t_tempBusNumber);//向下拉框中导入数据

    }

    QVector <Bus> t_Busarr_1 = t_tempBusInfoTable.m_arrBusTomorrow;//创建一个临时的Bus类数组引入Bus类数据
    for(int i = 0;i < t_Busarr_1.size() ; i++ )//循环赋值
    {
        QString t_tempBusNumber = QString::number(t_Busarr_1[i].m_nBusNumber);//转化为String类型方便addItem接收
        m_TomorrowTicketBusNumber.push_back(t_tempBusNumber);//用数组接收相关车次号信息
        ui->comboBox->addItem(t_tempBusNumber);//向下拉框中导入数据

    }

    QVector <Bus> t_Busarr_2 = t_tempBusInfoTable.m_arrBusDayAfter;//创建一个临时的Bus类数组引入Bus类数据
    for(int i = 0;i < t_Busarr_2.size() ; i++ )//循环赋值
    {
        QString t_tempBusNumber = QString::number(t_Busarr_2[i].m_nBusNumber);//转化为String类型方便addItem接收
        m_DayAfterTicketBusNumber.push_back(t_tempBusNumber);//用数组接收相关车次号信息
        ui->comboBox->addItem(t_tempBusNumber);//向下拉框中导入数据
    }
}

void ReturnTicket::on_TodayButton_clicked()
{
    ui->comboBox->clear();//清空下拉框中数据

    for(int i = 0;i < m_TicketBusInfoTable.m_arrBusToday.size() ; i++ )//循环赋值
    {
        ui->comboBox->addItem(m_TodayTicketBusNumber[i]);//导入车次号数据进入下拉框
    }
    if(m_TodayTicketBusNumber.size() == 0)
    {
        QMessageBox::critical(this, "错误", "还未导入车辆数据，无法退票");
        ui->buttonBox->setEnabled(false);
    }
}


void ReturnTicket::on_TomorrowButton_clicked()
{
    ui->comboBox->clear();//清空下拉框中数据

    for(int i = 0;i < m_TicketBusInfoTable.m_arrBusTomorrow.size() ; i++ )//循环赋值
    {
        ui->comboBox->addItem(m_TomorrowTicketBusNumber[i]);//导入车次号数据进入下拉框
    }
    if(m_TomorrowTicketBusNumber.size() == 0)
    {
        QMessageBox::critical(this, "错误", "还未导入车辆数据，无法退票");
        ui->buttonBox->setEnabled(false);
    }
}


void ReturnTicket::on_DayAfterButton_clicked()
{
    ui->comboBox->clear();//清空下拉框中数据

    for(int i = 0;i < m_TicketBusInfoTable.m_arrBusDayAfter.size() ; i++ )//循环赋值
    {
        ui->comboBox->addItem(m_DayAfterTicketBusNumber[i]);//导入车次号数据进入下拉框
    }
    if(m_DayAfterTicketBusNumber.size() == 0)
    {
        QMessageBox::critical(this, "错误", "还未导入车辆数据，无法退票");
        ui->buttonBox->setEnabled(false);
    }
}


QString ReturnTicket::m_getIDFromWidget()
{
    QString t_String  = ui->IDEdit->text();//将IDEdit的内容转化为文本并用一个临时变量承接

    return t_String;//返回值
}

void ReturnTicket::on_buttonBox_accepted()
{
    m_nPassengerBusNumber = ui->comboBox->currentText().toInt();
    m_strPassengerID = m_getIDFromWidget();
}

