#ifndef ASCIIDISPLAY_H
#define ASCIIDISPLAY_H
#include"datadisplay.h"

class AsciiDisplay : public DataDisplay
{
     Q_OBJECT

public:
    AsciiDisplay(QWidget *parent = 0);
    virtual void print(QDateTime dt,SOURCETYPE type,QString &data);
};

#endif // ASCIIDISPLAY_H
