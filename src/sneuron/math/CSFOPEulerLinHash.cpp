/*
 * CSFOPEulerLinHash.cpp
 *
 *  Created on: May 20, 2010
 *      Author: Samir Menon
 */

#include <vector>
#include <cassert>

#include "CSFOPEulerLinHash.hpp"

#include <sneuron/math/MathFunctions.hpp>

using namespace std;

namespace sneuron
{

  bool CSFOPEulerLinHash::init(const SSFirstOrderProcessData * arg_data,
                        const snFloat& arg_init_state,
                        const snFloat& arg_dt_)
  {
    bool flag;

#ifdef SN_TESTING
    assert(SN_NULL != arg_data);
#endif

    const vector<snFloat3> * tmp = &(arg_data->fo_);

    state_start_ = (*tmp)[0].data_[0];
    state_end_ = (*tmp).back().data_[0];
    d_state_ = (*tmp)[1].data_[0] - (*tmp)[0].data_[0];
    state_size_ = (*tmp).size();

    flag = CSFOPEuler::init(arg_data,arg_init_state,arg_dt_);
    if(false == flag)
    {
      //NOTE TODO : exceptions.
#ifdef SN_TESTING
      assert(false);
#endif
      return flag;
    }

    //Verify that the supplied data is correct
    //ie that the state space vector changes linearly.
    vector<snFloat3>::const_iterator it, ite, itn;
    ite = tmp->end();
    itn = tmp->begin(); ++itn;
    for(it = tmp->begin();itn!=ite;++it,++itn)
    {
      //printf(" %lf\n", (itn->data_)[0]);
      if(false==(snFloatEquals((it->data_)[0]+d_state_,(itn->data_)[0],0.0001)))
      {
        flag = false;
#ifdef SN_TESTING
        assert(false);
#endif
        return flag;
      }
    }

    return flag;
  }

}
