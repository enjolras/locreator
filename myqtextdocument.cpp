#include <QSettings>
#include "myqtextdocument.h"

myQTextDocument::myQTextDocument(const QString & text, QObject *parent) :
    QTextDocument(parent)
{

    QSettings settings("locreator","locreator") ;

    this->setDefaultFont(QFont(settings.value("TextEditFontName").toString(),
                               settings.value("TextEditFontSize").toInt()));

    this->setPlainText(text);

}
