#ifndef LOXMLHANDLER_H
#define LOXMLHANDLER_H

#include <QXmlDefaultHandler>
#include <QStringList>
#include "lomodel.h"

class loItem ;

class loXmlHandler : public QXmlDefaultHandler
{

public:
    loXmlHandler(loItem *rootItemArg);
    bool startDocument() ;
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts) ;
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName) ;
    bool characters(const QString &ch) ;
    void setFilePath(QString &filePathArg) ;

private:
    loItem *rootItem ;
    loItem *resourcesItem ;
    loItem *currentItem ;
    LangString *currentLangString ;
    ImsmdMetadata *imsmdData ;
    EjmdMetadata *ejmdData ;
    ContributeItem *currentContributeItem ;
    RequirementData *currentRequirementData ;
    FormatData *currentFormatData ;
    QStringList context ;
    QList<QVariant> imsmdDataList ;
    QList<QVariant> ejmdDataList ;
    QList<QVariant> resourcesData ;
    QString *filePath ;

};

#endif // LOXMLHANDLER_H
