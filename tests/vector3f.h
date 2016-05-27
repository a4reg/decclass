
namespace core {

    class vector3f {
    public:
        vector3f();

        vector3f operator+(vector3f);

        union {
            float coord[3];
            struct {
                float x, y, z;
            };
        };
    };
}

namespace color {
    class Colors {
        enum {
            R = 255
        };
        char RedCh[R];
        core::vector3f r;
    };

}