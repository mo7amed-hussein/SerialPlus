#include "utilitywidget.h"
#include<QVBoxLayout>
UtilityWidget::UtilityWidget(QWidget *parent) : QWidget(parent)
{

    ConfigWidget *config=new ConfigWidget(this);
    QVBoxLayout *mainlayout=new QVBoxLayout(this);
    mainlayout->addWidget(config);
}
