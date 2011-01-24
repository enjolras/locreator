#include "wizardintropage.h"
#include "ui_wizardintropage.h"

wizardIntroPage::wizardIntroPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::wizardIntroPage)
{
    ui->setupUi(this);

}

wizardIntroPage::~wizardIntroPage()
{
    delete ui;
}

void wizardIntroPage::changeEvent(QEvent *e)
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
