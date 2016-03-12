//
// Created by nikitas on 12.03.16.
//

#ifndef DECCLASS_STRUCTEXPANEDER_H
#define DECCLASS_STRUCTEXPANEDER_H

#define DEBUG_EXPANDER

#include "FieldFinder.h"

class StructExpander {
public:
    void expand(const std::string &file, const std::string &structName);
    void print(std::ostream & stream);

    std::vector<CXXField> getSimpleStruct(const std::vector<CXXField> &fields);



#ifdef DEBUG_EXPANDER
    void debug_print(std::ostream & stream);
#endif

private:

    std::vector<CXXField> __recur_search(const CXXField &field, std::string base);

    std::map < std::string, std::vector<CXXField> > m_classes;
    std::string m_file;
    std::string m_structName;

};


#endif //DECCLASS_STRUCTEXPANEDER_H
