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
/* \file SNeuronSet.hpp
 *
 *  Created on: Jul 7, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef SNEURONSET_HPP_
#define SNEURONSET_HPP_

#include <sneuron/database/SNeuron.hpp>
#include <sneuron/database/SObject.hpp>
#include <sneuron/util/CPileMap.hpp>
#include <sneuron/SNDataTypes.hpp>

#include <Eigen/Core>

namespace sneuron
{
  /** This is the data required to define a set of neurons */
  class SNeuronSet : public sneuron::SObject
  {
  public:
    snUInt n_neurons_;
    snUInt input_dim_;

    /** Since SNeuron is a base class, and many neuron types exist
     * we must allocate SNeuron objects like this:
     *
     * std::string name("MyName");//For example.
     * SNeuron** n = neuron_.create(name,NULL);
     * if(NULL == n) { We have an error. Handle it  }
     * *n = new SNeuronSubclass();
     * //And we are done.
     */
    sneuron::CPileMap<std::string, SNeuron*> neurons_;

    /** These are used to convert an input analog vector into
     * input currents for each neuron
     *
     * input_currents_ = alpha.array() * (analog_input_ * encoders_).array() + beta_.array();
     * */
    Eigen::MatrixXd encoders_;
    Eigen::VectorXd input_currents_, alpha_, beta_;

    /** Default constructor : Does nothing */
    SNeuronSet(){}
    /** Default destructor : Does nothing */
    virtual ~SNeuronSet();

    /* Inherited variables:
    std::string name_;
    std::string type_;
    snBool has_been_init_; */
  };

  SNeuronSet::~SNeuronSet()
  {
    /** Since neuron pointers are stored in the database (SNeuron is a base class)
     * we have to manually loop through the pilemap and delete the actual objects.
     */
    neurons_.resetIterator();
    while(NULL!=neurons_.iterator_)
    {
      SNeuron** neuron = neurons_.iterator_->data_;
      if(NULL!=*neuron)
      { delete *neuron;  }
      neurons_.iterator_ = neurons_.iterator_->next_;
    }
  }

}

#endif /* SNEURONSET_HPP_ */
