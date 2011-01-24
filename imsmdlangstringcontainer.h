#ifndef IMSMDLANGSTRINGCONTAINER_H
#define IMSMDLANGSTRINGCONTAINER_H

#include <QWidget>
#include "lomodel.h"

namespace Ui {
    class imsmdLangStringContainer;
}

class imsmdLangStringContainer : public QWidget {
    Q_OBJECT
public:
    imsmdLangStringContainer(LangString *argLangString, QWidget *parent = 0);
    ~imsmdLangStringContainer();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::imsmdLangStringContainer *ui;
    LangString *langString ;

private slots:
    void addLine() ;
    void removeLine(LangString *langStringPointer) ;

};

#endif // IMSMDLANGSTRINGCONTAINER_H
