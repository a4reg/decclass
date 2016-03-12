# decclass
Tool for decomposition C++ class/stuct to simple types using Clang.

Usage: 

decclass <path-to-cxxfile> <aim-struct>

Example:

```c++
#include "../core/vector3f.h"

enum { N = 2 };

struct model {
    core::vector3f pos[3];
  
    core::vector3f orient;
   
    int t;
    
    struct view {
        core::vector3f abc;
    } viewM,viewP[N+3];
};

//vector3f.h
namespace core {
    class vector3f {
    public:
        vector3f();

        vector3f operator+(vector3f);

        float x, y, z;
    };
}
``` 

must be print:

```c++
struct model_plain {
    float pos_0_x; //simple
    float pos_0_y; //simple
    float pos_0_z; //simple
    float pos_1_x; //simple
    float pos_1_y; //simple
    float pos_1_z; //simple
    float pos_2_x; //simple
    float pos_2_y; //simple
    float pos_2_z; //simple
    float orient_x; //simple
    float orient_y; //simple
    float orient_z; //simple
    int t; //simple
    float viewM_abc_x; //simple
    float viewM_abc_y; //simple
    float viewM_abc_z; //simple
    float viewP_0_abc_x; //simple
    float viewP_0_abc_y; //simple
    float viewP_0_abc_z; //simple
    float viewP_1_abc_x; //simple
    float viewP_1_abc_y; //simple
    float viewP_1_abc_z; //simple
    float viewP_2_abc_x; //simple
    float viewP_2_abc_y; //simple
    float viewP_2_abc_z; //simple
    float viewP_3_abc_x; //simple
    float viewP_3_abc_y; //simple
    float viewP_3_abc_z; //simple
    float viewP_4_abc_x; //simple
    float viewP_4_abc_y; //simple
    float viewP_4_abc_z; //simple
}; //auto generate
```