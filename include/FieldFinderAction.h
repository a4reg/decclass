//
// Created by nikitas on 12.03.16.
//

#ifndef DECCLASS_FIELDFINDERACTION_H
#define DECCLASS_FIELDFINDERACTION_H

#include "Consumer.h"

class FindFielderAction : public clang::ASTFrontendAction {
public:
    FindFielderAction(std::map < std::string, std::vector<CXXField> > &classes)
            : m_classes(classes) { }
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
        return std::unique_ptr<clang::ASTConsumer>(
                new Consumer(m_classes));
    }

private:
    std::map < std::string, std::vector<CXXField> > &m_classes;
};


#endif //DECCLASS_FIELDFINDERACTION_H
