
#pragma once

#include "RedGeometryNamespace.h"

namespace Red {
namespace Test {

    class RedTestGeometry
    {
    public:
        static int RunUnitTest(void);

    private:
        // 2D
        static int TestCircle(void);
        static int TestLine2D(void);
        static int TestPoint2D(void);
        static int TestRect(void);
        static int TestRectSize(void);
        static int TestVector2D(void);

        // 3D
        static int TestSphere(void);
        static int TestLine3D(void);
        static int TestLatLong(void);
        static int TestPoint3D(void);
        static int TestVector3D(void);
    };

}
}