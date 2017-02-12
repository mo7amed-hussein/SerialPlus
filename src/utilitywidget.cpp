#include "utilitywidget.h"
#include<QVBoxLayout>
UtilityWidget::UtilityWidget(QWidget *parent) : QWidget(parent)
{

  // configWidget=new ConfigDialog(this);

   searchWidget=new SearchWidget(this);

    searchWidget->setHidden(true);
   // config->setHidden(true);
    QVBoxLayout *mainlayout=new QVBoxLayout(this);
    //mainlayout->addWidget(searchWidget);
   // mainlayout->addWidget(configWidget);
}
void UtilityWidget::showConfig()
{
// searchWidget->setVisible(false);
// configWidget->setVisible(true);
    configWidget->exec();
}

void UtilityWidget::showSearch()
{

    configWidget->setVisible(false);
    searchWidget->setVisible(true);

}
