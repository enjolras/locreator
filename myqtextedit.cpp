#include "myqtextedit.h"

myQTextEdit::myQTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
    this->setAcceptRichText(FALSE);
}
