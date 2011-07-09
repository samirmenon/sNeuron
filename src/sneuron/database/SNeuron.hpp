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
/* \file SNeuron.hpp
 *
 *  Created on: Jul 7, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef SNEURON_HPP_
#define SNEURON_HPP_

#include <sneuron/database/SObject.hpp>

#include <Eigen/Core>

namespace sneuron
{

  /** A data structure to store generic neuron properties */
  class SNeuron : public sneuron::SObject
  {
  public:
    /** Every neuron has a numeric id in its set */
    snUInt id_;

    /** Every neuron has a globally unique id.
     * Get this from the database. */
    snUInt uid_;

    /** The membrane-voltage
     * The generic variable associated with any neuron. */
    snFloat vm_;

    /** Default constructor : Does nothing */
    SNeuron(){}
    /** Default constructor : Does nothing */
    virtual ~SNeuron(){}

    /* Inherited variables:
    std::string name_;
    std::string type_;
    snBool has_been_init_; */
  };

  /** A linear neuron with the following dynamic equation:
   *
   * dV/dt = aV + b
   */
  class SNeuronLinear : public SNeuron
  {
  public:
    /** The dynamical constants */
    snFloat a_, b_;

    /** This is the refractory period. Ie. The time period after a spike
     * for which the neuron's membrane voltage remains fixed at zero. */
    snFloat t_ref_;

    /** This should point to the memory in the Eigen::MatrixXd encoders_
     * from this neuron's set.
     */
    Eigen::VectorXd encoder_;
  };

  /** A quadratic neuron with the following dynamic equation:
   *
   * dV/dt = aV^2 + bV + c
   */
  class SNeuronQuadratic : public SNeuron
  {
  public:
    /** The dynamical constants */
    snFloat a_, b_, c_;

    /** This is the refractory period. Ie. The time period after a spike
     * for which the neuron's membrane voltage remains fixed at zero. */
    snFloat t_ref;
  };

  /** A quadratic neuron with the following dynamic equation:
   *
   * dV/dt = aV^3 + bV^2 + cV + d
   */
  class SNeuronCubic : public SNeuron
  {
  public:
    /** The dynamical constants */
    snFloat a_, b_, c_, d_;

    /** This is the refractory period. Ie. The time period after a spike
     * for which the neuron's membrane voltage remains fixed at zero. */
    snFloat t_ref;
  };

}

#endif /* SNEURON_HPP_ */
