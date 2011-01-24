#include "wizardpresentationpage.h"
#include "ui_wizardpresentationpage.h"

wizardPresentationPage::wizardPresentationPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::wizardPresentationPage)
{
    ui->setupUi(this);
}

wizardPresentationPage::~wizardPresentationPage()
{
    delete ui;
}

void wizardPresentationPage::changeEvent(QEvent *e)
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
