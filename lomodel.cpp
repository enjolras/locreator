#include <QStringList>
#include <QBuffer>
#include <quazip.h>
#include <quazipfile.h>
#include <QMessageBox>
#include <QFileInfo>
#include <QXmlQuery>
#include <QIcon>
#include <QXmlSimpleReader>
#include <QFont>
#include <QFlags>
#include "loxmlhandler.h"
#include "loitem.h"
#include "lomodel.h"
#include "enums.h"

loModel::loModel(QObject *parent) : QAbstractItemModel(parent)
{

}

loModel::~loModel()
 {
     loFile->close();
     delete rootItem;
 }

bool loModel::setFile(const QFileInfo *file) {

    filePath = file->absoluteFilePath() ;
    loFile = new QuaZip(filePath) ;

    if(!loFile->open(QuaZip::mdUnzip)) {
        QMessageBox::critical(0,tr("File Error"),tr("It is not a ZIP file.")) ;
        delete loFile ;
        this->deleteLater() ;
        return FALSE ;
    }

    if(!loFile->setCurrentFile("imsmanifest.xml")) {
         QMessageBox::critical(0,tr("File Error"),tr("The file is not a valid LO.")) ;
         delete loFile ;
         this->deleteLater();
         return FALSE ;
    }

    QuaZipFile manifestFile(loFile) ;

    QList<QVariant> rootData ;
    rootData << tr("EduJudge Learning Object") ;
    rootItem = new loItem(rootData) ;

    setupModelData(&manifestFile, rootItem) ;

    return TRUE ;

}

 QModelIndex loModel::index(int row, int column, const QModelIndex &parent)
             const
 {
     if (!hasIndex(row, column, parent))
         return QModelIndex();

     loItem *parentItem;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<loItem*>(parent.internalPointer());

     loItem *childItem = parentItem->child(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();
 }

  QModelIndex loModel::parent(const QModelIndex &index) const
 {
     if (!index.isValid())
         return QModelIndex();

     loItem *childItem = static_cast<loItem*>(index.internalPointer());
     loItem *parentItem = childItem->parent();

     if (parentItem == rootItem)
         return QModelIndex();

     return createIndex(parentItem->row(), 0, parentItem);
 }

 int loModel::rowCount(const QModelIndex &parent) const
 {
     loItem *parentItem;
     if (parent.column() > 0)
         return 0;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<loItem*>(parent.internalPointer());

     return parentItem->childCount();
 }

int loModel::columnCount(const QModelIndex &parent) const
 {
     if (parent.isValid())
         return static_cast<loItem*>(parent.internalPointer())->columnCount();
     else
         return rootItem->columnCount();
 }

QVariant loModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     loItem *item = static_cast<loItem*>(index.internalPointer());

     QFlags<ItemType::ItemTypes> itemType(item->data(1).toInt()) ;

     if (role == Qt::DisplayRole) {
         return item->data(index.column());
     } else if (role == Qt::FontRole) {
         if(itemType.testFlag(ItemType::FileHtml)) {
             if(item->parent()->data(2).toString() == item->data(0).toString()) {
                 QFont boldFont ;
                 boldFont.setBold(TRUE);
                 return boldFont ;
             } else {
                 return QVariant() ;
             }
         } else {
             return QVariant() ;
         }
     } else if (role == Qt::UserRole + 1) {
         return item->data(1) ;
     } else if (role == Qt::UserRole) {
         return item->data(2) ;
     } else if (role == Qt::UserRole + 2) {
        return item->childCount() ;
     } else if (role == Qt::DecorationRole) {
         if(itemType.testFlag(ItemType::Resource)) {
             if(itemType.testFlag(ItemType::ResInput)) {
                 return QIcon(":/icons/input.png") ;
             } else if(itemType.testFlag(ItemType::ResOutput)) {
                 return QIcon(":/icons/output.png") ;
             } else if(itemType.testFlag(ItemType::ResWebcontent)) {
                 return QIcon(":/icons/webcontent.png") ;
             } else if(itemType.testFlag(ItemType::ResSolution)) {
                 return QIcon(":/icons/solution.png") ;
             }
         } else if(itemType.testFlag(ItemType::File)) {
             if(itemType.testFlag(ItemType::FileHtml)) {
                 return QIcon(":/icons/filehtml.png") ;
             } else if(itemType.testFlag(ItemType::FileImage)) {
                 return QIcon(":/icons/fileimage.png") ;
             } else if(itemType.testFlag(ItemType::FileText)) {
                 return QIcon(":/icons/filetext.png") ;
             }
         } else if(itemType.testFlag(ItemType::Folder)) {
             return QIcon(":/icons/folder.png") ;
         } else if(itemType.testFlag(ItemType::EvalModel)) {
             return QIcon(":/icons/evalmodel.png") ;
         } else {
             return QIcon(":/icons/unknown.png") ;
         }

     }
     return QVariant() ;

 }

Qt::ItemFlags loModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return 0;

     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }

QVariant loModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
         return rootItem->data(section);

     return QVariant();
 }

void loModel::setupModelData(QIODevice *manifest,loItem *parent) {

    Q_UNUSED(parent) ;

    QXmlSimpleReader xmlReader ;
    QXmlInputSource *source = new QXmlInputSource(manifest) ;

    loXmlHandler *handler = new loXmlHandler(rootItem) ;
    handler->setFilePath(filePath);
    xmlReader.setContentHandler(handler) ;
    xmlReader.parse(source) ;

}
