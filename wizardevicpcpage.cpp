#include "wizardevicpcpage.h"
#include "ui_wizardevicpcpage.h"

wizardEvIcpcPage::wizardEvIcpcPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::wizardEvIcpcPage)
{
    ui->setupUi(this);
}

wizardEvIcpcPage::~wizardEvIcpcPage()
{
    delete ui;
}

void wizardEvIcpcPage::changeEvent(QEvent *e)
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
