/*
 * CSFOPEuler.cpp
 *
 *  Created on: May 20, 2010
 *      Author: Samir Menon
 */

#include <cassert>

#include "CSFOPEuler.hpp"

namespace sneuron
{
  bool CSFOPEuler::init(const SSFirstOrderProcessData * arg_data,
                    const snFloat& arg_init_state,
                    const snFloat& arg_dt_)
  {
    assert(arg_dt_ > 0); //It is "forward" euler after all.
    dt_ = arg_dt_;
    return CSFirstOrderProcess::init(arg_data,arg_init_state);
  }
}

