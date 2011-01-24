#include "aboutBox.h"
#include "ui_aboutBox.h"

aboutBox::aboutBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutBox)
{
    ui->setupUi(this);
}

aboutBox::~aboutBox()
{
    delete ui;
}

void aboutBox::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
