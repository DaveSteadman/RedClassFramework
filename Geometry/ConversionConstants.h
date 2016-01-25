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

namespace Red {
namespace Geometry {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Core
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const double pi     = 3.14159265;
static const double two_pi = 6.28318531;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Angles
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const double radsPerFullCircle    =   6.28318531;
static const double degreesPerFullCircle = 360.0;

static const double degreesPerRadian     = 57.29577951308232;
static const double radiansPerDegree     =  0.017453292519943;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Area
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial
static const double squarefeetPerAcre          = 43560.0;
static const double squareyardPerAcre          =  4840.0;
static const double squarefeetPerSquareyard    =     9.0;
static const double squareinchesPerSquarefoot  =   144.0;
static const double acresPerSquareMile         =   640.0;

// metric
static const double squaremetresPerHectare          = 10000.0;
static const double hectaresPerSquarekilometre      =   100.0;
static const double squarekilometresPerSquaremetre  =     0.000001;
static const double hectaresPerSquaremetre          =     0.0001;
static const double squarecentimetresPerSquaremetre = 10000.0;

// crossover
static const double hectaresPerAcre            =    0.404685642;
static const double squareinchesPerSquaremetre = 1550.0031;
static const double squarefeetPerSquaremetre   =   10.7639104;
static const double acresPerSquaremetre        =    0.000247105381;
static const double squaremetresPerAcre        = 4046.85643005078874;
static const double squaremilesPerSquaremetre  =    0.000000386102159;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Distance
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial
static const double inchesPerYard       =   36.0;
static const double inchesPerFoot       =   12.0;
static const double feetPerYard         =    3.0;
static const double yardsPerMile        = 1760.0;

// metric
static const double metresPerKilometre  = 1000.0;
static const double metresPerCentimetre =    0.01;
static const double metresPerMillimetre =    0.001;

static const double kilometresPerMetre  =    0.001;
static const double centimetresPerMetre =  100.0;
static const double millimetresPerMetre = 1000.0;

// crossover
static const double centimetresPerInch  = 2.54;

static const double metresPerInch       =    0.0254;
static const double metresPerFoot       =    0.3048;
static const double metresPerYard       =    0.9144;
static const double metresPerMile       = 1609.344;

static const double inchesPerMetre      = 39.3700787;
static const double feetPerMetre        =  3.2808399;
static const double yardsPerMetre       =  1.0936133;
static const double milesPerMetre       =  0.000621371192;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Speed
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial

// metric
static const double metrespersecondPerKilometreperhour       = 0.27778;
static const double kilometresperhourPerMetrespersecond      = 3.5999;

// crossover
static const double milesperhourPerMetrespersecond           = 2.2369;
static const double feetpersecondPerMetrespersecond          = 3.2808;
static const double machPerMetrespersecond                   = 0.0029;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Temperature
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial
static const double fahrenheitPerCelsius     = 1.8;
static const double absoluteZeroInFahrenheit = -459.67;

// metric
static const double absoluteZeroInCelsius    = -273.15;
static const double zeroCelsiusInKelvin      =  273.15;

// crossover
static const double zeroCelsiusInFahrenheit  = 32.0;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Time
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Day Units
static const int secondsPerMinute = 60;
static const int minutesPerHour   = 60;
static const int hoursPerDay      = 24;

// Year Units
static const int daysPerWeek        =   7;
static const int weeksPerYear       =  52;
static const int daysPerRegularYear = 355;
static const int daysPerLeapYear    = 356;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Volume 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// imperial
static const double pintsPerGallon       =   8.0;
static const double fluidOuncesPerPint   =  20.0;
static const double fluidOuncesPerGallon = 160.0;

// metric
static const double millitresPerLitre    = 1000.0;
static const double litresPerCubicMetre  = 1000.0;
static const double cubicMetresPerLitre  =    0.0001;

// crossover
static const double millilitresPerPint   = 568.261485;

static const double litresPerPint        = 0.568261458;
static const double litresPerGallon      = 4.54609188;

static const double pintsPerLitre        =  1.75975326;
static const double gallonsPerLitre      =  0.219969157;
static const double fluidOuncesPerLitre  = 35.1950652;
static const double cubicInchesPerLitre  = 61.0237441;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Weight 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Ton = imperial, 2240 pounds, Tonne = metric, 1000 kilos

// imperial
static const double ouncesPerPound     =  16.0;
static const double poundsPerStone     =  14.0;
static const double stonesPerTon       = 160.0;

// metric
static const double gramsPerKilogram   = 1000.0;
static const double kilogramsPerTonne  = 1000.0;
static const double tonnesPerKilogram  =    0.0001;

// crossover
static const double kilogramsPerOunce  =   0.0283495231;
static const double kilogramsPerPound  =   0.45359237;
static const double kilogramsPerStone  =   6.35029318;
static const double kilogramsPerTon    = 907.18474;

static const double ouncesPerKilogram  = 35.2739619;
static const double poundsPerKilogram  =  2.20462262;
static const double stonesPerKilogram  =  0.157473044;
static const double tonsPerKilogram    =  0.00110231131;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Geometry
} // Red


