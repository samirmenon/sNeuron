/* This file is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

Alternatively, you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This file is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License and a copy of the GNU General Public License along with
this file. If not, see <http://www.gnu.org/licenses/>.
*/
/* \file CSystemClock.hpp
 *
 *  Created on: 2008
 *
 *  Copyright (C) 2008, Samir Menon <smenon@stanford.edu>
 */

#ifndef CSYSTEMCLOCK_HPP_
#define CSYSTEMCLOCK_HPP_

#include <unistd.h>
#include <sys/time.h>

#include <wbc/WbcDataTypes.hpp>

namespace wbc
{
  typedef wClock NEURON_CLOCK;

  class CSystemClock
  {
  public:
    static CSystemClock* get_clock();
    inline wClock get_sim_time()	{ return clock;	}
    wFloat get_sys_time();

    //TODO: Make these functions private and access them only through a friend class
    //Only the main simulation classes will have access to setting and modifying the clock
    static void create_clock();
    static void destroy_clock();

    inline void tick(wFloat arg_dt){ clock+=arg_dt;  }
    inline void tick_sec(timeval &arg_t_start)
    {//Sleeps for 1sec from the time passed
      wFloat time_diff;
      time_diff = compute_t_diff(arg_t_start);
      if(time_diff<1.0){	sleep(1.0-time_diff);	} //Maintain real time
      clock+=1.0;
    }

  private:
    CSystemClock();
    CSystemClock(const CSystemClock&);
    CSystemClock& operator= (const CSystemClock&);
    wFloat compute_t_diff(timeval &t_start);
    //Data
    wClock clock;
    static CSystemClock* pinstance;
    timeval t_tick,t_diff;
    timeval t_start_;
  };

}

#endif /*CSYSTEMCLOCK_HPP_*/
