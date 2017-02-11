#ifndef FILESENDER_H
#define FILESENDER_H

#include <QWidget>
#include"datasender.h"
class FileSender : public DataSender
{
    Q_OBJECT
public:
    explicit FileSender(QWidget *parent = 0);

signals:

public slots:
    virtual void send();
};

#endif // FILESENDER_H
