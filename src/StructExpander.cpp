//
// Created by nikitas on 12.03.16.
//


#include <fstream>
#include <iostream>

#include "FieldFinderAction.h"
#include "StructExpander.h"


std::vector<CXXField> StructExpander::__recur_search(const CXXField &field, std::string base)
{
    std::vector<CXXField> fields;
    if (m_classes.find(field.type) == m_classes.end())
        return fields;

    base += field.name + "_";

    for (auto f : m_classes[field.type]) {
        if (f.simpleType) {
            f.name.insert(0, base);
            fields.push_back(f);
        }
        else {
            std::vector<CXXField> findCXXField = __recur_search(f, base);
            fields.insert(fields.end(), findCXXField.begin(), findCXXField.end());
        }
    }

    return fields;
}

std::vector<CXXField> StructExpander::getSimpleStruct(const std::vector<CXXField> &fields)
{
    std::vector<CXXField> res;
    for (auto f : fields) {
        if (f.simpleType) res.push_back(f);
        else  {
            std::vector<CXXField> F = __recur_search(f, "");
            res.insert(res.end(), F.begin(), F.end());
        }
    }
    return res;
}


void StructExpander::print(std::ostream &stream) {
    stream << "#pragma once\n#pragma pack(push,1))\n";
    stream << "struct " + m_structName + "_plain {\n";
    for (auto &f : getSimpleStruct(m_classes[m_structName])) {
        stream << f;
    }
    stream << "}; //auto generate\n#pragma pack(pop)";

}

void StructExpander::expand(const std::string &file, const std::string &structName) {
    m_structName = structName;
    std::ifstream codeFile(file, std::ifstream::in);
    if (!codeFile) {
        std::cerr << "bad file\n";
        return;
    }

    std::string line, code;
    while (std::getline(codeFile, line))
        code += line + "\n";

    clang::tooling::runToolOnCode(new FindFielderAction(m_classes), code);
}

#ifdef DEBUG_EXPANDER
void StructExpander::debug_print(std::ostream &stream)
{
    for (auto _class: m_classes) {
        std::cout << _class.first << ";\n";
        for (auto field : _class.second)
            std::cout << "     (" << field.name << " -> " << field.type << ")\n";
    }

}
#endif
