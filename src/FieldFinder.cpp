//
// Created by nikitas on 12.03.16.
//

#include <sstream>
#include <iostream>

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
    std::string base = decl->getCanonicalDecl()->getQualifiedNameAsString();
    if (decl->isAnonymousStructOrUnion())
    {
        std::cout << decl->getUnderlyingDecl()->getNameAsString() << std::endl;
        __anon_st_or_un_worker(decl, fields, it, base);
        return fields;
    }


    for (; it != decl->field_end(); ++it) {
        CXXField field;

        if (it->isAnonymousStructOrUnion()) {
            field.name = it->getName().str();
            field.simpleType = false;
            std::string type_ = decl->getCanonicalDecl()->getQualifiedNameAsString();
            field.type = __replaceAnonUoS(type_) + "::__anoninos_union_or_struct__";
            fields.push_back(field);
            continue;
        }

        if (it->getType().getTypePtr()->isConstantArrayType()) {
            field = getArrayField(fields, it, field, decl->getASTContext());
        }
        else {
            field.type = it->getType().getCanonicalType().getUnqualifiedType().getAsString();
            field.name = it->getName().str();
            field.simpleType = it->getType().isTrivialType(decl->getASTContext());
            if (!field.simpleType)
                __del_keyword(field.type);

            fields.push_back(field);
        }
    }
    return fields;
}

void FieldFinder::__anon_st_or_un_worker(const clang::CXXRecordDecl *decl, std::vector<CXXField> &fields,
                                         clang::RecordDecl::field_iterator &it2, const std::string &base) const {
    long long max_sizeof = 0;
    clang::FieldDecl *max_sizeof_decl = nullptr;
    auto it = decl->field_begin();
    for (; it != decl->field_end(); ++it) {
            auto sizeof_ = decl->getASTContext().getTypeSizeInChars(it->getType());
//            std::cout << it->getCanonicalDecl()->getType().getAsString() << std::endl;
            CXXField field;
            field.name = it->getNameAsString();
            if ( max_sizeof < sizeof_.getQuantity() ) {
                max_sizeof_decl = it->getCanonicalDecl();
                max_sizeof = sizeof_.getQuantity();
            }
        }
        if (max_sizeof_decl == nullptr) return;
        if (max_sizeof_decl->getType().getTypePtr()->isConstantArrayType())
        {
            auto arrayType = llvm::dyn_cast<clang::ConstantArrayType>(max_sizeof_decl->getType().getTypePtr());
            int count = (int) (arrayType->getSize()).roundToDouble();

            for (int i = 0; i < count; i++)
            {
                CXXField cxxField;
                cxxField.name = max_sizeof_decl->getNameAsString() + "_" + std::__1::to_string(i);
                cxxField.simpleType = true;

                std::string type_ = arrayType->getElementType().getCanonicalType().
                        getCanonicalType().getUnqualifiedType().getAsString();
                cxxField.type = __replaceAnonUoS(type_);
                fields.push_back(cxxField);
            }
        }
}

CXXField &FieldFinder::getArrayField(std::vector<CXXField> &fields, const clang::RecordDecl::field_iterator &it,
                                     CXXField &field, const clang::ASTContext &context) {
    auto arrayType = llvm::dyn_cast<clang::ConstantArrayType>(it->getType().getTypePtr());
    //че это? почему нельзя было сразу toInt?)
    int count = (int) (arrayType->getSize()).roundToDouble();
    for (int i = 0; i < count; i++) {
                field.name = it->getName().str() + "_" + std::__1::to_string(i);
                field.type = arrayType->getElementType().getCanonicalType().
                        getCanonicalType().getUnqualifiedType().getAsString();
                field.simpleType = arrayType->getElementType().isTrivialType(
                        const_cast<clang::ASTContext&>(context));
                if (!field.simpleType)
                    __del_keyword(field.type);
                fields.push_back(field);
            }
    return field;
}


bool FieldFinder::VisitCXXRecordDecl(clang::CXXRecordDecl *decl) {

    std::string name = decl->getCanonicalDecl()->getQualifiedNameAsString();

    name = __replaceAnonUoS(name);

    m_classes[name] = __get_fields(decl);

    return true;
}

std::string &FieldFinder::__replaceAnonUoS(std::string &name) const {
    while (true)
    {
        size_t pos = 0; bool exit = true;
        if ((pos = name.find("(anonymous)")) != std::string::npos)
        {
            std::string __st = (!pos) ? "" : name.substr(0, pos);
            name = __st + "__anoninos_union_or_struct__" + name.substr(pos + 11), exit = false;
        }

        if ((pos = name.find("(anonymous union)")) !=std::string::npos)
        {
            std::string __st = (!pos) ? "" : name.substr(0, pos);
            name = __st + "__anoninos_union_or_struct__" + name.substr(pos + 17), exit = false;
        }
        if (exit) break;
    }
    return name;
}
