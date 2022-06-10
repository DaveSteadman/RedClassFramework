// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
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

#ifndef NULL
    #define NULL 0
#endif

namespace Red {
namespace Core {

static const char* kNullStr = "\0";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Core
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const double kHalfPi = 1.570796326794896619;
static const double kPi     = 3.141592653589793238;
static const double kTwoPi  = 6.283185307179586476;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Angles
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const double kRadsPerFullCircle    =   6.28318531;
static const double kDegreesPerFullCircle = 360.0;

static const double kDegreesPerRadian     = 57.29577951308232;
static const double kRadiansPerDegree     =  0.017453292519943;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Area
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial
static const double kSquarefeetPerAcre          = 43560.0;
static const double kSquareyardPerAcre          =  4840.0;
static const double kSquarefeetPerSquareyard    =     9.0;
static const double kSquareinchesPerSquarefoot  =   144.0;
static const double kAcresPerSquareMile         =   640.0;

// metric
static const double kSquaremetresPerHectare          = 10000.0;
static const double kHectaresPerSquarekilometre      =   100.0;
static const double kSquarekilometresPerSquaremetre  =     0.000001;
static const double kHectaresPerSquaremetre          =     0.0001;
static const double kSquarecentimetresPerSquaremetre = 10000.0;

// crossover
static const double kHectaresPerAcre            =    0.404685642;
static const double kSquareinchesPerSquaremetre = 1550.0031;
static const double kSquarefeetPerSquaremetre   =   10.7639104;
static const double kAcresPerSquaremetre        =    0.000247105381;
static const double kSquaremetresPerAcre        = 4046.85643005078874;
static const double kSquaremilesPerSquaremetre  =    0.000000386102159;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Distance
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial
static const double kInchesPerYard       =   36.0;
static const double kInchesPerFoot       =   12.0;
static const double kFeetPerYard         =    3.0;
static const double kYardsPerMile        = 1760.0;

// metric
static const double kMetresPerKilometre  = 1000.0;
static const double kMetresPerCentimetre =    0.01;
static const double kMetresPerMillimetre =    0.001;

static const double kKilometresPerMetre  =    0.001;
static const double kCentimetresPerMetre =  100.0;
static const double kMillimetresPerMetre = 1000.0;

// crossover
static const double kCentimetresPerInch  = 2.54;

static const double kMetresPerInch       =    0.0254;
static const double kMetresPerFoot       =    0.3048;
static const double kMetresPerYard       =    0.9144;
static const double kMetresPerMile       = 1609.344;

static const double kInchesPerMetre      = 39.3700787;
static const double kFeetPerMetre        =  3.2808399;
static const double kYardsPerMetre       =  1.0936133;
static const double kMilesPerMetre       =  0.000621371192;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Speed
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial

// metric
static const double kMetrespersecondPerKilometreperhour       = 0.27778;
static const double kKilometresperhourPerMetrespersecond      = 3.5999;

// crossover
static const double kMilesperhourPerMetrespersecond           = 2.2369;
static const double kFeetpersecondPerMetrespersecond          = 3.2808;
static const double kMachPerMetrespersecond                   = 0.0029;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Temperature
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial
static const double kFahrenheitPerCelsius     = 1.8;
static const double kAbsoluteZeroInFahrenheit = -459.67;

// metric
static const double kAbsoluteZeroInCelsius    = -273.15;
static const double kZeroCelsiusInKelvin      =  273.15;

// crossover
static const double kZeroCelsiusInFahrenheit  = 32.0;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Time
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Day Units
static const int kSecondsPerMinute = 60;
static const int kMinutesPerHour   = 60;
static const int kHoursPerDay      = 24;

// Year Units
static const int kDaysPerWeek        =   7;
static const int kWeeksPerYear       =  52;
static const int kDaysPerRegularYear = 355;
static const int kDaysPerLeapYear    = 356;
static const int kMonthsPerYear      =  12;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Volume 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial
static const double kPintsPerGallon       =   8.0;
static const double kFluidOuncesPerPint   =  20.0;
static const double kFluidOuncesPerGallon = 160.0;

// metric
static const double kMillitresPerLitre    = 1000.0;
static const double kLitresPerCubicMetre  = 1000.0;
static const double kCubicMetresPerLitre  =    0.0001;

// crossover
static const double kMillilitresPerPint   = 568.261485;

static const double kLitresPerPint        = 0.568261458;
static const double kLitresPerGallon      = 4.54609188;

static const double kPintsPerLitre        =  1.75975326;
static const double kGallonsPerLitre      =  0.219969157;
static const double kFluidOuncesPerLitre  = 35.1950652;
static const double kCubicInchesPerLitre  = 61.0237441;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Weight 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Ton = imperial, 2240 pounds, Tonne = metric, 1000 kilos

// imperial
static const double kOuncesPerPound     =  16.0;
static const double kPoundsPerStone     =  14.0;
static const double kStonesPerTon       = 160.0;

// metric
static const double kGramsPerKilogram   = 1000.0;
static const double kKilogramsPerTonne  = 1000.0;
static const double kTonnesPerKilogram  =    0.0001;

// crossover
static const double kKilogramsPerOunce  =   0.0283495231;
static const double kKilogramsPerPound  =   0.45359237;
static const double kKilogramsPerStone  =   6.35029318;
static const double kKilogramsPerTon    = 907.18474;

static const double kOuncesPerKilogram  = 35.2739619;
static const double kPoundsPerKilogram  =  2.20462262;
static const double kStonesPerKilogram  =  0.157473044;
static const double kTonsPerKilogram    =  0.00110231131;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
