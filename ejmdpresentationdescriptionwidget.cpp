#include "ejmdpresentationdescriptionwidget.h"
#include "ui_ejmdpresentationdescriptionwidget.h"

ejmdPresentationDescriptionWidget::ejmdPresentationDescriptionWidget(EjmdPresentationDescription *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::ejmdPresentationDescriptionWidget)
{
    setTitle(tr("Description")) ;
    ui->setupUi(frameui->mainWidget);

    ui->deResource->setText(data->resource);

}

ejmdPresentationDescriptionWidget::~ejmdPresentationDescriptionWidget()
{
    delete ui;
}

void ejmdPresentationDescriptionWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
