#ifndef IMPORTFILE_H
#define IMPORTFILE_H

#include "businfotable.h"
class ImportFile
{
public:
    ImportFile();
    BusInfoTable m_ImportBusInfoTable;
    bool ImportBusInfoFile(const QString&);
};

#endif // IMPORTFILE_H
