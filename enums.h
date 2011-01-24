#ifndef ENUMS_H
#define ENUMS_H

class ItemType {
public:
    enum Type {
        Unknown         = 0x00,
        Folder          = 0x01,
        General         = 0x02,
        Presentation    = 0x04,
        Solution        = 0x08,
        EvalModel       = 0x10,
        Resource        = 0x20,
        File            = 0x40,
        ResInput        = 0x80,
        ResOutput       = 0x100,
        ResSolution     = 0x200,
        ResWebcontent   = 0x400,
        FileGeneric     = 0x800,
        FileHtml        = 0x1000,
        FileImage       = 0x2000,
        FileText        = 0x4000,
        FoldResources   = 0x8000,
        ImsmdMetadata   = 0x10000,
        EjmdMetadata    = 0x20000
                      } ;
    Q_DECLARE_FLAGS(ItemTypes,Type)
} ;

Q_DECLARE_OPERATORS_FOR_FLAGS(ItemType::ItemTypes)

#endif // ENUMS_H
