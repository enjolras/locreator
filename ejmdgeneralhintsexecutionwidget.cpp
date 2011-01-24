#include "ejmdgeneralhintsexecutionwidget.h"
#include "ui_ejmdgeneralhintsexecutionwidget.h"

ejmdGeneralHintsExecutionWidget::ejmdGeneralHintsExecutionWidget(EjmdGeneralHintsExecution *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::ejmdGeneralHintsExecutionWidget)
{
    setTitle(tr("Execution")) ;
    ui->setupUi(frameui->mainWidget);

    ui->exTime->setText(data->time);
}

ejmdGeneralHintsExecutionWidget::~ejmdGeneralHintsExecutionWidget()
{
    delete ui;
}

void ejmdGeneralHintsExecutionWidget::changeEvent(QEvent *e)
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
