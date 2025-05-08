#ifndef SAVEJSON_H
#define SAVEJSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include "businfotable.h"
#include <QFile>
#include <QDir>
#include <QTextStream>

class SaveJSON
{
public:
    SaveJSON();

    QJsonArray m_arrFileBusNumber;//存储今天Bus的相关信息
    QJsonArray m_arrFileDate;
    QJsonArray m_arrFileDepartureTime;
    QJsonArray m_arrFileTerminal;
    QJsonArray m_arrFileSeatsNumber;

    QJsonArray m_arrFileBusNumber_1;//存储明天Bus的相关信息
    QJsonArray m_arrFileDate_1;
    QJsonArray m_arrFileDepartureTime_1;
    QJsonArray m_arrFileTerminal_1;
    QJsonArray m_arrFileSeatsNumber_1;

    QJsonArray m_arrFileBusNumber_2;//存储后天Bus的相关信息
    QJsonArray m_arrFileDate_2;
    QJsonArray m_arrFileDepartureTime_2;
    QJsonArray m_arrFileTerminal_2;
    QJsonArray m_arrFileSeatsNumber_2;

    QJsonObject m_DataImport();
    BusInfoTable m_FileBusInfo;
    QJsonDocument BusInfoDocument;
    void SaveAsJson();
};

#endif // SAVEJSON_H
