#include "imsmdrightswidget.h"
#include "ui_imsmdrightswidget.h"

imsmdRightsWidget::imsmdRightsWidget(RightsData *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::imsmdRightsWidget)
{
    setTitle(tr("Rights")) ;
    ui->setupUi(frameui->mainWidget);

    putLangString(data->cost->value,ui->riCostLayout) ;
    putLangString(data->copyrightandotherrestrictions->value,ui->riCopyrightLayout) ;
    putLangString(data->description,ui->riDescriptionLayout) ;

}

imsmdRightsWidget::~imsmdRightsWidget()
{
    delete ui;
}
