#ifndef TERMINALEDIT_H
#define TERMINALEDIT_H

#include <QWidget>
#include<QTextEdit>
class TerminalEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TerminalEdit(QWidget *parent = 0);

signals:
    void newCommand(QString c);

public slots:
protected:
    void keyPressEvent(QKeyEvent * e);
 private:
    QString command;
};

#endif // TERMINALEDIT_H
