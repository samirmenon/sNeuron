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
/* \file CSystemClock.cpp
 *
 *  Created on: 2008
 *
 *  Copyright (C) 2008, Samir Menon <smenon@stanford.edu>
 */

#include "CSystemClock.hpp"

namespace wbc
{
  CSystemClock* CSystemClock::pinstance = NULL;// initialize pointer

  CSystemClock::CSystemClock()
  {
    gettimeofday(&t_start_,NULL);
    clock = 0.0;
  }

  CSystemClock* CSystemClock::get_clock()
  {
    if (pinstance == NULL)  // is it the first call?
    {
      return NULL; // create sole instance
    }
    return pinstance; // address of sole instance
  }

  void CSystemClock::create_clock()
  {
    if (pinstance == NULL)  // is it the first call?
    {
      pinstance = new CSystemClock(); // create sole instance
    }
  }

  void CSystemClock::destroy_clock()
  {
    if (pinstance != NULL)  // is it the first call?
    {
      delete pinstance; //delete the instance
    }
  }

  wFloat CSystemClock::compute_t_diff(timeval &t_start)
  {
    gettimeofday(&t_tick,NULL);
    //Code snippet from: http://www.gnu.org/software/libtool/manual/libc/Elapsed-Time.html
    /* Perform the carry for the later subtraction by updating y. */
    if (t_tick.tv_usec < t_start.tv_usec) {
      long int nsec = (t_start.tv_usec - t_tick.tv_usec) / 1000000 + 1;
      t_start.tv_usec -= 1000000 * nsec;
      t_start.tv_sec += nsec;
    }
    if (t_tick.tv_usec - t_start.tv_usec > 1000000) {
      long int nsec = (t_tick.tv_usec - t_start.tv_usec) / 1000000;
      t_start.tv_usec += 1000000 * nsec;
      t_start.tv_sec -= nsec;
    }

    /* Compute the time remaining to wait. tv_usec is certainly positive. */
    t_diff.tv_sec = t_tick.tv_sec - t_start.tv_sec;
    t_diff.tv_usec = t_tick.tv_usec - t_start.tv_usec;
    //End code snippet
    return (wFloat)t_diff.tv_sec+((wFloat)t_diff.tv_usec/1000000.00);
  }

  wFloat CSystemClock::get_sys_time()
  {
    return compute_t_diff(t_start_);
  }

}
