#include "imsmdlccontributewidget.h"
#include "ui_imsmdlccontributewidget.h"

imsmdLcContributeWidget::imsmdLcContributeWidget(ContributeItem *item,QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::imsmdLcContributeWidget)
{

    setTitle(tr("Contribute")) ;

    ui->setupUi(frameui->mainWidget);
    putLangString(item->role->value,ui->contributeRoleLayout) ;
    ui->contributeVCard->setText(item->vcard);
}

imsmdLcContributeWidget::~imsmdLcContributeWidget()
{
    delete ui;
}
