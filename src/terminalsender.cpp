#include "terminalsender.h"
#include"config.h"
#include<QGridLayout>
#include<QGroupBox>
#include<QRadioButton>
#include<QHBoxLayout>
TerminalSender::TerminalSender(QWidget *parent) : DataSender(parent)
{
    TerminalEdit *term=new TerminalEdit(this);
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

    QHBoxLayout *radioLayout=new QHBoxLayout;
    radioLayout->addWidget(cr);
    radioLayout->addWidget(lf);
    radioLayout->addWidget(cf);
    radioLayout->addStretch();

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
    emit sendDataSig(d);
}
