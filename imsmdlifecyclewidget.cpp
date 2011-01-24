#include "imsmdlifecyclewidget.h"
#include "ui_imsmdlifecyclewidget.h"
#include "imsmdlccontributewidget.h"

imsmdLifecycleWidget::imsmdLifecycleWidget(LifecycleData *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::imsmdLifecycleWidget)
{

    setTitle(tr("Life Cycle")) ;
    ui->setupUi(frameui->mainWidget);

    putLangString(data->version,ui->lcVersionLayout) ;
    putLangString(data->status->value,ui->lcStatusLayout) ;
    putContributeItems(data->contribute) ;

}

imsmdLifecycleWidget::~imsmdLifecycleWidget()
{
    delete ui;
}

void imsmdLifecycleWidget::putContributeItems(ContributeItem *data) {

    while(data!=NULL) {
        imsmdLcContributeWidget *tmpWidget = new imsmdLcContributeWidget(data,this) ;
        ui->lcContributeLayout->addWidget(tmpWidget);
        data = data->next ;
    }
}
