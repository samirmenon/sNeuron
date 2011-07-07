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
/* \file CSParserYaml.hpp
 *
 *  Created on: Jul 6, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef CSPARSERYAML_HPP_
#define CSPARSERYAML_HPP_

#include <sneuron/parser/CSParser.hpp>

namespace sneuron
{

  class CSParserYaml : public sneuron::CSParser
  {
  public:
    CSParserYaml();
    virtual ~CSParserYaml();

    /** Reads in some network globals from the given file.
     * Stuff like screen resolution, current working directory,
     * date, time, etc. etc. */
    virtual bool readGlobalsFromFile(const std::string &arg_file,
        /** The world's data will be filled into this data structure */
        sneuron::SWorld& arg_world)
    { return false; } //NOTE TODO : Complete this once the data structure is ready

    /** Returns a list of the neural networks in the file */
    virtual bool listNetworksInFile(const std::string& arg_file,
        std::vector<sneuron::string2>& arg_network_name_type);

    /** Reads in a neural network from the given file. */
    virtual bool readNetworkFromFile(const std::string& arg_file,
        /** The network which will be read into the passed data structure */
        const std::string& arg_network_name,
        /** The network's data will be filled into this data structure */
        sneuron::SNeuralNetwork& arg_network);

    /** Saves a network definition to file. */
    virtual bool saveNetworkToFile(const std::string &arg_file,
        /** The network to be saved to a file */
        const sneuron::SNeuralNetwork& arg_network);

    /** Returns a list of the ANNs in the file */
    virtual bool listANNsInFile(const std::string& arg_file,
        std::vector<std::string>& arg_ann_names)
    { return false; } //NOTE TODO : Complete this once the data structure is ready

    /** Reads in an ANN from the given file. */
    virtual bool readANNFromFile(const std::string& arg_file,
        /** The ANN which will be read into the passed data structure */
        const std::string& arg_network_name,
        /** The network's data will be filled into this data structure */
        sneuron::SANN& arg_network)
    { return false; } //NOTE TODO : Complete this once the data structure is ready

    /** Saves a network definition to file. */
    virtual bool saveANNToFile(const std::string &arg_file,
        /** The network to be saved to a file */
        const sneuron::SANN& arg_network)
    { return false; } //NOTE TODO : Complete this once the data structure is ready
  };

}

#endif /* CSPARSERYAML_HPP_ */
