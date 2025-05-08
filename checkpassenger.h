#ifndef CHECKPASSENGER_H
#define CHECKPASSENGER_H

#include <QDialog>
#include "businfotable.h"
namespace Ui {
class CheckPassenger;
}

class CheckPassenger : public QDialog
{
    Q_OBJECT

public:
    explicit CheckPassenger(QWidget *parent = nullptr);
    ~CheckPassenger();
    void ShowPassenger(BusInfoTable , int, int);

private:
    Ui::CheckPassenger *ui;
};

#endif // CHECKPASSENGER_H
