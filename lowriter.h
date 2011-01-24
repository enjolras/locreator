#ifndef LOWRITER_H
#define LOWRITER_H

#include <QObject>
#include "lomodel.h"

class QFileInfo ;
class loModel ;
class QXmlStreamWriter ;

class loWriter : public QObject
{
Q_OBJECT
public:
    loWriter(const QFileInfo *file, const loModel *tree, QObject *parent = 0);

private:
    void writeLangString(QXmlStreamWriter *streamWriter, LangString *langString) ;
    void writeImsmdItem(QXmlStreamWriter *streamWriter, ImsmdItem *imsmdItem) ;
    void writeContributeItem(QXmlStreamWriter *streamWriter, ContributeItem *contItem) ;
    void writeFormatData(QXmlStreamWriter *streamWriter, FormatData *formatData) ;
    void writeRequirementData(QXmlStreamWriter *streamWriter, RequirementData *reqData) ;

signals:

public slots:

};

#endif // LOWRITER_H
