#include "ejmdevaluationwidget.h"
#include "ui_ejmdevaluationwidget.h"

ejmdEvaluationWidget::ejmdEvaluationWidget(EjmdEvaluation *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::ejmdEvaluationWidget)
{
    setTitle(tr("Evaluation")) ;
    ui->setupUi(frameui->mainWidget);

    ui->evEvaluationModel->setText(data->evaluationModel) ;
    ui->evEvaluationModelVersion->setText(QString::number(data->evaluationModelVersion)) ;

}

ejmdEvaluationWidget::~ejmdEvaluationWidget()
{
    delete ui;
}

void ejmdEvaluationWidget::changeEvent(QEvent *e)
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
