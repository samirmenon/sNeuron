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
/* \file SObject.hpp
 *
 *  Created on: Jan 15, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef SOBJECT_HPP_
#define SOBJECT_HPP_

#include <sneuron/SNDataTypes.hpp>
#include <string>

namespace sneuron
{
  class SObject
  {
  public:
    std::string name_;
    std::string type_;
    snBool has_been_init_;

    SObject() : name_(""), type_(""), has_been_init_(false)
    {}

    virtual ~SObject() {}
  };

}

#endif /* SOBJECT_HPP_ */
