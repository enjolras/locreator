#include "ejmdpresentationwidget.h"
#include "ui_ejmdpresentationwidget.h"
#include "ejmdpresentationdescriptionwidget.h"

ejmdPresentationWidget::ejmdPresentationWidget(EjmdPresentation *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::ejmdPresentationWidget)
{
    setTitle(tr("Presentation")) ;
    ui->setupUi(frameui->mainWidget);

    ejmdPresentationDescriptionWidget *descWidget = new ejmdPresentationDescriptionWidget(data->description,this) ;
    ui->preDescriptionLayout->addWidget(descWidget);

}

ejmdPresentationWidget::~ejmdPresentationWidget()
{
    delete ui;
}

void ejmdPresentationWidget::changeEvent(QEvent *e)
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
