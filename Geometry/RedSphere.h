
#pragma once

#include "RedCoreNamespace.h"
#include "RedUnitsNamespace.h"

#include "RedPoint3D.h"
#include "RedLatLong.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

    class RedSphere
    {
    public:
     
        // Constructors
        RedSphere(void) { Init(); };
        RedSphere(const RedPoint3D& no, const RedNumber& nr) { Set(no, nr); };

        // Basic accessors
        void Init(void) { origin.Init(); radius=0; };
        void Set(const RedPoint3D& no, const RedNumber& nr) { origin=no; radius=nr; };

        RedNumber SurfaceArea(void)   const { return radius*radius * 4.0 * Red::Units::pi; }; // =4.pi.r^2
        RedNumber Volume(void)        const { return radius*radius*radius * (4.0 / 3.0) * Red::Units::pi; };  // =4/3.pi.r^3
        RedNumber Circumference(void) const { return radius * 2 * Red::Units::pi; }; // =2.pi.r

    private:
        RedPoint3D  origin;
        RedNumber   radius;
    };

} // Geometry
} // Red


