//
// Created by nikitas on 12.03.16.
//

#ifndef DECCLASS_CONSUMER_H
#define DECCLASS_CONSUMER_H

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Tooling/Tooling.h"

#include "FieldFinder.h"

class Consumer : public clang::ASTConsumer {
public:
    Consumer(std::map < std::string, std::vector<CXXField> > &classes) : Visitor(classes) {}
    virtual void HandleTranslationUnit(clang::ASTContext &Context) {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }

private:
    FieldFinder Visitor;
};


#endif //DECCLASS_CONSUMER_H
