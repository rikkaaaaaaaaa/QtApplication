#include "addbus.h"
#include "ui_addbus.h"

AddBus::AddBus(QWidget *parent)//构造函数
    : QDialog(parent)
    , ui(new Ui::AddBus)
{
    ui->setupUi(this);
}

AddBus::~AddBus()//析构函数
{
    delete ui;
}


int AddBus::m_getBusNumber()//获取车次号函数
{
    QString t_Number = ui->NumberEdit->text();//将LineEdit的内容转化为文本并用一个临时变量承接
    int t_TransNumber = t_Number.toInt();//转换文本为Int格式
    return t_TransNumber;//返回转化后的值
}

QTime AddBus::m_getDepartureTime()//获取出发时间
{
    return ui->Depature_Time->time();//将TimeEdit的值转化为Time类型并返回
}

QString AddBus::m_getTerminal()//获取终点站
{
    return ui->TerminalEdit->text();//将LineEdit的内容转化为文本并返回
}

unsigned AddBus::m_getSeats()//获得座位数
{
    QString t_Seats = ui->SeatsEdit->text();//将LineEdit的内容转化为文本并用一个临时变量承接
    int t_TransSeats = t_Seats.toUInt();//转换文本为unsigned格式
    return t_TransSeats;//返回转化后的值
}


int AddBus::DateSelection()//选择天数判断函数
{
    if(ui->TodayButton->isChecked())//今天按钮被勾选
    {
        m_DateSelection = 0;//日期赋值为0，今天
    }
    else if(ui->TomorrowButton->isChecked())//明天按钮被勾选
    {
        m_DateSelection = 1;//日期赋值为1，明天
    }
    else if(ui->DayAfterButton->isChecked())//后天按钮被勾选
    {
        m_DateSelection = 2;//日期赋值为2，后天
    }
    else
    {
        m_DateSelection = -1;//日期赋值为-1，报错
    }
    return m_DateSelection;
}

void AddBus::on_buttonBox_accepted()//当添加完车辆信息并确定后
{
    this->m_nBusNumber = m_getBusNumber();//通过获取函数将车次号导入成员变量
    this->m_timeDepartureTime = m_getDepartureTime();//通过获取函数将离开时间导入成员变量
    this->m_strTerminal = m_getTerminal();//通过获取函数将终点站导入成员变量
    this->m_unSeats = m_getSeats();//通过获取函数将座位数导入成员变量

}
