#include "ejmdgeneralwidget.h"
#include "ui_ejmdgeneralwidget.h"
#include "ejmdgeneralhintswidget.h"

ejmdGeneralWidget::ejmdGeneralWidget(EjmdGeneral *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::ejmdGeneralWidget)
{
    setTitle(tr("General")) ;
    ui->setupUi(frameui->mainWidget);

    ejmdGeneralHintsWidget *hintsWidget = new ejmdGeneralHintsWidget(data->hints,this) ;
    ui->genHintsLayout->addWidget(hintsWidget);

}

ejmdGeneralWidget::~ejmdGeneralWidget()
{
    delete ui;
}

void ejmdGeneralWidget::changeEvent(QEvent *e)
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
