#include "fileimagewidget.h"
#include "ui_fileimagewidget.h"

fileImageWidget::fileImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileImageWidget)
{
    ui->setupUi(this);
}

fileImageWidget::~fileImageWidget()
{
    delete ui;
}

void fileImageWidget::changeEvent(QEvent *e)
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
