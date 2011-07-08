/*
 * CSFOPEulerLinHash.hpp
 *
 *  Created on: May 20, 2010
 *      Author: Samir Menon
 */

#ifndef CSFOPEULERLINHASH_HPP_
#define CSFOPEULERLINHASH_HPP_

#include <math.h>
#include <stdio.h>

#include <sneuron/math/CSFOPEuler.hpp>

namespace sneuron
{

  /**
   * CSFOPEulerLinHash :
   *
   * Integrator : Euler
   * FoP variable access : Linear Hash
   */
  class CSFOPEulerLinHash : public sneuron::CSFOPEuler
  {
  protected:
    /**
     * Linear uniform hashing between the state variable
     * and the index.
     */
    snFloat state_start_, state_end_, d_state_;
    snUInt state_size_;

  public:
    CSFOPEulerLinHash(){}
    virtual ~CSFOPEulerLinHash(){}

    /**
     * Initializes the first order process with a linear hash
     * between the state variable and the data index
     *
     * Needs a fixed linear step size between the state space
     * elements
     */
    bool init(const SSFirstOrderProcessData * arg_data,
                            const snFloat& arg_init_state,
                            const snFloat& arg_dt_);

  //protected:
    /**
     * Maps the value of the state variable to the corresponding
     * index of the first order data vector
     */
    virtual inline snUInt get_idx(const snFloat & arg_state)
    { return (snUInt) round((arg_state - state_start_)/d_state_);  }

    /***
     * Get size
     */
    snUInt get_state_size()
    { return state_size_; }
  };

}

#endif /* CSFOPEULERLINHASH_HPP_ */
