#include "ejmdwidget.h"
#include "ui_ejmdwidget.h"
#include "ejmdgeneralwidget.h"
#include "ejmdpresentationwidget.h"
#include "ejmdsolutionwidget.h"
#include "ejmdevaluationwidget.h"

ejmdWidget::ejmdWidget(EjmdMetadata *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ejmdWidget)
{

    ui->setupUi(this);

    QVBoxLayout *mainLayout = new QVBoxLayout() ;
    mainLayout->setMargin(0);

    ejmdGeneralWidget *generalWidget = new ejmdGeneralWidget(data->general,this) ;
    ejmdPresentationWidget *presentationWidget = new ejmdPresentationWidget(data->presentation,this) ;
    ejmdSolutionWidget *solutionWidget = new ejmdSolutionWidget(data->solution,this) ;

    mainLayout->addWidget((QWidget*)generalWidget) ;
    mainLayout->addWidget((QWidget*)presentationWidget);
    mainLayout->addWidget((QWidget*)solutionWidget);

    EjmdEvaluation *tmpEjmdEvaluation = data->evaluation ;
    while(tmpEjmdEvaluation != NULL) {
        ejmdEvaluationWidget *evaluationWidget = new ejmdEvaluationWidget(tmpEjmdEvaluation,this) ;
        tmpEjmdEvaluation = tmpEjmdEvaluation->next ;
        mainLayout->addWidget((QWidget*)evaluationWidget);
    }

    mainLayout->addStretch() ;

    QWidget *mainScrollWidget = new QWidget() ;
    mainScrollWidget->setLayout(mainLayout);

    ui->scrollArea->setWidget(mainScrollWidget);

}

ejmdWidget::~ejmdWidget()
{
    delete ui;
}

void ejmdWidget::changeEvent(QEvent *e)
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
