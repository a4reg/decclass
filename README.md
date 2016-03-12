# decclass
Tool for decomposition C++ class/stuct to simple types

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
``` 

must be print:
```c
struct model2_plain {
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
    float abc_x; //simple
    float abc_y; //simple
    float abc_z; //simple
    float abc_x; //simple
    float abc_y; //simple
    float abc_z; //simple
    float abc_x; //simple
    float abc_y; //simple
    float abc_z; //simple
    float abc_x; //simple
    float abc_y; //simple
    float abc_z; //simple
    float abc_x; //simple
    float abc_y; //simple
    float abc_z; //simple
    float abc_x; //simple
    float abc_y; //simple
    float abc_z; //simple
}; //auto generate
```


