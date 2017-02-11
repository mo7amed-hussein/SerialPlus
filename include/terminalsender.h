#ifndef TERMINALSENDER_H
#define TERMINALSENDER_H

#include <QWidget>
#include<QTextEdit>
#include"datasender.h"


class TerminalSender : public DataSender
{
    Q_OBJECT
public:
    explicit TerminalSender(QWidget *parent = 0);

signals:

public slots:
};

#endif // TERMINALSENDER_H
