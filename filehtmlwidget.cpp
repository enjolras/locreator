#include <QGridLayout>
#include <QByteArray>
#include <QWebPage>
#include <QWebFrame>
#include "myqtextedit.h"
#include "myqtextdocument.h"
#include "filehtmlwidget.h"
#include "ui_filehtmlwidget.h"

fileHtmlWidget::fileHtmlWidget(QByteArray *data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileHtmlWidget)
{

    ui->setupUi(this);

    QGridLayout *sourceLayout = new QGridLayout(ui->sourceTab) ;
    sourceEdit = new myQTextEdit(ui->sourceTab) ;
    sourceLayout->addWidget(sourceEdit);
    ui->sourceTab->setLayout(sourceLayout) ;

    connect(sourceEdit,SIGNAL(textChanged()),this,SLOT(textChanged())) ;

    myQTextDocument *document = new myQTextDocument(QString(data->data()),this) ;
    sourceEdit->setDocument(document);

}

fileHtmlWidget::~fileHtmlWidget()
{
    delete ui;
}

void fileHtmlWidget::changeEvent(QEvent *e)
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

void fileHtmlWidget::textChanged() {
    ui->webView->setHtml(sourceEdit->document()->toPlainText());
}
