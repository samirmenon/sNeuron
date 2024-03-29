/*
 * External code that performs useful mathematical
 * functions...
 *
 * MathExternal.hpp
 *
 *  Created on: May 20, 2010
 *      Author: Samir Menon
 */

#ifndef MATHEXTERNAL_HPP_
#define MATHEXTERNAL_HPP_

#include <stdlib.h>
#include <math.h>

//  #define INFINITYCHECK
//  #define NANCHECK
  #define SIGNCHECK

namespace sneuron
{

  // Support functions and conditional compilation directives for the
  // master AlmostEqual function.
  // http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm

  inline bool IsInfinite(float A)
  {
      const int kInfAsInt = 0x7F800000;

      // An infinity has an exponent of 255 (shift left 23 positions) and
      // a zero mantissa. There are two infinities - positive and negative.
      if ((*(int*)&A & 0x7FFFFFFF) == kInfAsInt)
          return true;
      return false;
  }

  inline bool IsNan(float A)
  {
      // A NAN has an exponent of 255 (shifted left 23 positions) and
      // a non-zero mantissa.
      int exp = *(int*)&A & 0x7F800000;
      int mantissa = *(int*)&A & 0x007FFFFF;
      if (exp == 0x7F800000 && mantissa != 0)
          return true;
      return false;
  }

  inline int Sign(float A)
  {
      // The sign bit of a number is the high bit.
      return (*(int*)&A) & 0x80000000;
  }

  // This is the 'final' version of the AlmostEqualUlps function.
  // The optional checks are included for completeness, but in many
  // cases they are not necessary, or even not desirable.
  // Ulps = significant digits
  bool AlmostEqualUlpsFinal(float A, float B, int maxUlps)
  {
      // There are several optional checks that you can do, depending
      // on what behavior you want from your floating point comparisons.
      // These checks should not be necessary and they are included
      // mainly for completeness.

  #ifdef  INFINITYCHECK
      // If A or B are infinity (positive or negative) then
      // only return true if they are exactly equal to each other -
      // that is, if they are both infinities of the same sign.
      // This check is only needed if you will be generating
      // infinities and you don't want them 'close' to numbers
      // near FLT_MAX.
      if (IsInfinite(A) || IsInfinite(B))
          return A == B;
  #endif

  #ifdef  NANCHECK
      // If A or B are a NAN, return false. NANs are equal to nothing,
      // not even themselves.
      // This check is only needed if you will be generating NANs
      // and you use a maxUlps greater than 4 million or you want to
      // ensure that a NAN does not equal itself.
      if (IsNan(A) || IsNan(B))
          return false;
  #endif

  #ifdef  SIGNCHECK
      // After adjusting floats so their representations are lexicographically
      // ordered as twos-complement integers a very small positive number
      // will compare as 'close' to a very small negative number. If this is
      // not desireable, and if you are on a platform that supports
      // subnormals (which is the only place the problem can show up) then
      // you need this check.
      // The check for A == B is because zero and negative zero have different
      // signs but are equal to each other.
      if (Sign(A) != Sign(B))
          return A == B;
  #endif

      int aInt = *(int*)&A;
      // Make aInt lexicographically ordered as a twos-complement int
      if (aInt < 0)
          aInt = 0x80000000 - aInt;
      // Make bInt lexicographically ordered as a twos-complement int
      int bInt = *(int*)&B;
      if (bInt < 0)
          bInt = 0x80000000 - bInt;

      // Now we can compare aInt and bInt to find out how far apart A and B
      // are.
      int intDiff = abs(aInt - bInt);
      if (intDiff <= maxUlps)
          return true;
      return false;
  }

}

#endif /* MATHEXTERNAL_HPP_ */
