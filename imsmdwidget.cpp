#include <QVBoxLayout>
#include "imsmdgeneralwidget.h"
#include "imsmdlifecyclewidget.h"
#include "imsmdtechnicalwidget.h"
#include "imsmdeducationalwidget.h"
#include "imsmdrightswidget.h"
#include "imsmdclassificationwidget.h"
#include "imsmdwidget.h"
#include "framewidget.h"
#include "ui_imsmdwidget.h"

imsmdWidget::imsmdWidget(ImsmdMetadata *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imsmdWidget)
{
    ui->setupUi(this);

    QVBoxLayout *mainLayout = new QVBoxLayout() ;
    mainLayout->setMargin(0);

    imsmdGeneralWidget *generalWidget = new imsmdGeneralWidget(data->general,this) ;
    imsmdLifecycleWidget *lifecycleWidget = new imsmdLifecycleWidget(data->lifecycle,this) ;
    imsmdTechnicalWidget *technicalWidget = new imsmdTechnicalWidget(data->technical,this) ;
    imsmdEducationalWidget *educationalWidget = new imsmdEducationalWidget(data->educational,this) ;
    imsmdRightsWidget *rightsWidget = new imsmdRightsWidget(data->rights,this) ;
    imsmdClassificationWidget *classificationWidget = new imsmdClassificationWidget(data->classification,this) ;

    mainLayout->addWidget((QWidget*)generalWidget) ;
    mainLayout->addWidget((QWidget*)lifecycleWidget) ;
    mainLayout->addWidget((QWidget*)technicalWidget) ;
    mainLayout->addWidget((QWidget*)educationalWidget);
    mainLayout->addWidget((QWidget*)rightsWidget);
    mainLayout->addWidget((QWidget*)classificationWidget);
    mainLayout->addStretch() ;

    QWidget *mainScrollWidget = new QWidget() ;
    mainScrollWidget->setLayout(mainLayout);

    ui->scrollArea->setWidget(mainScrollWidget);

}

imsmdWidget::~imsmdWidget()
{
    delete ui;
}

void imsmdWidget::changeEvent(QEvent *e)
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
