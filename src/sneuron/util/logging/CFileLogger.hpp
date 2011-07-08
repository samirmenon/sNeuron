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
/* \file CFileLogger.hpp
 *
 *  Copyright (C) 2008
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef CFILELOGGER_H_
#define CFILELOGGER_H_


#include <sneuron/SNDataTypes.hpp>

#include <fstream>
#include <string>

namespace sneuron
{	
  class CFileLogger
  {
    std::string logfile_name_;
    std::ofstream log_;
  public:
    CFileLogger();
    virtual ~CFileLogger();

    bool init(const std::string & arg_outfile);

    void log_spike(const snInt & arg_neuron_id);
    void log_data(const snInt & arg_neuron_id, const std::string &arg_string_to_log);
  };

}

#endif /*CFILELOGGER_H_*/
