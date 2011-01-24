#include "imsmdtechnicalwidget.h"
#include "ui_imsmdtechnicalwidget.h"
#include "imsmdterequirementwidget.h"
#include "imsmdteformatwidget.h"

imsmdTechnicalWidget::imsmdTechnicalWidget(TechnicalData *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::imsmdTechnicalWidget)
{
    setTitle(tr("Technical")) ;
    ui->setupUi(frameui->mainWidget);

    putRequirementItems(data->requirement) ;
    putFormatItems(data->format) ;

}

imsmdTechnicalWidget::~imsmdTechnicalWidget()
{
    delete ui;
}

void imsmdTechnicalWidget::putRequirementItems(RequirementData *data) {
    while(data!=NULL) {
        imsmdTeRequirementWidget *tmpWidget = new imsmdTeRequirementWidget(data,this) ;
        ui->teRequirementLayout->addWidget(tmpWidget);
        data = data->next ;
    }
}

void imsmdTechnicalWidget::putFormatItems(FormatData *data) {
    while(data!=NULL) {
        imsmdTeFormatWidget *tmpWidget = new imsmdTeFormatWidget(data,this) ;
        ui->teFormatLayout->addWidget(tmpWidget);
        data = data->next ;
    }
}
