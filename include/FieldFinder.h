//
// Created by nikitas on 12.03.16.
//

#ifndef DECCLASS_FIELDFINDER_H
#define DECCLASS_FIELDFINDER_H

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Tooling/Tooling.h"

#include "CXXField.h"

class FieldFinder : public clang::RecursiveASTVisitor<FieldFinder> {
public:
    FieldFinder(std::map < std::string, std::vector<CXXField> > &classes);

    bool VisitCXXRecordDecl(clang::CXXRecordDecl *decl);

private:
    std::vector<CXXField> __get_fields(clang::CXXRecordDecl *decl);
    void __del_keyword(std::string &str);

    static std::set<std::string> m_keywords;
    std::map < std::string, std::vector<CXXField> > &m_classes;

    CXXField &getArrayField(std::vector<CXXField> &fields, const clang::RecordDecl::field_iterator &it, CXXField &field);

    void __anon_st_or_un_worker(const clang::CXXRecordDecl *decl, std::vector<CXXField> &fields,
                                clang::RecordDecl::field_iterator &it, const std::string &base) const;

    std::string &__replaceAnonUoS(std::string &name) const;
};


#endif //DECCLASS_FIELDFINDER_H
