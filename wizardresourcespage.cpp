#include "wizardresourcespage.h"
#include "ui_wizardresourcespage.h"

wizardResourcesPage::wizardResourcesPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::wizardResourcesPage)
{
    ui->setupUi(this);
}

wizardResourcesPage::~wizardResourcesPage()
{
    delete ui;
}

void wizardResourcesPage::changeEvent(QEvent *e)
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
