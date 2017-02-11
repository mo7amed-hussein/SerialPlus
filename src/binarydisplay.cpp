#include "binarydisplay.h"

BinaryDisplay::BinaryDisplay(QWidget *parent) : DataDisplay(parent)
{


}

void BinaryDisplay::print(QDateTime dt,SOURCETYPE type,QString &data)
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
 str+=toBin(data);

 this->append(str);
 //qDebug()<<char2bin(12);
 //qDebug()<<char2bin(3);
 //data="1";
 //qDebug()<<toBin(data);

}
QString BinaryDisplay::toBin(QString &data)
{
    QByteArray arr(data.toLatin1());
    qDebug()<<arr;
    QString bin;

    for(int i=0;i<arr.size();i++)
    {

        bin.append(char2bin(arr[i]).toLocal8Bit());
        bin.append(" ");
    }
    return QString(bin);
}

QString BinaryDisplay::char2bin(unsigned char ch)
{
    QString bin;
    bin.setNum(ch,2);
    qDebug()<<"bin >>>"<<bin.trimmed();
    return bin;
}
