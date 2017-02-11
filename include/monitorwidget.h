#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include<QTableWidget>
#include"datadisplay.h"
#include"hexdisplay.h"
#include"binarydisplay.h"
#include"asciidisplay.h"

class MonitorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorWidget(QWidget *parent = 0);
    void print(QDateTime dt,SOURCETYPE type,QString &data);
signals:

public slots:
private:
    QTabWidget *displayTabs;
    DataDisplay *asciiDisplay;
    DataDisplay *hexDisplay;
    DataDisplay *binaryDisplay;
};

#endif // MONITORWIDGET_H
