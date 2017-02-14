#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include<QTableWidget>
#include<QFile>
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
    void clear();
    bool find(QString str,bool wd,bool cs);
    void startLog(QString file, QIODevice::OpenMode mode);

    void stopLog();
signals:

public slots:
private:
    QTabWidget *displayTabs;
    DataDisplay *asciiDisplay;
    DataDisplay *hexDisplay;
    DataDisplay *binaryDisplay;

    QFile log;
    bool isLogged;
};

#endif // MONITORWIDGET_H
