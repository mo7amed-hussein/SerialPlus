#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include<QDialog>
#include<QCheckBox>

#include"monitorwidget.h"

class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SearchDialog(QWidget *parent = 0);
    void find();
    void count();

signals:

public slots:
private:
MonitorWidget *display;
QLineEdit *findEdit;
QCheckBox *wholeWord;
QCheckBox *caseFlag;
};

#endif // SEARCHWIDGET_H
