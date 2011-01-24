#include <QGridLayout>
#include <QByteArray>
#include "myqtextdocument.h"
#include "myqtextedit.h"
#include "filetextwidget.h"
#include "ui_filetextwidget.h"

fileTextWidget::fileTextWidget(QByteArray *data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileTextWidget)
{
    ui->setupUi(this);

    QGridLayout *mainLayout = new QGridLayout(this) ;
    mainLayout->setContentsMargins(0,0,0,0) ;
    textEdit = new myQTextEdit(this) ;
    mainLayout->addWidget(textEdit) ;
    this->setLayout(mainLayout);

    myQTextDocument *document = new myQTextDocument(QString(data->data()),this) ;

    textEdit->setDocument(document) ;
}

fileTextWidget::~fileTextWidget()
{
    delete ui;
}

void fileTextWidget::changeEvent(QEvent *e)
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
