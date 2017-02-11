#ifndef NORMALSENDER_H
#define NORMALSENDER_H

#include <QWidget>
#include"datasender.h"
class NormalSender : public DataSender
{
    Q_OBJECT
public:
    explicit NormalSender(QWidget *parent = 0);

signals:

public slots:
};

#endif // NORMALSENDER_H
