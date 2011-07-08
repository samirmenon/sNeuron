/*
 * CSFirstOrderProcess.cpp
 *
 *  Created on: May 19, 2010
 *      Author: Samir Menon
 */

#include <cassert>

#ifdef SN_TESTING
#include <iostream>
#endif

#include "CSFirstOrderProcess.hpp"

#include <sneuron/math/MathFunctions.hpp>

namespace sneuron
{

  CSFirstOrderProcess::CSFirstOrderProcess()
  {
    fo_var_=0;
    fo_idx_=-1;
    data_=SN_NULL;
  }

  CSFirstOrderProcess::~CSFirstOrderProcess()
  {}

  /**
   * Initialize the first order process
   */
  bool CSFirstOrderProcess::init(const SSFirstOrderProcessData * arg_data,
      const snFloat& arg_init_statevar)
  {
    data_ = &(arg_data->fo_);
    fo_idx_ = get_idx(arg_init_statevar);
    data_slice_ = data_->at(fo_idx_).data_;
    name_ = arg_data->name_;
    /**
     * TODO Handle error if idx not found.
     * Throw exception and handle it in the calling
     * function(s).
     * Alt : Return false.
     */
    //Hash function is working properly.
#ifdef SN_TESTING
    if(!snFloatEquals(data_slice_[0],arg_init_statevar,0.05))
    {
      std::cout<<"\nError : data_slice = "
        <<data_slice_[0]
        <<"statevar = "<<arg_init_statevar
        <<std::endl;
      assert(false);
    }
#endif

    fo_var_ = data_slice_[1];

    return true;
  }

}
