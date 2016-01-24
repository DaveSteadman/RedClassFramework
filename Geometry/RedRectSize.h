

#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

    class RedRectSize
    {
    public:
        RedRectSize() { Init(); };

        void Init(void)                    { width=0; height=0; };
        void Set(RedRectSize newsize)      { width=newsize.width; height=newsize.height; };
        void Set(const RedNumber& w, const RedNumber& h) { width=w; height=h; };

        void Adjust(const RedNumber& dx, const RedNumber& dy) { width+=dx; height+=dy; };

        void Scale(const RedNumber& f)     { width*=f; height*=f; };

        const RedNumber Width(void)  const { return width;  };
        const RedNumber Height(void) const { return height; };

        void operator =(const RedRectSize& newsize) { Set(newsize); };
        
    private: 
        RedNumber width;
        RedNumber height;
    };

} // Geometry
} // Red


