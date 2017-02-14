#ifndef TERMINALSENDER_H
#define TERMINALSENDER_H

#include <QWidget>
#include<QTextEdit>
#include"datasender.h"
#include"terminaledit.h"

class TerminalSender : public DataSender
{
    Q_OBJECT
public:
    explicit TerminalSender(QWidget *parent = 0);
    void sendTerm(QString d);
    void clear();
signals:

public slots:
    virtual void send();
 private:
    TerminalEdit *term;
};

#endif // TERMINALSENDER_H
