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
/* \file CSParser.hpp
 *
 *  Created on: Jul 6, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef CSPARSER_HPP_
#define CSPARSER_HPP_

//Data structures passed to the branching template
#include <sneuron/database/SWorld.hpp>
#include <sneuron/database/SNeuralNetwork.hpp>
#include <sneuron/database/SANN.hpp>
#include <sneuron/SNDataTypes.hpp>

#include <string>
#include <vector>
#include <Eigen/Eigen>

namespace sneuron
{
  /** This class is a base for reading a neural network definition into
   * a set of data structures.
   *
   * All file-format specific parsers will subclass this API class.
   *
   * If you want to implement a new parser for a new filetype, please
   * see how you should populate the sneuron/database/data_structs/*
   * data structures (look at an existing parser to learn how).
   */
  class CSParser
  {
  public:
    CSParser(){}
    virtual ~CSParser(){}

    /** Reads in some network globals from the given file.
     * Stuff like screen resolution, current working directory,
     * date, time, etc. etc. */
    virtual bool readGlobalsFromFile(const std::string &arg_file,
        /** The world's data will be filled into this data structure */
        sneuron::SWorld& arg_world)=0;

    /** Returns a list of the neural networks in the file
     * Reads in a name and a type. */
    virtual bool listNetworksInFile(const std::string& arg_file,
        std::vector<sneuron::string2>& arg_network_name_type)=0;

    /** Reads in a neural network from the given file. */
    virtual bool readNetworkFromFile(const std::string& arg_file,
        /** The network which will be read into the passed data structure */
        const std::string& arg_network_name,
        /** The network's data will be filled into this data structure */
        sneuron::SNeuralNetwork& arg_network)=0;

    /** Saves a network definition to file. */
    virtual bool saveNetworkToFile(const std::string &arg_file,
        /** The network to be saved to a file */
        const sneuron::SNeuralNetwork& arg_network)=0;

    /** Reads in an ANN from the given file. */
    virtual bool readANNFromFile(const std::string& arg_file,
        /** The ANN which will be read into the passed data structure */
        const std::string& arg_network_name,
        /** The network's data will be filled into this data structure */
        sneuron::SANN& arg_network)=0;

    /** Saves a network definition to file. */
    virtual bool saveANNToFile(const std::string &arg_file,
        /** The network to be saved to a file */
        const sneuron::SANN& arg_network)=0;
  };

}//End of namespace sneuron_parser

#endif /* CSPARSER_HPP_ */
