#ifndef RETURNTICKET_H
#define RETURNTICKET_H

#include <QDialog>
#include "BusInfoTable.h"
#include "passenger.h"
#include <QDebug>

namespace Ui {
class ReturnTicket;
}

class ReturnTicket : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnTicket(QWidget *parent = nullptr);
    ~ReturnTicket();

    void m_importBusNumberToComboBox(BusInfoTable);       //将当天的BusVector中Bus和Bus中Seat数据集导入ComboBox
    int DateSelection();                           //判断选择的日期
    QString m_getIDFromWidget();                   //从表格中获取乘客身份证

    QVector<QString> m_TodayTicketBusNumber;       //今天可选车数组
    QVector<QString> m_TomorrowTicketBusNumber;    //明天可选车数组
    QVector<QString> m_DayAfterTicketBusNumber;    //后天可选车数组

    BusInfoTable m_TicketBusInfoTable;

    int m_nPassengerDate;                        //选择日期
    int m_nPassengerBusNumber;                   //乘客选择车次号
    QString m_strPassengerID;                    //身份证号码

private slots:
    void on_TodayButton_clicked();
    void on_TomorrowButton_clicked();
    void on_DayAfterButton_clicked();
    void on_buttonBox_accepted();

private:
    Ui::ReturnTicket *ui;
};

#endif // RETURNTICKET_H

