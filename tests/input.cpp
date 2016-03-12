
#include "/home/nikitas/Repos/decclass/tests/vector3f.h"


enum {
    N = 2
};

const int num = 3;

// !!! always #pragma pack(1)

// model.h

int main() {
    struct randomStr {
        int a;
        int b;
    };
}

struct model {

    core::vector3f pos[3];
    core::vector3f pos2[num];
    core::vector3f orient;
    color::Colors *c;
    //std::pair<core::vector3f, int> pair;
    int *t;
    const color::Colors e;
    struct view {
        view *self;
        core::vector3f abc;
    } viewM,viewP[N+3];
};




//
//    Parser(
//    "model.h", //in file
//    "model", // in classname
//    [def=0]"autogenerate_model_plain.h" // out file
//    [def=0]"model_plain", // out classname
//    );
//
//// model_plain.h
//// autogenerated file
//#pragma once
//#pragma pack(push,1)
struct model_plain {
    // pos[0]
    float pos_0_x;
    float pos_0_y;
    float pos_0_z;
    //
    float pos_1_x;
    float pos_1_y;
    float pos_1_z;
    // ...
 //   viewM_abc_x;
};
//#pragma pack(pop)
