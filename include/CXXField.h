//
// Created by nikitas on 12.03.16.
//

#ifndef DECCLASS_CXXFIELD_H
#define DECCLASS_CXXFIELD_H

struct CXXField {
    std::string type;
    std::string name;
    bool simpleType;
};

inline std::ostream & operator<<(std::ostream & stream, CXXField &cxxField)
{
    return stream << "    " << cxxField.type << ' ' << cxxField.name << ';' << std::endl;
}

#endif //DECCLASS_CXXFIELD_H