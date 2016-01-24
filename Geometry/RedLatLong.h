
#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedNumberRange kDegreesLatitudeRange  = RedNumberRange(-90,   90, 0); // 0 = default range behaviour to crop
static const RedNumberRange kDegreesLongitudeRange = RedNumberRange(-180, 180, kRedNumberRangeWrapOnUpper);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    class RedLatLong
    {
    public:
          
        // Constructors
        RedLatLong(void)                                               { Init(); };
        RedLatLong(const RedNumber& nlat, const RedNumber& nlon)       { Set(nlat, nlon); };

        // Basic accessors
        void      Init(void)                                           { lat=0; lon=0; };
        void      Set(const RedLatLong& p)                             { lat=p.lat; lon=p.lon; };
        void      Set(const RedNumber& nlat, const RedNumber& nlon)    { lat=nlat; lon=nlon; };
        RedNumber Lat(void) const                                      { return lat; };
        RedNumber Lon(void) const                                      { return lon; };

        void      PlaceNumbersWithinRange(void) { kDegreesLatitudeRange.CropNumber(lat); kDegreesLongitudeRange.WrapNumber(lon); };

        RedString StringOfObject(void) const;
        int       PopulateFromString(const RedString& str);

        void operator =(const RedLatLong& p) { Set(p); };
        //operator==

    private:
        RedNumber lat;
        RedNumber lon;
    };

} // Geometry
} // Red


