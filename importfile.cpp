#include "importfile.h"
#include "qdir.h"
#include <qtextstream.h>

ImportFile::ImportFile() {}


bool ImportFile::ImportBusInfoFile(const QString &t_filename)
{
    QFile t_file(t_filename);
    if(!t_file.exists())
        return false;
    if(!t_file.open(QIODevice::ReadOnly|QIODevice::Text))
        return false;
    QTextStream t_Stream(&t_file); //用文本流读取文件
    t_Stream; //显示汉字


    t_file.close();
    return true;
}
