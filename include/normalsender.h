#ifndef NORMALSENDER_H
#define NORMALSENDER_H

#include <QWidget>
#include<QLineEdit>
#include"datasender.h"
class NormalSender : public DataSender
{
    Q_OBJECT
public:
    explicit NormalSender(QWidget *parent = 0);

signals:

public slots:
     virtual void send();
 private:
 QLineEdit *dataTyper;
};

#endif // NORMALSENDER_H
