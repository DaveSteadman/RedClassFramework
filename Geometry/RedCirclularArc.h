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
 
#include "RedPoint2D.h"
#include "RedVector2D.h"
 
namespace Red {
namespace Geometry {

using namespace Red::Core;

/// Arc class exists to define circular arc maths. This in turn supports the definition of a rounded rectangle.
class RedCircularArc
{
public:

      // Constructors
      RedCircularArc (const RedPoint2D& p, const RedNumber r) : origin(p), radius(r) {};
      RedCircularArc (const RedCircle& c) : origin(c.origin), radius (c.radius) {};

      // Simple Assigns / Queries

      // create from rect, points, three points
      // Get points on circumference (for maths or drawing)
     
      // Bounding box
     
      // point-in-circle: get vector of distance
      RedVector2D VectorOffsetFromOrigin(const RedPoint2D<RedNumber>& p);
      
        const RedNumber DistanceFromOriginToPoint(const RedPoint2DUnit p) const;

     /// \todo Point routine to contribute to drawing
     const RedPoint2DUnit PointAtAngle(RedNumber a);

private:
      RedPoint2D             origin;
      RedRectPositions     rectPos;
      RedNumber            startAngle;
      RedNumber            endAngle;

};

}
}