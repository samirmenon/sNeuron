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
/* \file CTCPStreamLogger.cpp
 *
 *  Copyright (C) 2008
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#include <stdio.h>
#include <string.h>

#include <sneuron/engine/logging/CTCPStreamLogger.hpp>
#include <sneuron/engine/clock/CSystemClock.hpp>

namespace sneuron
{


snBool CTCPStreamLogger::init(const char* arg_outip, const snInt &arg_outport)
{		
	snBool flag = false;
  //Create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //TCP synchronous commn (for now)
  if (sockfd < 0)
  {	printf("ERROR opening socket");	goto END; }

  //Retrieves host information corresponding to a host name from a host database
  serverIpHost = gethostbyname(arg_outip); //Ip used here
  if (serverIpHost == NULL)
  {	printf("Could not obtain host name");	goto END; }


  memset((char *) &socket_address, '\0', sizeof(socket_address));
  socket_address.sin_family = AF_INET; //TCP
  memmove((char *)serverIpHost->h_addr, (char *)&socket_address.sin_addr.s_addr,
        serverIpHost->h_length);
  socket_address.sin_port = htons(arg_outport); //Port: to TCP/IP byte order(big-endian)

  if(connect(sockfd,(sockaddr*)&socket_address,sizeof(socket_address)) < 0)
  {	printf("ERROR connecting"); goto END;	}

  flag = true;
END:
  return flag;
}

CTCPStreamLogger::~CTCPStreamLogger()
{
	close(sockfd);
}

void CTCPStreamLogger::log_spike(const snInt &arg_neuron_id)
{
  snLogType tmp[2];
  snInt bytes_written;

  snChar log_buf[2*sizeof(snLogType)];//Buffer to be logged

  //NOTE TODO Serialize this
  memset((snChar *) log_buf, '\0', SNEURON_LOG_BUF_LEN);

  tmp[0] = (snLogType) arg_neuron_id; //Neuron id
  CSystemClock *clock = CSystemClock::get_clock();
  tmp[1] = (snLogType) clock->get_sim_time(); //Spike time

  memcpy(log_buf,tmp, SNEURON_LOG_BUF_LEN);

  bytes_written = write(sockfd,log_buf,SNEURON_LOG_BUF_LEN);

  if (bytes_written < 0)
  {	printf("LOG : ERROR writing to socket");	}
}

}
