#ifndef HEXDISPLAY_H
#define HEXDISPLAY_H

#include <QWidget>
#include"datadisplay.h"
class HexDisplay : public DataDisplay
{
    Q_OBJECT
public:
    explicit HexDisplay(QWidget *parent = 0);
    virtual void print(QDateTime dt,SOURCETYPE type,QString &data);
    QString toHex(QString &data);


signals:

public slots:
};

#endif // HEXDISPLAY_H
