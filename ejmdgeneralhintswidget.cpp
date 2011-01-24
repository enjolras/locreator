#include "ejmdgeneralhintswidget.h"
#include "ui_ejmdgeneralhintswidget.h"
#include "ejmdgeneralhintssubmissionwidget.h"
#include "ejmdgeneralhintscompilationwidget.h"
#include "ejmdgeneralhintsexecutionwidget.h"

ejmdGeneralHintsWidget::ejmdGeneralHintsWidget(EjmdGeneralHints *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::ejmdGeneralHintsWidget)
{
    setTitle(tr("Hints")) ;
    ui->setupUi(frameui->mainWidget);

    ejmdGeneralHintsSubmissionWidget *submissionWidget = new ejmdGeneralHintsSubmissionWidget(data->submission,this) ;
    ui->genHintsSubmissionLayout->addWidget(submissionWidget);

    ejmdGeneralHintsCompilationWidget *compilationWidget = new ejmdGeneralHintsCompilationWidget(data->compilation,this) ;
    ui->genHintsCompilationLayout->addWidget(compilationWidget);

    ejmdGeneralHintsExecutionWidget *executionWidget = new ejmdGeneralHintsExecutionWidget(data->execution,this) ;
    ui->genHintsExecutionLayout->addWidget(executionWidget);


}

ejmdGeneralHintsWidget::~ejmdGeneralHintsWidget()
{
    delete ui;
}

void ejmdGeneralHintsWidget::changeEvent(QEvent *e)
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
