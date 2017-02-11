#include "hexdisplay.h"

HexDisplay::HexDisplay(QWidget *parent) : DataDisplay(parent)
{

}

void HexDisplay::print(QDateTime dt,SOURCETYPE type,QString &data)
{
    QString str;
    str="< "+dt.date().toString(Qt::ISODate)+ " , "+dt.time().toString(Qt::ISODate)+" >";
    if(type==TX)
    {
        str+=" [TX] -";
        this->setTextColor(Qt::blue);
    }
    else
    {
       str+=" [RX] -";
       this->setTextColor(Qt::red);
    }
    str+= toHex(data);
    this->append(str.toUpper());

}
QString HexDisplay::toHex(QString &data)
{
    QByteArray arr(data.toLocal8Bit());

    return QString(arr.toHex());
}
