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
/* \file CFileLogger.cpp
 *
 *  Copyright (C) 2008
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#include <cassert>

#include <sneuron/engine/logging/CFileLogger.hpp>
#include <sneuron/engine/clock/CSystemClock.hpp>

using namespace std;

namespace sneuron
{
CFileLogger::CFileLogger()
{
}

CFileLogger::~CFileLogger()
{		
}

bool CFileLogger::init(const string & arg_outfile)
{
  logfile_name_ = arg_outfile;
  log_.open(logfile_name_.c_str(), ios::app);
  if(log_.fail()){  return false; }
  return true;
}

void CFileLogger::log_spike(const snInt & arg_neuron_id)
{
  assert(!log_.fail());
  CSystemClock *clock = CSystemClock::get_clock();
  log_<<"\n"<<clock->get_sim_time()<<" "<<arg_neuron_id;
}

void CFileLogger::log_data(const snInt & arg_neuron_id, const string &arg_string_to_log)
{
  assert(!log_.fail());
  CSystemClock *clock = CSystemClock::get_clock();
  log_<<"\n"<<clock->get_sim_time()<<" "<<arg_neuron_id<<"	"<<arg_string_to_log;
}


}
