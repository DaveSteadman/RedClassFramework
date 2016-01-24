#pragma once

#include "RedCoreNamespace.h"

#include "RedPoint2D.h"
#include "RedVector2D.h"
#include "RedRect.h"
#include "RedCircularArc.h"
 
namespace Red {
namespace Geometry {

using namespace Red::Core;

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
 