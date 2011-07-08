/*
 * CSFirstOrderProcess.hpp
 *
 *  Created on: May 19, 2010
 *      Author: Samir Menon
 */

#ifndef CSFIRSTORDERPROCESS_HPP_
#define CSFIRSTORDERPROCESS_HPP_

#include <string>
#include <vector>

#include <sneuron/SNeuronDataTypes.hpp>
#include <sneuron/SConstants.hpp>

namespace sneuron
{
  /**
   * Contains the information needed to run
   * a first order process
   */
  struct SSFirstOrderProcessData
  {
    /**
     * The name of the first order process
     */
    std::string name_;
    /**
     * The data vector:
     * <state var, first order var steady state, first order var time constt>
     */
    std::vector<snFloat3> fo_;
  };

  /**
   * A generic first order process base class.
   * Each first order process has to implement a hash function
   * (or something similar) which can look up an index for the first
   * order data (data_->fo_) given a state variable value.
   *
   * To Use : Subclass and implement the get_idx() function, and the
   * integrate() function.
   */
  class CSFirstOrderProcess
  {
  protected:
    /**
     * The first order process can't modify its
     * behavior.
     */
    const std::vector<snFloat3>* data_;
    /**
     * The first order variable
     */
    snFloat fo_var_;
    /**
     * The state data index
     */
    snUInt fo_idx_;
    /**
     * A pointer to the current data
     */
    const snFloat *data_slice_;

    /**
     * The name of the fop
     */
    std::string name_;

  public:
    CSFirstOrderProcess();
    virtual ~CSFirstOrderProcess();
    /**
     * Initialize the first order process
     */
    bool init(const SSFirstOrderProcessData * arg_data,
              const snFloat& arg_init_state);

    /**
     * Gets the current first order variable's value
     */
    inline snFloat get_fo_var()
    { return fo_var_; }

    /**
     * Gets the current goal fo_var value (steady state)
     */
    inline snFloat get_fo_ss()
    { return data_slice_[1]; }

    /**
     * Gets the current first order variable's time constant
     */
    inline snUInt get_fo_idx()
    { return fo_idx_; }

#ifdef SN_TESTING
    /**
     * Test function
     * @param arg_statevar
     */
    inline const snFloat * get_data_slice()
    { return data_slice_; }
#endif

    /**
     * Recomputes the first order variable given an updated
     * state variable value.
     */
    inline void set_state(const snFloat& arg_statevar)
    {
      //Get current state data
      fo_idx_ = get_idx(arg_statevar);
      //NOTE TODO : Some error handling for when the value doesn't
      //match anything
      data_slice_ = (*data_)[fo_idx_].data_;
    }

    /**
     * Recomputes the first order variable given an updated
     * state variable index (faster than update by value).
     */
    inline void set_state_idx(const snUInt arg_statevar_idx)
    {
      //Get current state data
      fo_idx_ = arg_statevar_idx;
      //NOTE TODO : Some error handling for when the index doesn't
      //match anything
      data_slice_ = (*data_)[fo_idx_].data_;
    }

    /**
     * Sets the first order variable to its steady state.
     * Useful for resets.
     */
    inline void set_to_steady_state()
    { fo_var_ = get_fo_ss();  }

    /**
     * Maps the value of the state variable to the corresponding
     * index of the first order data vector
     */
    virtual inline void integrate()=0;

  protected:
    /**
     * Maps the value of the state variable to the corresponding
     * index of the first order data vector
     */
    virtual inline snUInt get_idx(const snFloat & arg_state)=0;
  };

}

#endif /* CSFIRSTORDERPROCESS_HPP_ */

