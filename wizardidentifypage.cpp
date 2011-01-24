#include "wizardidentifypage.h"
#include "ui_wizardidentifypage.h"

wizardIdentifyPage::wizardIdentifyPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::wizardIdentifyPage)
{
    ui->setupUi(this);

    this->setTitle(tr("Learning Object Identification")) ;
    this->setSubTitle(tr("Please, complete the form to identify the newly created LO")) ;

}

wizardIdentifyPage::~wizardIdentifyPage()
{
    delete ui;
}

void wizardIdentifyPage::changeEvent(QEvent *e)
{
    QWizardPage::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
