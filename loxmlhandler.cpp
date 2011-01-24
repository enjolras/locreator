#include <QMessageBox>
#include <QObject>
#include <QList>
#include <QVariant>
#include <quazip.h>
#include <quazipfile.h>
#include "loxmlhandler.h"
#include "loitem.h"
#include "enums.h"

loXmlHandler::loXmlHandler(loItem *rootItemArg) : rootItem(rootItemArg)
{

}

bool loXmlHandler::startDocument() {

    imsmdData = new ImsmdMetadata ;

    imsmdData->general = new GeneralData ;
    imsmdData->general->title = NULL ;
    imsmdData->general->description = NULL ;

    imsmdData->lifecycle = new LifecycleData ;
    imsmdData->lifecycle->version = NULL ;
    imsmdData->lifecycle->status = NULL ;
    imsmdData->lifecycle->contribute = NULL ;

    imsmdData->technical = new TechnicalData ;
    imsmdData->technical->format = NULL ;
    imsmdData->technical->requirement = NULL ;

    imsmdData->educational = new EducationalData ;
    imsmdData->educational->interactivitytype = NULL ;
    imsmdData->educational->learningresourcetype = NULL ;
    imsmdData->educational->interactivitylevel = NULL ;
    imsmdData->educational->intendedenduserrole = NULL ;
    imsmdData->educational->context = NULL ;
    imsmdData->educational->typicalagerange = NULL ;
    imsmdData->educational->description = NULL ;

    imsmdData->rights = new RightsData ;
    imsmdData->rights->cost = NULL ;
    imsmdData->rights->copyrightandotherrestrictions = NULL ;
    imsmdData->rights->description = NULL ;

    imsmdData->classification = new ClassificationData ;
    imsmdData->classification->purpose = NULL ;
    imsmdData->classification->keyword = NULL ;

    imsmdDataList << QObject::tr("IMSMD Metadata") << ItemType::ImsmdMetadata ;


    ejmdData = new EjmdMetadata ;

    ejmdData->general = new EjmdGeneral ;
    ejmdData->general->hints = NULL ;

    ejmdData->presentation = new EjmdPresentation ;
    ejmdData->presentation->description = NULL ;

    ejmdData->solution = new EjmdSolution ;
    ejmdData->solution->next = NULL ;

    ejmdData->evaluation = NULL ;

    ejmdDataList << QObject::tr("EJMD Metadata") << ItemType::EjmdMetadata ;

    resourcesData << QObject::tr("Resources") << (int)(ItemType::Folder | ItemType::FoldResources) ;
    resourcesItem = new loItem(resourcesData,rootItem) ;

    return TRUE ;

}

bool loXmlHandler::startElement(const QString &namespaceURI,
                                const QString &localName,
                                const QString &qName,
                                const QXmlAttributes &atts) {

    Q_UNUSED(namespaceURI) ;
    Q_UNUSED(localName) ;

    context << qName ;

    if(context.at(context.size()-1) == "imsmd:langstring") {
        LangString *tmpLangString = new LangString ;
        tmpLangString->language = atts.value("xml:lang") ;
        tmpLangString->next = NULL ;
        LangString *tmpPointer = NULL ;

        if(context.at(context.size()-2) == "imsmd:title") {
            if(context.at(context.size()-3) == "imsmd:general") {
                if(imsmdData->general->title == NULL) {
                    currentLangString = imsmdData->general->title = tmpLangString ;
                } else {
                    tmpPointer = imsmdData->general->title ;
                }
            }
        } else if(context.at(context.size()-2) == "imsmd:description") {
            if(context.at(context.size()-3) == "imsmd:general") {
                if(imsmdData->general->description == NULL) {
                    currentLangString = imsmdData->general->description = tmpLangString ;
                } else {
                    tmpPointer = imsmdData->general->description ;
                }
            } else if(context.at(context.size()-3) == "imsmd:educational") {
                if(imsmdData->educational->description == NULL) {
                    currentLangString = imsmdData->educational->description = tmpLangString ;
                } else {
                    tmpPointer = imsmdData->educational->description ;
                }
            } else if(context.at(context.size()-3) == "imsmd:rights") {
                if(imsmdData->rights->description == NULL) {
                    currentLangString = imsmdData->rights->description = tmpLangString ;
                } else {
                    tmpPointer = imsmdData->educational->description ;
                }
            }
        } else if(context.at(context.size()-2) == "imsmd:version") {
            if(context.at(context.size()-3) == "imsmd:lifecycle") {
                if(imsmdData->lifecycle->version == NULL) {
                    currentLangString = imsmdData->lifecycle->version = tmpLangString ;
                } else {
                    tmpPointer = imsmdData->lifecycle->version ;
                }
            }
        } else if(context.at(context.size()-2) == "imsmd:typicalagerange") {
            if(imsmdData->educational->typicalagerange == NULL) {
                currentLangString = imsmdData->educational->typicalagerange = tmpLangString ;
            } else {
                tmpPointer = imsmdData->educational->typicalagerange ;
            }
        } else if(context.at(context.size()-2) == "imsmd:keyword") {
            if(imsmdData->classification->keyword == NULL)   {
                currentLangString = imsmdData->classification->keyword = tmpLangString ;
            } else {
                tmpPointer = imsmdData->classification->keyword ;
            }
        } else if(context.at(context.size()-2) == "imsmd:source") {
            if(context.at(context.size()-3) == "imsmd:status") {
                if(context.at(context.size()-4) == "imsmd:lifecycle") {
                    if(imsmdData->lifecycle->status->source == NULL) {
                        currentLangString = imsmdData->lifecycle->status->source = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->lifecycle->status->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:role") {
                if(context.at(context.size()-4) == "imsmd:contribute") {
                    if(context.at(context.size()-5) == "imsmd:lifecycle") {
                        if(currentContributeItem->role->source == NULL) {
                            currentLangString = currentContributeItem->role->source = tmpLangString ;
                        } else {
                            tmpPointer = currentContributeItem->role->source ;
                        }
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:type") {
                if(context.at(context.size()-4) == "imsmd:requirement") {
                    if(currentRequirementData->type->source == NULL) {
                        currentLangString = currentRequirementData->type->source = tmpLangString ;
                    } else {
                        tmpPointer = currentRequirementData->type->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:name") {
                if(context.at(context.size()-4) == "imsmd:requirement") {
                    if(currentRequirementData->name->source == NULL) {
                        currentLangString = currentRequirementData->name->source = tmpLangString ;
                    } else {
                        tmpPointer = currentRequirementData->name->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:interactivitytype") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->interactivitytype->source == NULL) {
                        currentLangString = imsmdData->educational->interactivitytype->source = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->interactivitytype->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:learningresourcetype") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->learningresourcetype->source == NULL) {
                        currentLangString = imsmdData->educational->learningresourcetype->source = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->learningresourcetype->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:interactivitylevel") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->interactivitylevel->source == NULL) {
                        currentLangString = imsmdData->educational->interactivitylevel->source = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->interactivitylevel->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:intendedenduserrole") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->intendedenduserrole->source == NULL) {
                        currentLangString = imsmdData->educational->intendedenduserrole->source = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->intendedenduserrole->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:context") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->context->source == NULL) {
                        currentLangString = imsmdData->educational->context->source = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->context->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:cost") {
                if(context.at(context.size()-4) == "imsmd:rights") {
                    if(imsmdData->rights->cost->source == NULL) {
                        currentLangString = imsmdData->rights->cost->source = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->rights->cost->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:copyrightandotherrestrictions") {
                if(context.at(context.size()-4) == "imsmd:rights") {
                    if(imsmdData->rights->copyrightandotherrestrictions->source == NULL) {
                        currentLangString = imsmdData->rights->copyrightandotherrestrictions->source = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->rights->copyrightandotherrestrictions->source ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:purpose") {
                if(context.at(context.size()-4) == "imsmd:classification") {
                    if(imsmdData->classification->purpose->source == NULL) {
                        currentLangString = imsmdData->classification->purpose->source = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->classification->purpose->source ;
                    }
                }
            }
        } else if(context.at(context.size()-2) == "imsmd:value") {
            if(context.at(context.size()-3) == "imsmd:status") {
                if(context.at(context.size()-4) == "imsmd:lifecycle") {
                    if(imsmdData->lifecycle->status->value == NULL) {
                        currentLangString = imsmdData->lifecycle->status->value = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->lifecycle->status->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:role") {
                if(context.at(context.size()-4) == "imsmd:contribute") {
                    if(context.at(context.size()-5) == "imsmd:lifecycle") {
                        if(currentContributeItem->role->value == NULL) {
                            currentLangString = currentContributeItem->role->value = tmpLangString ;
                        } else {
                            tmpPointer = currentContributeItem->role->value ;
                        }
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:type") {
                if(context.at(context.size()-4) == "imsmd:requirement") {
                    if(currentRequirementData->type->value == NULL) {
                        currentLangString = currentRequirementData->type->value = tmpLangString ;
                    } else {
                        tmpPointer = currentRequirementData->type->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:name") {
                if(context.at(context.size()-4) == "imsmd:requirement") {
                    if(currentRequirementData->name->value == NULL) {
                        currentLangString = currentRequirementData->name->value = tmpLangString ;
                    } else {
                        tmpPointer = currentRequirementData->name->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:interactivitytype") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->interactivitytype->value == NULL) {
                        currentLangString = imsmdData->educational->interactivitytype->value = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->interactivitytype->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:learningresourcetype") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->learningresourcetype->value == NULL) {
                        currentLangString = imsmdData->educational->learningresourcetype->value = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->learningresourcetype->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:interactivitylevel") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->interactivitylevel->value == NULL) {
                        currentLangString = imsmdData->educational->interactivitylevel->value = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->interactivitylevel->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:intendedenduserrole") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->intendedenduserrole->value == NULL) {
                        currentLangString = imsmdData->educational->intendedenduserrole->value = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->intendedenduserrole->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:context") {
                if(context.at(context.size()-4) == "imsmd:educational") {
                    if(imsmdData->educational->context->value == NULL) {
                        currentLangString = imsmdData->educational->context->value = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->educational->context->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:cost") {
                if(context.at(context.size()-4) == "imsmd:rights") {
                    if(imsmdData->rights->cost->value == NULL) {
                        currentLangString = imsmdData->rights->cost->value = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->rights->cost->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:copyrightandotherrestrictions") {
                if(context.at(context.size()-4) == "imsmd:rights") {
                    if(imsmdData->rights->copyrightandotherrestrictions->value == NULL) {
                        currentLangString = imsmdData->rights->copyrightandotherrestrictions->value = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->rights->copyrightandotherrestrictions->value ;
                    }
                }
            } else if(context.at(context.size()-3) == "imsmd:purpose") {
                if(context.at(context.size()-4) == "imsmd:classification") {
                    if(imsmdData->classification->purpose->value == NULL) {
                        currentLangString = imsmdData->classification->purpose->value = tmpLangString ;
                    } else {
                        tmpPointer = imsmdData->classification->purpose->value ;
                    }
                }
            }
        }

        if(tmpPointer != NULL) {
            while(tmpPointer->next != NULL) {
                tmpPointer = tmpPointer->next ;
            }
            currentLangString = tmpPointer->next = tmpLangString ;
        }
    } else if(context.at(context.size()-1) == "imsmd:status") {
        if(context.at(context.size()-2) == "imsmd:lifecycle") {
            imsmdData->lifecycle->status = new ImsmdItem ;
            imsmdData->lifecycle->status->source = NULL ;
            imsmdData->lifecycle->status->value = NULL ;
        }
    } else if(context.at(context.size()-1) == "imsmd:contribute") {
        if(context.at(context.size()-2) == "imsmd:lifecycle") {
            if(imsmdData->lifecycle->contribute == NULL) {
                imsmdData->lifecycle->contribute = currentContributeItem = new ContributeItem ;
                imsmdData->lifecycle->contribute->role = new ImsmdItem ;
                imsmdData->lifecycle->contribute->role->source = NULL ;
                imsmdData->lifecycle->contribute->role->value = NULL ;
                imsmdData->lifecycle->contribute->next = NULL ;
            } else {
                ContributeItem *tmpContributeItem = imsmdData->lifecycle->contribute ;
                while(tmpContributeItem->next != NULL) {
                    tmpContributeItem = tmpContributeItem->next ;
                }
                tmpContributeItem->next = currentContributeItem = new ContributeItem ;
                currentContributeItem->next = NULL ;
                currentContributeItem->role = NULL ;
            }
        }
    } else if(context.at(context.size()-1) == "imsmd:requirement") {
        if(context.at(context.size()-2) == "imsmd:technical") {
            if(imsmdData->technical->requirement == NULL) {
                imsmdData->technical->requirement = currentRequirementData = new RequirementData ;
            } else {
                currentRequirementData = imsmdData->technical->requirement ;
                while(currentRequirementData->next != NULL) {
                    currentRequirementData = currentRequirementData->next ;
                }
                currentRequirementData->next = new RequirementData ;
                currentRequirementData = currentRequirementData->next ;
            }
            currentRequirementData->next = NULL ;
            currentRequirementData->type = new ImsmdItem ;
            currentRequirementData->name = new ImsmdItem ;
            currentRequirementData->type->source = NULL ;
            currentRequirementData->type->value = NULL ;
            currentRequirementData->name->source = NULL ;
            currentRequirementData->name->value = NULL ;
        }
    } else if(context.at(context.size()-1) == "imsmd:format") {
        if(context.at(context.size()-2) == "imsmd:technical") {
            if(context.at(context.size()-3) == "imsmd:lom") {
                if(context.at(context.size()-4) == "metadata") {
                    if(context.at(context.size()-5) == "manifest") {
                        if(imsmdData->technical->format == NULL) {
                            imsmdData->technical->format = currentFormatData = new FormatData ;
                        } else {
                            currentFormatData = imsmdData->technical->format ;
                            while(currentFormatData->next != NULL) {
                                currentFormatData = currentFormatData->next ;
                            }
                            currentFormatData->next = new FormatData ;
                            currentFormatData = currentFormatData->next ;
                        }
                        currentFormatData->next = NULL ;
                    }
                }
            }
        }
    } else if(context.at(context.size()-1) == "imsmd:interactivitytype") {
        imsmdData->educational->interactivitytype = new ImsmdItem ;
        imsmdData->educational->interactivitytype->source = NULL ;
        imsmdData->educational->interactivitytype->value = NULL ;
    } else if(context.at(context.size()-1) == "imsmd:learningresourcetype") {
        imsmdData->educational->learningresourcetype = new ImsmdItem ;
        imsmdData->educational->learningresourcetype->source = NULL ;
        imsmdData->educational->learningresourcetype->value = NULL ;
    } else if(context.at(context.size()-1) == "imsmd:interactivitylevel") {
        imsmdData->educational->interactivitylevel = new ImsmdItem ;
        imsmdData->educational->interactivitylevel->source = NULL ;
        imsmdData->educational->interactivitylevel->value = NULL ;
    } else if(context.at(context.size()-1) == "imsmd:intendedenduserrole") {
        imsmdData->educational->intendedenduserrole = new ImsmdItem ;
        imsmdData->educational->intendedenduserrole->source = NULL ;
        imsmdData->educational->intendedenduserrole->value = NULL ;
    } else if(context.at(context.size()-1) == "imsmd:context") {
        imsmdData->educational->context = new ImsmdItem ;
        imsmdData->educational->context->source = NULL ;
        imsmdData->educational->context->value = NULL ;
    } else if(context.at(context.size()-1) == "imsmd:cost") {
        imsmdData->rights->cost = new ImsmdItem ;
        imsmdData->rights->cost->source = NULL ;
        imsmdData->rights->cost->value = NULL ;
    } else if(context.at(context.size()-1) == "imsmd:copyrightandotherrestrictions") {
        imsmdData->rights->copyrightandotherrestrictions = new ImsmdItem ;
        imsmdData->rights->copyrightandotherrestrictions->source = NULL ;
        imsmdData->rights->copyrightandotherrestrictions->value = NULL ;
    } else if(context.at(context.size()-1) == "imsmd:purpose") {
        imsmdData->classification->purpose = new ImsmdItem ;
        imsmdData->classification->purpose->source = NULL ;
        imsmdData->classification->purpose->value = NULL ;
    } else if(context.at(context.size()-1) == "resource") {
        QList<QVariant> tmpResource ;
        tmpResource << atts.value("identifier") ;
        if(atts.value("type") == "input")
            tmpResource << (int)(ItemType::Resource | ItemType::ResInput) ;
        else if(atts.value("type") == "output")
            tmpResource << (int)(ItemType::Resource | ItemType::ResOutput) ;
        else if(atts.value("type") == "solution")
            tmpResource << (int)(ItemType::Resource | ItemType::ResSolution) ;
        else if(atts.value("type") == "webcontent")
            tmpResource << (int)(ItemType::Resource | ItemType::ResWebcontent) << atts.value("href");
        else
            tmpResource << (int)(ItemType::Unknown) ;

        loItem *tmpItem = new loItem(tmpResource,resourcesItem) ;
        currentItem = tmpItem ;
        resourcesItem->appendChild(tmpItem) ;
    } else if(context.at(context.size()-1) == "ejmd:hints") {
        ejmdData->general->hints = new EjmdGeneralHints ;
        ejmdData->general->hints->submission = NULL ;
        ejmdData->general->hints->compilation = NULL ;
        ejmdData->general->hints->execution = NULL ;
    } else if(context.at(context.size()-1) == "ejmd:submission") {
        ejmdData->general->hints->submission = new EjmdGeneralHintsSubmission ;
        ejmdData->general->hints->submission->timesolve = atts.value("ejmd:time-solve") ;
        ejmdData->general->hints->submission->timesubmit = atts.value("ejmd:time-submit") ;
        ejmdData->general->hints->submission->attempts = atts.value("ejmd:attempts").toInt() ;
        ejmdData->general->hints->submission->codelines = atts.value("ejmd:code-lines").toInt() ;
        ejmdData->general->hints->submission->length = atts.value("ejmd:length").toInt() ;
    } else if(context.at(context.size()-1) == "ejmd:compilation") {
        ejmdData->general->hints->compilation = new EjmdGeneralHintsCompilation ;
        ejmdData->general->hints->compilation->time = atts.value("ejmd:time") ;
        ejmdData->general->hints->compilation->size = atts.value("ejmd:size").toInt() ;
    } else if(context.at(context.size()-1) == "ejmd:execution") {
        ejmdData->general->hints->execution = new EjmdGeneralHintsExecution ;
        ejmdData->general->hints->execution->time = atts.value("ejmd:time") ;
    } else if(context.at(context.size()-1) == "ejmd:evaluation") {

        EjmdEvaluation *tmpEvaluationPointer = NULL ;

        if(ejmdData->evaluation == NULL) {
            ejmdData->evaluation = tmpEvaluationPointer = new EjmdEvaluation ;
            ejmdData->evaluation->tests = new EjmdEvaluationTests ;
            ejmdData->evaluation->tests->testFiles = NULL ;
            ejmdData->evaluation->next = NULL ;
        } else {
            tmpEvaluationPointer = ejmdData->evaluation ;
            while(tmpEvaluationPointer->next != NULL) {
                tmpEvaluationPointer = tmpEvaluationPointer->next ;
            }
            tmpEvaluationPointer->next = new EjmdEvaluation ;
            tmpEvaluationPointer = tmpEvaluationPointer->next ;
            tmpEvaluationPointer->tests = new EjmdEvaluationTests ;
            tmpEvaluationPointer->tests->testFiles = NULL ;
            tmpEvaluationPointer->next = NULL ;
        }

        tmpEvaluationPointer->evaluationModel = atts.value("ejmd:evaluationModel") ;
        tmpEvaluationPointer->evaluationModelVersion = atts.value("ejmd:evaluationModelVersion").toInt() ;

    } else if(context.at(context.size()-1) == "ejmd:testFiles") {
        EjmdEvaluation *tmpEvaluationPointer = ejmdData->evaluation ;
        while(tmpEvaluationPointer->next != NULL) tmpEvaluationPointer = tmpEvaluationPointer->next ;

        EjmdEvaluationTestsTestFiles *tmpTestFiles = NULL ;
        if(tmpEvaluationPointer->tests->testFiles == NULL) {
            tmpEvaluationPointer->tests->testFiles = tmpTestFiles = new EjmdEvaluationTestsTestFiles ;
            tmpTestFiles->next = NULL ;
        } else {
            tmpTestFiles = tmpEvaluationPointer->tests->testFiles ;
            while(tmpTestFiles->next != NULL) {
                tmpTestFiles = tmpTestFiles->next ;
            }
            tmpTestFiles->next = new EjmdEvaluationTestsTestFiles ;
            tmpTestFiles = tmpTestFiles->next ;
            tmpTestFiles->next = NULL ;
        }

        tmpTestFiles->arguments = atts.value("ejmd:arguments") ;
        tmpTestFiles->valorization = atts.value("ejmd:valorization").toInt() ;

    } else if(context.at(context.size()-1) == "ejmd:input") {
        EjmdEvaluation *tmpEvaluationPointer = ejmdData->evaluation ;
        while(tmpEvaluationPointer->next != NULL) tmpEvaluationPointer = tmpEvaluationPointer->next ;

        EjmdEvaluationTestsTestFiles *tmpTestFiles = tmpEvaluationPointer->tests->testFiles ;
        while(tmpTestFiles->next != NULL) tmpTestFiles = tmpTestFiles->next ;

        tmpTestFiles->inputResource = atts.value("ejmd:resource") ;
    } else if(context.at(context.size()-1) == "ejmd:output") {
        EjmdEvaluation *tmpEvaluationPointer = ejmdData->evaluation ;
        while(tmpEvaluationPointer->next != NULL) tmpEvaluationPointer = tmpEvaluationPointer->next ;

        EjmdEvaluationTestsTestFiles *tmpTestFiles = tmpEvaluationPointer->tests->testFiles ;
        while(tmpTestFiles->next != NULL) tmpTestFiles = tmpTestFiles->next ;

        tmpTestFiles->outputResource = atts.value("ejmd:resource") ;
    } else if(context.at(context.size()-1) == "file") {
        if(context.at(context.size()-2) == "resource") {
            QList<QVariant> tmpResource ;
            tmpResource << atts.value("href") ;

            QString extension = atts.value("href").split(".").at(1) ;

            if(extension == "jpg" || extension == "png" || extension == "gif")
                tmpResource << (int)(ItemType::File | ItemType::FileImage) ;
            else if(extension == "html" || extension == "htm")
                tmpResource << (int)(ItemType::File | ItemType::FileHtml) ;
            else if(extension == "txt" || extension == "cpp")
                tmpResource << (int)(ItemType::File | ItemType::FileText) ;
            else
                tmpResource << (int)(ItemType::File | ItemType::FileGeneric) ;

            QuaZip *tmpFile = new QuaZip(*filePath) ;
            tmpFile->open(QuaZip::mdUnzip) ;
            tmpFile->setCurrentFile(atts.value("href")) ;

            QuaZipFile resourceFile(tmpFile) ;
            resourceFile.open(QIODevice::ReadOnly) ;
            tmpResource << resourceFile.readAll() ;
            resourceFile.close();

            tmpFile->close();
            delete tmpFile ;

            loItem *tmpItem = new loItem(tmpResource,currentItem) ;
            currentItem->appendChild(tmpItem) ;
        }
    } else if(context.at(context.size()-1) == "ejmd:description") {
        if(context.at(context.size()-2) == "ejmd:presentation") {
            ejmdData->presentation->description = new EjmdPresentationDescription ;
            ejmdData->presentation->description->resource = atts.value("ejmd:resource") ;
        }
    } else if(context.at(context.size()-1) == "ejmd:solution") {
        ejmdData->solution->resource = atts.value("ejmd:resource") ;
        ejmdData->solution->compilationLine = atts.value("ejmd:compilationLine") ;
        ejmdData->solution->executionLine = atts.value("ejmd:executionLine") ;
        ejmdData->solution->language = atts.value("ejmd:language") ;
        ejmdData->solution->languageVersion = atts.value("ejmd:languageVersion") ;

    }

    return TRUE ;

}

bool loXmlHandler::endElement(const QString &namespaceURI,
                              const QString &localName,
                              const QString &qName) {

    Q_UNUSED(namespaceURI) ;
    Q_UNUSED(localName) ;
    Q_UNUSED(qName) ;

    if(context.at(context.size()-1) == "imsmd:lom") {
        if(context.at(context.size()-2) == "metadata") {
            if(context.at(context.size()-3) == "manifest") {
                imsmdDataList << qVariantFromValue(*imsmdData) ;
                rootItem->appendChild(new loItem(imsmdDataList,rootItem)) ;
            }
        }
    } else if(context.at(context.size()-1) == "ejmd:metadata") {
        ejmdDataList << qVariantFromValue(*ejmdData) ;
        rootItem->appendChild(new loItem(ejmdDataList,rootItem));
    } else if(context.at(context.size()-1) == "resources") {
        rootItem->appendChild(resourcesItem) ;
    }

    context.removeLast();

    return TRUE ;
}

bool loXmlHandler::characters(const QString &ch) {

    if(context.at(context.size()-1) == "imsmd:identifier") {
        imsmdData->general->identifier = ch ;
    } else if(context.at(context.size()-1) == "imsmd:language") {
        if(context.at(context.size()-2) == "imsmd:general") {
            if(context.at(context.size()-3) == "imsmd:lom") {
                if(context.at(context.size()-4) == "metadata") {
                    if(context.at(context.size()-5) == "manifest") {
                        imsmdData->general->language = ch ;
                    }
                }
            }
        } else if(context.at(context.size()-2) == "imsmd:educational") {
            imsmdData->educational->language = ch ;
        }
    } else if(context.at(context.size()-1) == "imsmd:langstring") {
        currentLangString->content = ch ;
        currentLangString = new LangString ;
    } else if(context.at(context.size()-1) == "imsmd:vcard") {
        currentContributeItem->vcard = ch ;
    } else if(context.at(context.size()-1) == "imsmd:minimumversion") {
        currentRequirementData->minimumversion = ch ;
    } else if(context.at(context.size()-1) == "imsmd:maximumversion") {
        currentRequirementData->maximumversion = ch ;
    } else if(context.at(context.size()-1) == "imsmd:format") {
        if(context.at(context.size()-3) == "imsmd:lom") {
            if(context.at(context.size()-4) == "metadata") {
                if(context.at(context.size()-5) == "manifest") {
                    currentFormatData->format = ch ;
                }
            }
        }
    } else if(context.at(context.size()-1) == "imsmd:datetime") {
        imsmdData->educational->typicallearningtime = ch ;
    }

    return TRUE ;

}

void loXmlHandler::setFilePath(QString &filePathArg) {
    filePath = &filePathArg ;
}
