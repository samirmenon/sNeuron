/* This file is part of SNeuron, a control and simulation library
for neural networks.

SNeuron is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

Alternatively, you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

SNeuron is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License and a copy of the GNU General Public License along with
SNeuron. If not, see <http://www.gnu.org/licenses/>.
 */
/* \file SNDataTypes.hpp
 *
 *  Created on: Oct 22, 2009
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

/*  Defines a lot of custom variables. */

#ifndef SNEURONDATATYPES_HPP_
#define SNEURONDATATYPES_HPP_

#include <string>

namespace sneuron
{
  ///////////////////////////////////////////////////////////////
  ////////////////////////////DATA TYPES/////////////////////////
  ///////////////////////////////////////////////////////////////

  //Standard bool
  typedef bool snBool;
  //Standard char
  typedef char snChar;
  //Standard unsigned int
  typedef unsigned int snUInt;
  //Standard int (4-byte)
  typedef int snInt;
  //Standard longlong
  typedef long long snLongLong;
  //Standard NULL
  const snUInt SN_NULL=0;

  /** Standard floating point ops in general */
  typedef double snFloat;

  /** Neuron clock (Can use system clock measurements which require
   * more than a float */
  typedef double snClock;

  struct string2
  {
    std::string str1;
    std::string str2;
  };

  ///////////////////////////THE END/////////////////////////////
}
#endif /* SNEURONDATATYPES_HPP_ */
