#include "imsmdterequirementwidget.h"
#include "ui_imsmdterequirementwidget.h"

imsmdTeRequirementWidget::imsmdTeRequirementWidget(RequirementData *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::imsmdTeRequirementWidget)
{
    setTitle(tr("Requirement")) ;
    ui->setupUi(frameui->mainWidget);

    putLangString(data->type->value,ui->requirementTypeLayout) ;
    putLangString(data->name->value,ui->requirementNameLayout) ;
    ui->requirementMinVersion->setText(data->minimumversion);
    ui->requirementMaxVersion->setText(data->maximumversion);

}

imsmdTeRequirementWidget::~imsmdTeRequirementWidget()
{
    delete ui;
}
