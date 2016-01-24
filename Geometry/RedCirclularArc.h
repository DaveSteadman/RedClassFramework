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