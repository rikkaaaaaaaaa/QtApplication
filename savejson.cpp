#include "savejson.h"

SaveJSON::SaveJSON()
{

}

QJsonObject SaveJSON::m_DataImport()
{
    //m_FileBusInfo = t_tempBusInfoTable;
    for(int i = 0; i < m_FileBusInfo.m_arrBusToday.size(); i++)
    {
        int t_seats = m_FileBusInfo.m_arrBusToday[i].m_unSeats;
        m_arrFileBusNumber.append(m_FileBusInfo.m_arrBusToday[i].m_nBusNumber);
        m_arrFileDate.append(m_FileBusInfo.m_arrBusToday[i].m_Date);
        m_arrFileDepartureTime.append(m_FileBusInfo.m_arrBusToday[i].m_timeDepartureTime.toString("hh:mm"));
        m_arrFileTerminal.append(m_FileBusInfo.m_arrBusToday[i].m_strTerminal);
        m_arrFileSeatsNumber.append(t_seats);
    }
    for(int i = 0; i < m_FileBusInfo.m_arrBusTomorrow.size(); i++)
    {
        int t_seats = m_FileBusInfo.m_arrBusTomorrow[i].m_unSeats;
        m_arrFileBusNumber_1.append(m_FileBusInfo.m_arrBusTomorrow[i].m_nBusNumber);
        m_arrFileDate_1.append(m_FileBusInfo.m_arrBusTomorrow[i].m_Date);
        m_arrFileDepartureTime_1.append(m_FileBusInfo.m_arrBusTomorrow[i].m_timeDepartureTime.toString("hh:mm"));
        m_arrFileTerminal_1.append(m_FileBusInfo.m_arrBusTomorrow[i].m_strTerminal);
        m_arrFileSeatsNumber_1.append(t_seats);
    }
    for(int i = 0; i < m_FileBusInfo.m_arrBusDayAfter.size(); i++)
    {
        int t_seats = m_FileBusInfo.m_arrBusDayAfter[i].m_unSeats;
        m_arrFileBusNumber_2.append(m_FileBusInfo.m_arrBusDayAfter[i].m_nBusNumber);
        m_arrFileDate_2.append(m_FileBusInfo.m_arrBusDayAfter[i].m_Date);
        m_arrFileDepartureTime_2.append(m_FileBusInfo.m_arrBusDayAfter[i].m_timeDepartureTime.toString("hh:mm"));
        m_arrFileTerminal_2.append(m_FileBusInfo.m_arrBusDayAfter[i].m_strTerminal);
        m_arrFileSeatsNumber_2.append(t_seats);
    }
}

void SaveJSON::SaveAsJson()
{
    QJsonObject t_DataFile;
    t_DataFile = m_DataImport();
    //BusInfoDocument(t_DataFile);
    BusInfoDocument.setObject(t_DataFile);

    QMessageBox::information(0, "提示", "数据导入成功");
}
