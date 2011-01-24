#include "imsmdeducationalwidget.h"
#include "ui_imsmdeducationalwidget.h"

imsmdEducationalWidget::imsmdEducationalWidget(EducationalData *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::imsmdEducationalWidget)
{
    setTitle(tr("Educational")) ;
    ui->setupUi(frameui->mainWidget);

    putLangString(data->interactivitytype->value,ui->edInteractivityTypeLayout) ;
    putLangString(data->learningresourcetype->value,ui->edLearningResourceTypeLayout) ;
    putLangString(data->interactivitylevel->value,ui->edInteractivityLevelLayout) ;
    putLangString(data->intendedenduserrole->value,ui->edIntendedEndUserRoleLayout) ;
    putLangString(data->context->value,ui->edContextLayout) ;
    putLangString(data->typicalagerange,ui->edTypicalAgeRangeLayout) ;
    ui->edTypicalLearningTime->setText(data->typicallearningtime);
    putLangString(data->description,ui->edDescriptionLayout) ;
    ui->edLanguage->setText(data->language);

}

imsmdEducationalWidget::~imsmdEducationalWidget()
{
    delete ui;
}
