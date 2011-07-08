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
/* \file SDatabase.hpp
 *
 *  Created on: Jul 2, 2010
 *
 *  Copyright (C) 2010
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef SDATABASE_HPP_
#define SDATABASE_HPP_

#include <sneuron/database/SNeuralNetwork.hpp>

#include <sneuron/SNDataTypes.hpp>

#include <sneuron/util/CPileMap.hpp>

namespace sneuron
{

  /** The main data store for any sneuron simulation.
   * All data components that are shared across the
   * simulation will reside here.
   *
   * For instance :
   * -- Ion channel FOPs and vm range
   * -- The spike sharing buffers
   * -- Handles to the neurons
   * -- Handles to the Gui and visualization data
   */
  struct SDatabase
  {
    /** A pile containing the neuron type static information.
     * Manages the data and enables pointer based access. */
    sneuron::CPileMap<std::string, SNeuronType> neuron_types_;

    /** A pile containing the neural network static information.
     * Manages the data and enables pointer based access. */
    sneuron::CPileMap<std::string, SNeuralNetwork> nn_;

    /** A pile containing the ANN static information.
     * Manages the data and enables pointer based access. */
    sneuron::CPileMap<std::string, SANN> ann_;
  };

}

#endif /* SDATABASE_HPP_ */
