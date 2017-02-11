#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include <QWidget>
#include<QTextEdit>
#include<QDebug>
#include<QDateTime>
#include<QString>
#include<QTextCharFormat>
#include"config.h"
class DataDisplay : public QTextEdit
{
    Q_OBJECT
public:
    explicit DataDisplay(QWidget *parent = 0);
    virtual void  print(QDateTime dt,SOURCETYPE type,QString &data)=0;

signals:

public slots:
    void onCustomContextMenuRequested(const QPoint& pos);
    void toggleCopy(bool c);

private:
     QAction *copyAction;
};

#endif // DATADISPLAY_H
