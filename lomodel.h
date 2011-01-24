#ifndef LOMODEL_H
#define LOMODEL_H

#include <QFlags>
#include <QObject>
#include <QAbstractItemModel>
#include "loitem.h"

struct LangString {
    QString content ;
    QString language ;
    LangString *next ;
} ;

struct ImsmdItem {
    LangString *source ;
    LangString *value ;
} ;

struct ContributeItem {
   ImsmdItem *role ;
   QString vcard ;
   ContributeItem *next ;
} ;

struct FormatData {
    QString format ;
    FormatData *next ;
} ;

struct RequirementData {
    ImsmdItem *type ;
    ImsmdItem *name ;
    QString minimumversion ;
    QString maximumversion ;
    RequirementData *next ;
} ;

struct GeneralData {
    QString identifier ;
    QString language ;
    LangString *title ;
    LangString *description ;
} ;

struct LifecycleData {
    LangString *version ;
    ImsmdItem *status ;
    ContributeItem *contribute ;
} ;

struct TechnicalData {
    FormatData *format ;
    RequirementData *requirement ;
} ;

struct EducationalData {
    ImsmdItem *interactivitytype ;
    ImsmdItem *learningresourcetype ;
    ImsmdItem *interactivitylevel ;
    ImsmdItem *intendedenduserrole ;
    ImsmdItem *context ;
    LangString *typicalagerange ;
    QString typicallearningtime ;
    LangString *description ;
    QString language ;
} ;

struct RightsData {
    ImsmdItem *cost ;
    ImsmdItem *copyrightandotherrestrictions ;
    LangString *description ;
} ;

struct ClassificationData {
    ImsmdItem *purpose ;
    LangString *keyword ;
} ;

struct ImsmdMetadata {
    GeneralData *general ;
    LifecycleData *lifecycle ;
    TechnicalData *technical ;
    EducationalData *educational ;
    RightsData *rights ;
    ClassificationData *classification ;
} ;

Q_DECLARE_METATYPE(ImsmdMetadata) ;

struct TestCase {
    QString inputRes ;
    QString outputRes ;
    int valorization ;
    TestCase *next ;
};

Q_DECLARE_METATYPE(TestCase) ;

struct EjmdGeneralHintsSubmission {
    QString timesolve ;
    QString timesubmit ;
    int attempts ;
    int codelines ;
    int length ;
};

struct EjmdGeneralHintsCompilation {
    QString time ;
    int size ;
};

struct EjmdGeneralHintsExecution {
    QString time ;
};

struct EjmdGeneralHints {
    EjmdGeneralHintsSubmission *submission ;
    EjmdGeneralHintsCompilation *compilation ;
    EjmdGeneralHintsExecution *execution ;
};

struct EjmdGeneral {
    EjmdGeneralHints *hints ;
};

struct EjmdPresentationDescription {
    QString resource ;
};

struct EjmdPresentation {
    EjmdPresentationDescription *description ;
};

struct EjmdSolution {
    QString resource ;
    QString compilationLine ;
    QString executionLine ;
    QString language ;
    QString languageVersion ;
    EjmdSolution *next ;
};

struct EjmdEvaluationTestsTestFiles {
    QString arguments ;
    int valorization ;
    QString inputResource ;
    QString outputResource ;
    EjmdEvaluationTestsTestFiles *next ;
};

struct EjmdEvaluationTests {
    EjmdEvaluationTestsTestFiles *testFiles ;
};

struct EjmdEvaluation {
    QString evaluationModel ;
    int evaluationModelVersion ;
    EjmdEvaluationTests *tests ;
    EjmdEvaluation *next ;
};

struct EjmdMetadata {
    EjmdGeneral *general ;
    EjmdPresentation *presentation ;
    EjmdSolution *solution ;
    EjmdEvaluation *evaluation ;
};

Q_DECLARE_METATYPE(EjmdMetadata) ;

class QFileInfo ;
class QBuffer ;
class QuaZip ;

class loModel : public QAbstractItemModel {

        Q_OBJECT

public:
    loModel(QObject *parent=0);
    ~loModel() ;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool setFile(const QFileInfo *file) ;

protected:
    QString filePath ;

private:
     void setupModelData(QIODevice *manifest, loItem *parent);
     loItem *rootItem ;
     QuaZip *loFile ;
};

#endif // LOMODEL_H
