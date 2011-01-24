#include "imsmdlangstringwidget.h"
#include "ui_imsmdlangstringwidget.h"

imsmdLangStringWidget::imsmdLangStringWidget(LangString *argLangString, QWidget *parent, bool rootItem) :
    QWidget(parent),
    ui(new Ui::imsmdLangStringWidget),
    langString(argLangString)
{
    ui->setupUi(this);
    ui->langEdit->addItem(QIcon(":/flags/es"),tr("Spanish"),QVariant("es"));
    ui->langEdit->addItem(QIcon(":/flags/en"),tr("English"),QVariant("en"));
    ui->langEdit->addItem(QIcon(":/flags/pt"),tr("Portuguese"),QVariant("pt"));
    ui->langEdit->addItem(QIcon(":/flags/x-none"),tr("None"),QVariant("x-none")) ;

    ui->contentEdit->setText(langString->content);

    if(rootItem) {
        ui->removeButton->setVisible(FALSE);
    } else {
        ui->addButton->setVisible(FALSE);
    }

    ui->langEdit->setCurrentIndex(ui->langEdit->count()-1);

    for(int i=0;i < ui->langEdit->count();i++) {
        if(langString->language == ui->langEdit->itemData(i).toString()) {
            ui->langEdit->setCurrentIndex(i);
            break ;
        }
    }

    setLanguage(ui->langEdit->currentIndex()) ;

    connect(ui->contentEdit,SIGNAL(textEdited(QString)),this,SLOT(setContent(QString))) ;
    connect(ui->langEdit,SIGNAL(currentIndexChanged(int)),this,SLOT(setLanguage(int))) ;

    connect(ui->removeButton,SIGNAL(clicked()),this,SLOT(removeSelf())) ;
    connect(ui->addButton,SIGNAL(clicked()),this,SIGNAL(addLine())) ;

}

imsmdLangStringWidget::~imsmdLangStringWidget()
{
    delete ui;
}

void imsmdLangStringWidget::changeEvent(QEvent *e)
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

void imsmdLangStringWidget::setContent(QString content) {
    langString->content = content ;
}

void imsmdLangStringWidget::setLanguage(int index) {
    langString->language = ui->langEdit->itemData(index).toString() ;
}

void imsmdLangStringWidget::removeSelf() {
    emit removeLine(langString) ;
    this->deleteLater();
}
