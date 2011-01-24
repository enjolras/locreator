#ifndef FORMATWIDGET_H
#define FORMATWIDGET_H

//#include "langStringWidget.h"
#include "lomodel.h"
#include <QWidget>

class imsmdTeFormatWidget : public QWidget /*public langStringWidget*/ {
    Q_OBJECT
public:
    imsmdTeFormatWidget(FormatData *argFormatData, QWidget *parent = 0);

private:
    FormatData *formatData ;

};

#endif // FORMATWIDGET_H
