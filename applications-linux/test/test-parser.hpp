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
/* \file test-parser.hpp
 *
 *  Created on: Jul 7, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef TEST_PARSER_HPP_
#define TEST_PARSER_HPP_

#include <sneuron/database/SNeuralNetwork.hpp>
#include <sneuron/database/SANN.hpp>

#include <sneuron/parser/syaml/CSParserYaml.hpp>
#include <sneuron/util/HelperFunctions.hpp>

#include <iostream>
#include <stdexcept>

namespace sneuron_test
{

  /** 1. Tests the sneuron yaml parser with a sample network
   *
   *   File  = "specs/Test/TestCfg.yaml"
   */
  void test_parser(int arg_id)
  {
    bool flag;
    int r_id=0; //The current test stage for this function.
    try
    {
      sneuron::CSParserYaml parser;
      sneuron::SANN ann;

      //1. Read in a file
      std::string infile;
      flag = sneuron_util::getCurrentDir(infile);
      if(false == flag)
      { throw(std::runtime_error("Could not read current working directory"));  }
      else  { std::cout<<"\nTest Result ("<<r_id++<<") Current working directory = "<<infile; }
      infile = + "../../specs/Test/TestCfg.yaml";
      std::cout<<"\nTest Result ("<<r_id++<<") Test file is : "<<infile;

      //Test to check listNetworksInFile
      std::vector<sneuron::string2> network_list;
      flag = parser.listNetworksInFile(infile, network_list);
      if(false == flag)
      { throw(std::runtime_error("Could not read list of networks from the test file"));  }
      else  { std::cout<<"\nTest Result ("<<r_id++<<") Read ("<<network_list.size()<<") networks from the test file"; }

     //Test for readNetworkFromFile
      std::vector<sneuron::string2>::iterator it,ite;
      for(it = network_list.begin(), ite = network_list.end();
          it!=ite; ++it)
      {
        if((*it).str2 == "NEF")
        {
          //You need to receive every network in a new object to avoid duplicate map entries
          sneuron::SNeuralNetwork nn;

          /** Call the function. Pass it the Yaml file, name of network to be read and the object
           * that recieves it.
           */
          flag = parser.readNetworkFromFile(infile,(*it).str1, nn);
          if(false == flag)
          { throw(std::runtime_error("Could not read an NEF network from the test file"));  }
          else  { std::cout<<"\nTest Result ("<<r_id++<<") Read ("<<(*it).str1<<") NEF network from the test file"; }

          /** To check if the network was read correctly. Compare parameters with the test file
          */
          if(nn.name_!=(*it).str1 || "NEF"!=nn.type_ || 1!=nn.sets_.size())
          { throw(std::runtime_error("Could not parse an NEF network from the test file"));  }
          else
          { std::cout<<"\nTest Result ("<<r_id++<<") Successfully parsed ("<<(*it).str1<<") NEF network from the test file"; }
        //Add more test function here
        }

        else if((*it).str2 == "ANN")
        {
          flag = parser.readANNFromFile(infile,(*it).str1, ann);
          if(false == flag)
          { throw(std::runtime_error("Could not read an NEF network from the test file"));  }
          else  { std::cout<<"\nTest Result ("<<r_id++<<") Read ("<<(*it).str1<<") ANN network from the test file"; }

          /** A bunch of code that checks whether you've correctly read the file */
        }
      }
      std::cout<<"\nTest #"<<arg_id<<" : Succeeded.";
    }
    catch (std::exception& ee)
    {
      std::cout<<"\nTest Error ("<<r_id++<<") : "<<ee.what();
      std::cout<<"\nTest #"<<arg_id<<" : Failed.";
    }
  }

}//End of namespace sneuron_test

#endif /* TEST_PARSER_HPP_ */
