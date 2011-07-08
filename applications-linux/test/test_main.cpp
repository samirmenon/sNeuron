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
/* \file test_main.cpp
 *
 *  Created on: Jul 7, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */


#include "test-parser.hpp"

#include <sneuron/SNDataTypes.hpp>
#include <sneuron/util/CSystemClock.hpp>

#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace sneuron;


/** This is a test application to test sneuron's features.
 * It also serves as a tutorial to show you how to use the
 * features. */
int main(int argc, char** argv)
{
  if(argc != 2)
  {
    int tid = 0;
    cout<<"\nThe command line input is: ./<executable> <test_number>";
    cout<<"\n"<<tid++<<" : Run all tests";
    cout<<"\n"<<tid++<<" : Run parser tests";
    cout<<"\n";
  }
  else
  {
    int tid, id = 1;
    tid = atoi(argv[1]);
    cout<<"\nRunning sneuron tests for case: "<<tid;
    sneuron::CSystemClock::create_clock(); //NOTE: Clock MUST be created and destroyed in main
    cout<<"\nStarting tests. Time:"<<sneuron::CSystemClock::get_clock()->get_sys_time();

    if((tid==0)||(tid==id))
    {//Test clock
      std::cout<<"\n\nTest #"<<id<<". System Clock [Sys time, Sim time :"
          <<sneuron::CSystemClock::get_clock()->get_sys_time()
          <<" "
          <<sneuron::CSystemClock::get_clock()->get_sim_time()
          <<"]";
      sneuron_test::test_parser(id);
    }
    ++id;

    cout<<"\n\nEnding tests. Time:"<<sneuron::CSystemClock::get_clock()->get_sys_time()<<"\n";
    sneuron::CSystemClock::destroy_clock();//NOTE: Clock MUST be created and destroyed
  }
  return 0;
}
