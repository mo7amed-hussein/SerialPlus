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

signals:

public slots:
private:
    QTabWidget *displayTabs;

};

#endif // MONITORWIDGET_H
