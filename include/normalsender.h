#ifndef NORMALSENDER_H
#define NORMALSENDER_H

#include <QWidget>
#include<QLineEdit>
#include<QCheckBox>
#include<QRadioButton>
#include<QRegExpValidator>
#include<QListWidget>

#include"datasender.h"
class NormalSender : public DataSender
{
    Q_OBJECT
public:
    explicit NormalSender(QWidget *parent = 0);
    QString toHex(QString data);
    QString toAscii(QString data);


signals:

public slots:
     virtual void send();
     void radioToggled();


     void editCommand(QListWidgetItem * item);
     void sendAgain(QListWidgetItem * item);

 private:
 QLineEdit *dataTyper;
 QCheckBox *del;
 QRadioButton *ascii;
 QRadioButton *hex;
 QRegExpValidator *hexValidator;
 QCompleter *comp;
 QListWidget *historyList;
};

#endif // NORMALSENDER_H
