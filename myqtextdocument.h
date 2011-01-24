#ifndef MYQTEXTDOCUMENT_H
#define MYQTEXTDOCUMENT_H

#include <QTextDocument>

class myQTextDocument : public QTextDocument
{
Q_OBJECT
public:
    myQTextDocument(const QString & text, QObject *parent = 0);

signals:

public slots:

};

#endif // MYQTEXTDOCUMENT_H
