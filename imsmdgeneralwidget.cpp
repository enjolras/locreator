#include "imsmdgeneralwidget.h"
#include "ui_imsmdgeneralwidget.h"

imsmdGeneralWidget::imsmdGeneralWidget(GeneralData *argData, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::imsmdGeneralWidget),
    data(argData)
{

    setTitle(tr("General")) ;
    ui->setupUi(frameui->mainWidget);

    ui->identifierEdit->setText(data->identifier) ;
    ui->languageEdit->setText(data->language) ;
    putLangString(data->title,ui->genTitleLayout) ;
    putLangString(data->description,ui->genDescriptionLayout) ;

    connect(ui->identifierEdit,SIGNAL(textEdited(QString)),this,SLOT(setIdentifier(QString))) ;
    connect(ui->languageEdit,SIGNAL(textEdited(QString)),this,SLOT(setLanguage(QString))) ;

}

imsmdGeneralWidget::~imsmdGeneralWidget()
{
    delete ui;
}

void imsmdGeneralWidget::setIdentifier(QString content) {
    data->identifier = content ;
}

void imsmdGeneralWidget::setLanguage(QString content) {
    data->language = content ;
}
