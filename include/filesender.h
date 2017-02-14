#ifndef FILESENDER_H
#define FILESENDER_H

#include <QWidget>
#include<QLineEdit>
#include<QRadioButton>
#include<QProgressBar>
#include"datasender.h"
class FileSender : public DataSender
{
    Q_OBJECT
public:
    explicit FileSender(QWidget *parent = 0);
    void getFile();
    void sendCommands();
    void sendData();
    void sendSlot();

signals:

public slots:
    virtual void send();
 private:
     QLineEdit *fileEdit;
     QString filePath;
     QRadioButton *allfile;
     QProgressBar *sendBar;
};

#endif // FILESENDER_H
