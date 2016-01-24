
#pragma once

#include "RedCoreNamespace.h"

#include "RedPoint2D.h"
#include "RedRectSize.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

    class RedRect
    {
    public:
        RedRect() { Init(); };
        RedRect(const RedRect& nr) { Set(nr); };
        RedRect(const RedPoint2D& no, const RedRectSize& ns) { Set(no, ns); };
        RedRect(const RedNumber& nx1, const RedNumber& ny1, const RedNumber& nx2, const RedNumber& ny2) { Set(nx1, ny1, nx2, ny2); };

        void Init(void)            { origin.Init(); size.Init(); };

        void Set(const RedRect& nr) { origin=nr.origin; size=nr.size; };
        void Set(const RedPoint2D& no, const RedRectSize& ns) { origin=no; size=ns; };
        void Set(const RedNumber& nx1, const RedNumber& ny1, const RedNumber& nx2, const RedNumber& ny2) { origin.Set(nx1,ny1); size.Set(nx2-nx1, ny2-ny1); };

        void              SetOrigin(const RedPoint2D& no)  { origin=no; };
        void              SetSize(const RedRectSize& ns) { size=ns; };
        const RedPoint2D    Origin(void) const { return origin; };
        const RedRectSize Size(void)   const { return size; };

        const int IsPointInRect(RedPoint2D p) const;

        void Inset(const RedNumber& i);

        void operator =(const RedRect& newvect) { Set(newvect); };

    private:
        RedPoint2D    origin;
        RedRectSize size; 
    };

} // Geometry
} // Red


