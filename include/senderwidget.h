#ifndef SENDERWIDGET_H
#define SENDERWIDGET_H

#include <QWidget>
#include<QTabWidget>
#include"terminalsender.h"
//#include"filesender.h"
#include"normalsender.h"

class SenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SenderWidget(QWidget *parent = 0);
    void loadHistory();
    void saveHistory();
signals:

     void sendDataSig(QString data);
public slots:
    void sendDataSlot(QString data);
private:
QTabWidget *senderTabs;
NormalSender *normal;
};

#endif // SENDERWIDGET_H
