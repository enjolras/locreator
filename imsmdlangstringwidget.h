#ifndef IMSMDLANGSTRINGWIDGET_H
#define IMSMDLANGSTRINGWIDGET_H

#include <QWidget>
#include "lomodel.h"

namespace Ui {
    class imsmdLangStringWidget;
}

class imsmdLangStringWidget : public QWidget {
    Q_OBJECT
public:
    imsmdLangStringWidget(LangString *argLangString=0, QWidget *parent = 0, bool rootItem = FALSE);
    ~imsmdLangStringWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::imsmdLangStringWidget *ui;
    LangString *langString ;

private slots:
    void setContent(QString content) ;
    void setLanguage(int index) ;
    void removeSelf() ;

signals:
    void removeLine(LangString *langStringPointer) ;
    void addLine() ;
};

#endif // IMSMDLANGSTRINGWIDGET_H
