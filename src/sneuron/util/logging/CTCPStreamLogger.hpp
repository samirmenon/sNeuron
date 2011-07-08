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
/* \file CTCPStreamLogger.hpp
 *
 *  Copyright (C) 2008
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef CTCPSTREAMLOGGER_HPP_
#define CTCPSTREAMLOGGER_HPP_

#include <sneuron/SNDataTypes.hpp>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string>

namespace sneuron
{

  typedef double snLogType;
  const snLogType SNEURON_LOG_BUF_LEN = (2*sizeof(snLogType));

  class CTCPStreamLogger
  {
    hostent *serverIpHost;
    sockaddr_in socket_address;
    int sockfd; //socket file descriptor
  public:
    CTCPStreamLogger(){}
    virtual ~CTCPStreamLogger();

    snBool init(const snChar * arg_outip="127.0.0.1",
        const snInt &arg_outport=8088);

    void log_spike(const snInt &arg_neuron_id);
  };

}

#endif /*CTCPSTREAMLOGGER_HPP_*/
