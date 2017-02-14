#include "terminalsender.h"
#include"config.h"
#include<QGridLayout>
#include<QGroupBox>
#include<QRadioButton>
#include<QHBoxLayout>
#include<QPushButton>
TerminalSender::TerminalSender(QWidget *parent) : DataSender(parent)
{
    term=new TerminalEdit(this);
    QGridLayout *mainLayout=new QGridLayout(this);
   // term->setAutoFillBackground(true);
   // term->setBackgroundRole(QPalette::Highlight);
   // term->setTextBackgroundColor(Qt::black);

    term->setPlaceholderText(tr("Type to send"));

    connect(term,&TerminalEdit::newCommand,this,&TerminalSender::sendTerm);
    QGroupBox *radioGroup=new QGroupBox(tr("Append sent data"));

    QRadioButton *cr=new QRadioButton(tr("CR"));
    QRadioButton *lf=new QRadioButton(tr("LF"));
    QRadioButton *cf=new QRadioButton(tr("CR+LF"));

    QPushButton *clearBtn=new QPushButton(this);
    const QIcon clearIcon(":/resources/icons/clear.png");
    clearBtn->setToolTip(tr("clear terminal"));
    clearBtn->setIcon(clearIcon);
    connect(clearBtn,&QPushButton::clicked,this,&TerminalSender::clear);
    QHBoxLayout *radioLayout=new QHBoxLayout;
    radioLayout->addWidget(cr);
    radioLayout->addWidget(lf);
    radioLayout->addWidget(cf);
    radioLayout->addStretch();
    radioLayout->addWidget(clearBtn);

    radioGroup->setLayout(radioLayout);


    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,0,0);
    mainLayout->addWidget(radioGroup);
    mainLayout->addWidget(term);

}
void TerminalSender::send()
{

}
void TerminalSender::sendTerm(QString d)
{
    d+='\n';
    emit sendDataSig(d);
}
void TerminalSender::clear()
{
    term->clear();
    term->append(">>");
}
