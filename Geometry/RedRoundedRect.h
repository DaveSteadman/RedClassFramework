// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2016 David G. Steadman
// -------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// -------------------------------------------------------------------------------------------------
// (http://opensource.org/licenses/MIT)
// -------------------------------------------------------------------------------------------------

#pragma once

#include "RedCoreNamespace.h"

#include "RedPoint2D.h"
#include "RedVector2D.h"
#include "RedRect.h"
#include "RedCircularArc.h"
 
using namespace Red::Core;

namespace Red {
namespace Geometry {


/// Arc class exists to define circular arc maths. This in turn supports the definition of a rounded rectangle.
class RedRoundedRect
{
public:

      // Constructors
      RedRoundedRect(const RedRect& o, const RedNumber& r) : outlineRect(o), cornerRadius(r) { };

      // Simple Assigns / Queries
      void Init(void)                           { outlineRect.Init(); cornerRadius = 0; };
      void SetOutline(const RedRect& o)         { outline = o; };
      void SetCornerRadius(const RedNumber& r)  { cornerRadius = r; };

      const RedRect    Outline(void)      const { return outlineRect; };
      const RedNumber  CornerRadius(void) const { return cornerRadius; };

      // create from rect, points, three points
      // Get points on circumference (for maths or drawing)

      // Bounding box



      // point-in-shape: get vector of distance
      const RedVector2D VectorOffsetFromCentre(void) const;

      const int           IsPointInside(const RedPoint2D& p) const;
      /// Make IsPointWithRectAndOutsideArc routine.

private:
      /// Rect outline
      RedRect     outlineRect;
      RedNumber   cornerRadius;

      /// Derived attributes
      //RedCircularArcUnit

};

}
}
 