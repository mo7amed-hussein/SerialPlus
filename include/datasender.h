#ifndef DATASENDER_H
#define DATASENDER_H

#include <QWidget>

class DataSender : public QWidget
{
    Q_OBJECT
public:
    explicit DataSender(QWidget *parent = 0);

signals:
    emit void sendDataSig(QString data);

public slots:
    virtual void send()=0;
};

#endif // DATASENDER_H
