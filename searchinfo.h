#ifndef SEARCHINFO_H
#define SEARCHINFO_H

#include <QDialog>
#include "businfotable.h"
namespace Ui {
class SearchInfo;
}

class SearchInfo : public QDialog
{
    Q_OBJECT

public:
    explicit SearchInfo(QWidget *parent = nullptr);
    ~SearchInfo();
    QString SearchWhat;
    int DateSelection();  //判断选择的日期
    int SearchDate;
    QString m_getSearchInfoFromComboBox(); //从下拉框中获取查询内容
    QString SearchInfomation;
    BusInfoTable m_SearchInfoTable;

private slots:
    void on_pushButton_clicked();

private:
    Ui::SearchInfo *ui;
};

#endif // SEARCHINFO_H
