#include "wizardevsamplepage.h"
#include "ui_wizardevsamplepage.h"

wizardEvSamplePage::wizardEvSamplePage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::wizardEvSamplePage)
{
    ui->setupUi(this);
}

wizardEvSamplePage::~wizardEvSamplePage()
{
    delete ui;
}

void wizardEvSamplePage::changeEvent(QEvent *e)
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
