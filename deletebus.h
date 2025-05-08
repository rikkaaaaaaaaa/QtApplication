#ifndef DELETEBUS_H
#define DELETEBUS_H

#include <QDialog>
#include "businfotable.h"

namespace Ui {
class DeleteBus;
}

class DeleteBus : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteBus(QWidget *parent = nullptr);

    BusInfoTable m_DeleteBusInfo;
    void m_importBusNumberToComboBox(BusInfoTable);       //将当天的BusVector中Bus和Bus中Seat数据集导入ComboBox

    int DateSelection();                           //判断选择的日期
    QString m_getBusNumberFromWidget();

    QVector<QString> m_TodayTicketBusNumber;       //今天可选车数组
    QVector<QString> m_TomorrowTicketBusNumber;    //明天可选车数组
    QVector<QString> m_DayAfterTicketBusNumber;    //后天可选车数组

    int m_nDeleteBusDate;                        //选择日期
    int m_nDeleteBusNumber;                   //乘客选择车次号
    ~DeleteBus();

private slots:
    void on_buttonBox_accepted();

    void on_TodayButton_clicked();
    void on_TomorrowButton_clicked();
    void on_DayAfterButton_clicked();

private:
    Ui::DeleteBus *ui;
};

#endif // DELETEBUS_H
