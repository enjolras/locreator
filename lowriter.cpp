#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <quazip.h>
#include <quazipfile.h>
#include <quazipnewinfo.h>
#include <QFlags>
#include <QModelIndex>
#include <QXmlStreamWriter>
#include "lowriter.h"
#include "enums.h"

loWriter::loWriter(const QFileInfo *file, const loModel *tree, QObject *parent) :
    QObject(parent)
{

    QuaZip *loFile = new QuaZip(file->absoluteFilePath()) ;

    if(!loFile->open(QuaZip::mdCreate)) {
        QMessageBox::critical(0,tr("Save Error"),tr("Cannot create ZIP file.")) ;
        delete loFile ;
        this->deleteLater() ;
        return ;
    }

    QFile tmpFile ;
    QuaZipFile writeFile ;
    writeFile.setZip(loFile);

    // We write the common (XML stuff) files to the archive
    QStringList commonFiles;
    commonFiles << "ejmd_v1.xsd" << "imscp_v1p1.xsd" << "imsmd_v1p2p4.xsd" ;

    while(!commonFiles.isEmpty()) {
        QString tmpFileName = commonFiles.takeFirst() ;
        QuaZipNewInfo tmpFileInfo(tmpFileName) ;
        writeFile.open(QIODevice::WriteOnly,tmpFileInfo) ;
        tmpFile.setFileName(":/xml/" + tmpFileName);
        tmpFile.open(QIODevice::ReadOnly) ;
        writeFile.write(tmpFile.readAll()) ;
        tmpFile.close() ;
        writeFile.close() ;
    }

    // Now we write all the resources created in the data tree
    for(int i=0;i<tree->rowCount();i++) {
        QFlags<ItemType::ItemTypes> itemType(tree->index(i,0).data(Qt::UserRole+1).toInt()) ;
        if(itemType.testFlag(ItemType::FoldResources)) {
            for(int j=0;j<tree->rowCount(tree->index(i,0));j++) {
                for(int k=0;k<tree->rowCount(tree->index(j,0,tree->index(i,0)));k++) {
                    QFlags<ItemType::ItemTypes> resType(tree->index(k,0,tree->index(j,0,tree->index(i,0))).data(Qt::UserRole+1).toInt()) ;
                    if(resType.testFlag(ItemType::File)) {
                        QuaZipNewInfo tmpFileInfo(tree->index(k,0,tree->index(j,0,tree->index(i,0))).data(Qt::DisplayRole).toString()) ;
                        writeFile.open(QIODevice::WriteOnly,tmpFileInfo) ;
                        writeFile.write(tree->index(k,0,tree->index(j,0,tree->index(i,0))).data(Qt::UserRole).toByteArray()) ;
                        writeFile.close();
                    }
                }
            }
        }
    }

    // And finally let's compose and write the lo manifest
    QuaZipNewInfo manifestInfo("imsmanifest.xml") ;
    writeFile.open(QIODevice::WriteOnly,manifestInfo) ;
    QXmlStreamWriter xmlOutput(&writeFile) ;

    ImsmdMetadata *imsmdData = &qVariantValue<ImsmdMetadata>(tree->index(0,0).data(Qt::UserRole)) ;

    xmlOutput.setAutoFormatting(TRUE);
    xmlOutput.writeStartDocument();

    xmlOutput.writeStartElement("manifest");
    xmlOutput.writeAttribute("xmlns","http://www.imsglobal.org/xsd/imscp_v1p1");
    xmlOutput.writeAttribute("xmlns:imsmd","http://www.imsglobal.org/xsd/imsmd_v1p2");
    xmlOutput.writeAttribute("xmlns:ejmd","http://www.edujudge.eu/ejmd_v2");
    xmlOutput.writeAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
    xmlOutput.writeAttribute("identifier","TMPIDENTIFIER");
    xmlOutput.writeAttribute("xsi:schemaLocation","http://www.imsglobal.org/xsd/imscp_v1p1  imscp_v1p1.xsd http://www.imsglobal.org/xsd/imsmd_v1p2  imsmd_v1p2p4.xsd http://www.edujudge.eu/ejmd_v2 ejmd_v2.xsd");

    xmlOutput.writeStartElement("metadata");

    xmlOutput.writeTextElement("schema","IMS Content");
    xmlOutput.writeTextElement("schemaversion","1.1");

    xmlOutput.writeStartElement("imsmd:lom");

    xmlOutput.writeStartElement("imsmd:general");
    xmlOutput.writeTextElement("imsmd:identifier",imsmdData->general->identifier);
    xmlOutput.writeTextElement("imsmd:language",imsmdData->general->language);
    xmlOutput.writeStartElement("imsmd:title");
    writeLangString(&xmlOutput,imsmdData->general->title) ;
    xmlOutput.writeEndElement() ; // imsmd:title
    xmlOutput.writeStartElement("imsmd:description");
    writeLangString(&xmlOutput,imsmdData->general->description) ;
    xmlOutput.writeEndElement(); // imsmd:description
    xmlOutput.writeEndElement() ; // imsmd:general

    xmlOutput.writeStartElement("imsmd:lifecycle") ;
    xmlOutput.writeStartElement("imsmd:version");
    writeLangString(&xmlOutput,imsmdData->lifecycle->version) ;
    xmlOutput.writeEndElement(); // imsmd:version
    xmlOutput.writeStartElement("imsmd:status");
    writeImsmdItem(&xmlOutput,imsmdData->lifecycle->status) ;
    xmlOutput.writeEndElement(); // imsmd:status
    writeContributeItem(&xmlOutput,imsmdData->lifecycle->contribute) ;
    xmlOutput.writeEndElement() ; // imsmd:lifecycle
    
    xmlOutput.writeStartElement("imsmd:technical") ;
    writeFormatData(&xmlOutput,imsmdData->technical->format) ;
    writeRequirementData(&xmlOutput,imsmdData->technical->requirement) ;
    xmlOutput.writeEndElement() ; // imsmd:technical
    
    xmlOutput.writeStartElement("imsmd:educational") ;
    xmlOutput.writeStartElement("imsmd:interactivitytype");
    writeImsmdItem(&xmlOutput,imsmdData->educational->interactivitytype) ;
    xmlOutput.writeEndElement(); // imsmd:interactivitytype
    xmlOutput.writeStartElement("imsmd:learningresourcetype");
    writeImsmdItem(&xmlOutput,imsmdData->educational->learningresourcetype) ;
    xmlOutput.writeEndElement(); // imsmd:learningresourcetype
    xmlOutput.writeStartElement("imsmd:interactivitylevel");
    writeImsmdItem(&xmlOutput,imsmdData->educational->interactivitylevel) ;
    xmlOutput.writeEndElement(); // imsmd:interactivitylevel
    xmlOutput.writeStartElement("imsmd:intendedenduserrole");
    writeImsmdItem(&xmlOutput,imsmdData->educational->intendedenduserrole) ;
    xmlOutput.writeEndElement(); // imsmd:intendedenduserrole
    xmlOutput.writeStartElement("imsmd:context");
    writeImsmdItem(&xmlOutput,imsmdData->educational->context) ;
    xmlOutput.writeEndElement(); // imsmd:context
    xmlOutput.writeStartElement("imsmd:typicalagerange");
    writeLangString(&xmlOutput,imsmdData->educational->typicalagerange) ;
    xmlOutput.writeEndElement(); // imsmd:typicalagerange
    xmlOutput.writeStartElement("imsmd:typicallearningtime");
    xmlOutput.writeTextElement("imsmd:datetime",imsmdData->educational->typicallearningtime);
    xmlOutput.writeEndElement(); // imsmd:typicallearningtime
    xmlOutput.writeStartElement("imsmd:description");
    writeLangString(&xmlOutput,imsmdData->educational->description) ;
    xmlOutput.writeEndElement(); // imsmd:description
    xmlOutput.writeTextElement("imsmd:language",imsmdData->educational->language);
    xmlOutput.writeEndElement() ; // imsmd:educational
    
    xmlOutput.writeStartElement("imsmd:rights") ;
    xmlOutput.writeStartElement("imsmd:cost");
    writeImsmdItem(&xmlOutput,imsmdData->rights->cost) ;
    xmlOutput.writeEndElement(); // imsmd:cost
    xmlOutput.writeStartElement("imsmd:copyrightandotherrestrictions");
    writeImsmdItem(&xmlOutput,imsmdData->rights->copyrightandotherrestrictions) ;
    xmlOutput.writeEndElement(); // imsmd:copyrightandotherrestrictions
    xmlOutput.writeStartElement("imsmd:description");
    writeLangString(&xmlOutput,imsmdData->rights->description) ;
    xmlOutput.writeEndElement();
    xmlOutput.writeEndElement() ; // imsmd:rights
    
    xmlOutput.writeStartElement("imsmd:classification") ;
    xmlOutput.writeStartElement("imsmd:purpose");
    writeImsmdItem(&xmlOutput,imsmdData->classification->purpose) ;
    xmlOutput.writeEndElement(); // imsmd:purpose
    xmlOutput.writeStartElement("imsmd:keyword");
    writeLangString(&xmlOutput,imsmdData->classification->keyword) ;
    xmlOutput.writeEndElement(); // imsmd:keyword
    xmlOutput.writeEndElement() ; // imsmd:classification

    xmlOutput.writeEndElement() ; // imsmd:lom


    EjmdMetadata *ejmdData = &qVariantValue<EjmdMetadata>(tree->index(1,0).data(Qt::UserRole)) ;


    xmlOutput.writeStartElement("ejmd:metadata");

    xmlOutput.writeStartElement("ejmd:general");
    xmlOutput.writeStartElement("ejmd:hints");
    xmlOutput.writeStartElement("ejmd:submission");
    xmlOutput.writeAttribute("ejmd:time-solve",ejmdData->general->hints->submission->timesolve);
    xmlOutput.writeAttribute("ejmd:time-submit",ejmdData->general->hints->submission->timesubmit);
    xmlOutput.writeAttribute("ejmd:attempts",QString::number(ejmdData->general->hints->submission->attempts));
    xmlOutput.writeAttribute("ejmd:code-lines",QString::number(ejmdData->general->hints->submission->codelines));
    xmlOutput.writeAttribute("ejmd:length",QString::number(ejmdData->general->hints->submission->length));
    xmlOutput.writeEndElement(); // ejmd:submission
    xmlOutput.writeStartElement("ejmd:compilation");
    xmlOutput.writeAttribute("ejmd:time",ejmdData->general->hints->compilation->time);
    xmlOutput.writeAttribute("ejmd:size",QString::number(ejmdData->general->hints->compilation->size));
    xmlOutput.writeEndElement(); // ejmd:compilation
    xmlOutput.writeStartElement("ejmd:execution");
    xmlOutput.writeAttribute("ejmd:time",ejmdData->general->hints->execution->time);
    xmlOutput.writeEndElement(); // ejmd:execution
    xmlOutput.writeEndElement(); // ejmd:hints
    xmlOutput.writeEndElement(); // ejmd:general

    xmlOutput.writeStartElement("ejmd:presentation");
    xmlOutput.writeStartElement("ejmd:description");
    xmlOutput.writeAttribute("ejmd:resource",ejmdData->presentation->description->resource);
    xmlOutput.writeEndElement(); // ejmd:description
    xmlOutput.writeEndElement(); // ejmd:presentation

    xmlOutput.writeStartElement("ejmd:solution") ;
    xmlOutput.writeAttribute("ejmd:resource",ejmdData->solution->resource) ;
    xmlOutput.writeAttribute("ejmd:compilationLine",ejmdData->solution->compilationLine);
    xmlOutput.writeAttribute("ejmd:executionLine",ejmdData->solution->executionLine);
    xmlOutput.writeAttribute("ejmd:language",ejmdData->solution->language);
    xmlOutput.writeAttribute("ejmd:languageVersion",ejmdData->solution->languageVersion);
    xmlOutput.writeEndElement(); // ejmd:solution

    EjmdEvaluation *tmpEvaluation = ejmdData->evaluation ;
    while(tmpEvaluation != NULL) {
        xmlOutput.writeStartElement("ejmd:evaluation");
        xmlOutput.writeAttribute("ejmd:evaluationModel",tmpEvaluation->evaluationModel);
        xmlOutput.writeAttribute("ejmd:evaluationModelVersion",QString::number(tmpEvaluation->evaluationModelVersion));
        xmlOutput.writeStartElement("ejmd:tests");
        EjmdEvaluationTestsTestFiles *tmpTestFiles = tmpEvaluation->tests->testFiles ;
        while(tmpTestFiles != NULL) {
            xmlOutput.writeStartElement("ejmd:testFiles");
            xmlOutput.writeAttribute("ejmd:arguments",tmpTestFiles->arguments);
            xmlOutput.writeAttribute("ejmd:valorization",QString::number(tmpTestFiles->valorization));
            xmlOutput.writeStartElement("ejmd:input");
            xmlOutput.writeAttribute("ejmd:resource",tmpTestFiles->inputResource);
            xmlOutput.writeEndElement(); // ejmd:input
            xmlOutput.writeStartElement("ejmd:output");
            xmlOutput.writeAttribute("ejmd:resource",tmpTestFiles->outputResource);
            xmlOutput.writeEndElement(); // ejmd:output
            xmlOutput.writeEndElement(); // ejmd:testFiles
            tmpTestFiles = tmpTestFiles->next ;
        }
        xmlOutput.writeEndElement(); // ejmd:tests
        xmlOutput.writeEndElement(); // ejmd:evaluation
        tmpEvaluation = tmpEvaluation->next ;
    }

    xmlOutput.writeEndElement(); // ejmd:metadata

    xmlOutput.writeEndElement() ; // metadata

    xmlOutput.writeStartElement("organizations");

    xmlOutput.writeEndElement() ; // organizations


    xmlOutput.writeStartElement("resources");


    for(int i=0;i<tree->rowCount();i++) {
        QFlags<ItemType::ItemTypes> itemType(tree->index(i,0).data(Qt::UserRole+1).toInt()) ;
        if(itemType.testFlag(ItemType::FoldResources)) {


            for(int j=0;j<tree->rowCount(tree->index(i,0));j++) {

                xmlOutput.writeStartElement("resource");
                xmlOutput.writeAttribute("identifier",tree->index(j,0,tree->index(i,0)).data(Qt::DisplayRole).toString());

                QString tmpResType ;
                QFlags<ItemType::ItemTypes> itemType(tree->index(j,0,tree->index(i,0)).data(Qt::UserRole+1).toInt()) ;

                if(itemType.testFlag(ItemType::ResInput))
                    tmpResType = "input" ;
                else if(itemType.testFlag(ItemType::ResOutput))
                    tmpResType = "output" ;
                else if(itemType.testFlag(ItemType::ResSolution))
                    tmpResType = "solution" ;
                else if(itemType.testFlag(ItemType::ResWebcontent))
                    tmpResType = "webcontent" ;

                xmlOutput.writeAttribute("type",tmpResType);

                if(itemType.testFlag(ItemType::ResWebcontent)) {
                    xmlOutput.writeAttribute("href",tree->index(j,0,tree->index(i,0)).data(Qt::UserRole).toString());
                }

                for(int k=0;k<tree->rowCount(tree->index(j,0,tree->index(i,0)));k++) {
                    xmlOutput.writeStartElement("file");
                    xmlOutput.writeAttribute("href",tree->index(k,0,tree->index(j,0,tree->index(i,0))).data(Qt::DisplayRole).toString());
                    xmlOutput.writeEndElement(); // file
                }

                xmlOutput.writeEndElement(); // resource

            }


        }
    }



    xmlOutput.writeEndElement() ; // resources


    xmlOutput.writeEndElement() ; // manifest

    xmlOutput.writeEndDocument();

    writeFile.close();
    loFile->close() ;

}

void loWriter::writeLangString(QXmlStreamWriter *streamWriter, LangString *langString) {
    while(langString != NULL) {
        streamWriter->writeStartElement("imsmd:langstring");
        streamWriter->writeAttribute("xml:lang",langString->language);
        streamWriter->writeCharacters(langString->content);
        streamWriter->writeEndElement();
        langString = langString->next ;
    }
}

void loWriter::writeImsmdItem(QXmlStreamWriter *streamWriter, ImsmdItem *imsmdItem) {
    streamWriter->writeStartElement("imsmd:source");
    writeLangString(streamWriter,imsmdItem->source) ;
    streamWriter->writeEndElement(); // imsmd:source
    streamWriter->writeStartElement("imsmd:value");
    writeLangString(streamWriter,imsmdItem->value) ;
    streamWriter->writeEndElement(); // imsmd:value
}

void loWriter::writeContributeItem(QXmlStreamWriter *streamWriter, ContributeItem *contItem) {
    while(contItem != NULL) {
        streamWriter->writeStartElement("imsmd:contribute");
        streamWriter->writeStartElement("imsmd:role");
        writeImsmdItem(streamWriter,contItem->role) ;
        streamWriter->writeEndElement(); // imsmd:role
        streamWriter->writeStartElement("imsmd:centity");
        streamWriter->writeTextElement("imsmd:vcard",contItem->vcard);
        streamWriter->writeEndElement(); // imsmd:centity
        streamWriter->writeEndElement(); // imsmd:contribute
        contItem = contItem->next ;
    }
}

void loWriter::writeFormatData(QXmlStreamWriter *streamWriter, FormatData *formatData) {
    while(formatData != NULL) {
        streamWriter->writeTextElement("imsmd:format",formatData->format);
        formatData = formatData->next ;
    }
}

void loWriter::writeRequirementData(QXmlStreamWriter *streamWriter, RequirementData *reqData) {
    while(reqData != NULL) {
        streamWriter->writeStartElement("imsmd:requirement");
        streamWriter->writeStartElement("imsmd:type");
        writeImsmdItem(streamWriter,reqData->type) ;
        streamWriter->writeEndElement(); // imsmd:type
        streamWriter->writeStartElement("imsmd:name");
        writeImsmdItem(streamWriter,reqData->name) ;
        streamWriter->writeEndElement(); // imsmd:name
        streamWriter->writeTextElement("imsmd:minimumversion",reqData->minimumversion);
        streamWriter->writeTextElement("imsmd:maximumversion",reqData->maximumversion);
        streamWriter->writeEndElement(); // imsmd:requirement
        reqData = reqData->next ;
    }
}
