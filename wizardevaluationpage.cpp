#include "wizardevaluationpage.h"
#include "ui_wizardevaluationpage.h"

wizardEvaluationPage::wizardEvaluationPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::wizardEvaluationPage)
{
    ui->setupUi(this);
}

wizardEvaluationPage::~wizardEvaluationPage()
{
    delete ui;
}

void wizardEvaluationPage::changeEvent(QEvent *e)
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
