/*
 * CSFOPEuler.hpp
 *
 *  Created on: May 20, 2010
 *      Author: Samir Menon
 */

#ifndef CSFOPEULER_HPP_
#define CSFOPEULER_HPP_

#include <sneuron/math/CSFirstOrderProcess.hpp>

namespace sneuron
{

  class CSFOPEuler : public sneuron::CSFirstOrderProcess
  {
  protected:
    /*
     * Inherited:
      const SSFirstOrderProcessData *data_;
      snFloat fo_var_;
      snUInt fo_idx_;
      const snFloat *data_slice_;
     */
    /*
     * The forward euler timestep
     */
    snFloat dt_;

  public:
    CSFOPEuler():CSFirstOrderProcess(){}
    virtual ~CSFOPEuler(){}

    bool init(const SSFirstOrderProcessData * arg_data,
                  const snFloat& arg_init_state,
                  const snFloat& arg_dt_);
    /**
     * Uses forward euler to integrate the first order process.
     */
    virtual inline void integrate()
    {// x(t+1) = x(t) + ( (x_ss(state) - x(t))*dt/tau )
      fo_var_ += ((data_slice_[1]-fo_var_)*dt_/data_slice_[2]);
    }
  };

}

#endif /* CSFOPEULER_HPP_ */
