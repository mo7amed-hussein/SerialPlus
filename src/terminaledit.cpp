#include "terminaledit.h"
#include<QKeyEvent>
#include<QDebug>
TerminalEdit::TerminalEdit(QWidget *parent) : QTextEdit(parent)
{
 this->append(">>");
}
void TerminalEdit::keyPressEvent(QKeyEvent * e)
{
    QString str=e->text();
    QTextCursor cr=this->textCursor();
    cr.columnNumber();
   // str.to
    qDebug()<<"line pos : "<<cr.columnNumber();
    if(e->key()==Qt::Key_Up)
    {
        e->ignore();
    }
    else if(e->key()==Qt::Key_Enter || e->key()==Qt::Key_Return)
    {
        qDebug()<<"enter pressed: "<<command;
        if(!command.isEmpty())
        {
            emit newCommand(command);
        }
        command.clear();
        QTextEdit::keyPressEvent(e);
        this->append(">>");

    }
    else if(e->key()==Qt::Key_Backspace)
    {
        if(cr.columnNumber()!=2)
        {
        command.chop(1);

        QTextEdit::keyPressEvent(e);
        }
    }
    else if(e->key()>31 && e->key()<128)
    {
        qDebug()<<"key "<<e->text()<<e->key();
        command+=e->text();
    return QTextEdit::keyPressEvent(e);
    }
}
