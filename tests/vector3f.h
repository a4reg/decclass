
namespace core {

    class vector3f {
    public:
        vector3f();

        vector3f operator+(vector3f);

        float x, y, z;
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