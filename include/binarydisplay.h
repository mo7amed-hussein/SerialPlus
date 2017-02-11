#ifndef BINARYDISPLAY_H
#define BINARYDISPLAY_H

#include"datadisplay.h"
#include <QWidget>

class BinaryDisplay : public DataDisplay
{
    Q_OBJECT
public:
    explicit BinaryDisplay(QWidget *parent = 0);
    virtual void print(QDateTime dt,SOURCETYPE type,QString &data);
    QString toBin(QString &data);
    QString char2bin(unsigned char ch);

signals:

public slots:
  private:

};

#endif // BINARYDISPLAY_H
