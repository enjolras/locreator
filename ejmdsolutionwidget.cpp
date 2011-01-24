#include "ejmdsolutionwidget.h"
#include "ui_ejmdsolutionwidget.h"

ejmdSolutionWidget::ejmdSolutionWidget(EjmdSolution *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::ejmdSolutionWidget)
{
    setTitle(tr("Solution")) ;
    ui->setupUi(frameui->mainWidget);

    ui->soResource->setText(data->resource);
    ui->soCompilationLine->setText(data->compilationLine);
    ui->soExecutionLine->setText(data->executionLine);
    ui->soLanguage->setText(data->language);
    ui->soLanguageVersion->setText(data->languageVersion);

}

ejmdSolutionWidget::~ejmdSolutionWidget()
{
    delete ui;
}

void ejmdSolutionWidget::changeEvent(QEvent *e)
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
