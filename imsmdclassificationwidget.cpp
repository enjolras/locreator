#include "imsmdclassificationwidget.h"
#include "ui_imsmdclassificationwidget.h"

imsmdClassificationWidget::imsmdClassificationWidget(ClassificationData *data, QWidget *parent) :
    frameWidget(parent),
    ui(new Ui::imsmdClassificationWidget)
{
    setTitle(tr("Classification")) ;
    ui->setupUi(frameui->mainWidget);

    putLangString(data->purpose->value,ui->clPurposeLayout) ;
    putLangString(data->keyword,ui->clKeywordLayout) ;

}

imsmdClassificationWidget::~imsmdClassificationWidget()
{
    delete ui;
}
