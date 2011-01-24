#include "wizardevioipage.h"
#include "ui_wizardevioipage.h"

wizardEvIoiPage::wizardEvIoiPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::wizardEvIoiPage)
{
    ui->setupUi(this);
}

wizardEvIoiPage::~wizardEvIoiPage()
{
    delete ui;
}

void wizardEvIoiPage::changeEvent(QEvent *e)
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
