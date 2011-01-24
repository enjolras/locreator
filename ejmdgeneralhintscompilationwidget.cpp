#include "ejmdgeneralhintscompilationwidget.h"
#include "ui_ejmdgeneralhintscompilationwidget.h"

ejmdGeneralHintsCompilationWidget::ejmdGeneralHintsCompilationWidget(EjmdGeneralHintsCompilation *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::ejmdGeneralHintsCompilationWidget)
{
    setTitle(tr("Compilation")) ;
    ui->setupUi(frameui->mainWidget);

    ui->coTime->setText(data->time);
    ui->coSize->setText(QString::number(data->size));

}

ejmdGeneralHintsCompilationWidget::~ejmdGeneralHintsCompilationWidget()
{
    delete ui;
}

void ejmdGeneralHintsCompilationWidget::changeEvent(QEvent *e)
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
