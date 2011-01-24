#include "ejmdgeneralhintssubmissionwidget.h"
#include "ui_ejmdgeneralhintssubmissionwidget.h"

ejmdGeneralHintsSubmissionWidget::ejmdGeneralHintsSubmissionWidget(EjmdGeneralHintsSubmission *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::ejmdGeneralHintsSubmissionWidget)
{
    setTitle(tr("Submission")) ;
    ui->setupUi(frameui->mainWidget);

    ui->suTimeSolve->setText(data->timesolve);
    ui->suTimeSubmit->setText(data->timesubmit);
    ui->suAttempts->setText(QString::number(data->attempts));
    ui->suCodeLines->setText(QString::number(data->codelines));
    ui->suLength->setText(QString::number(data->length));

}

ejmdGeneralHintsSubmissionWidget::~ejmdGeneralHintsSubmissionWidget()
{
    delete ui;
}

void ejmdGeneralHintsSubmissionWidget::changeEvent(QEvent *e)
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
