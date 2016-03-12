//
// Created by nikitas on 12.03.16.
//

#include <sstream>

#include "FieldFinder.h"

std::set<std::string> FieldFinder::m_keywords{
        "class",
        "struct"
};

FieldFinder::FieldFinder(std::map<std::string, std::vector<CXXField> > &classes) :
        m_classes(classes) { }

void FieldFinder::__del_keyword(std::string &str) {
    std::stringstream ss(str);
    std::string fstWord;
    ss >> fstWord;
    if (m_keywords.find(fstWord) != m_keywords.end())
        str = str.substr(fstWord.length() + 1);
}


std::vector<CXXField> FieldFinder::__get_fields(clang::CXXRecordDecl *decl) {
    std::vector<CXXField> fields;
    auto it = decl->field_begin();
    for (; it != decl->field_end(); ++it) {
        CXXField field;

        if (it->getType().getTypePtr()->isConstantArrayType()) {
            auto arrayType =
                    clang::dyn_cast<clang::ConstantArrayType>(it->getType().getTypePtr());
            //че это? почему нельзя было сразу toInt?)
            int count = (int) (arrayType->getSize()).roundToDouble();
            for (int i = 0; i < count; i++) {
                field.name = it->getName().str() + "_" + std::to_string(i);
                field.type = arrayType->getElementType().getCanonicalType().
                        getCanonicalType().getUnqualifiedType().getAsString();
                field.simpleType = arrayType->getElementType().isCanonical();
                if (!field.simpleType)
                    __del_keyword(field.type);
                fields.push_back(field);
            }
        }
        else {
            field.type = it->getType().getCanonicalType().getUnqualifiedType().getAsString();
            field.name = it->getName().str();
            field.simpleType = it->getType().isCanonical();
            if (!field.simpleType)
                __del_keyword(field.type);

            fields.push_back(field);
        }
    }
    return fields;
}


bool FieldFinder::VisitCXXRecordDecl(clang::CXXRecordDecl *decl) {
    std::string name = decl->getCanonicalDecl()->getQualifiedNameAsString();
    m_classes[name] = __get_fields(decl);

    return true;
}
