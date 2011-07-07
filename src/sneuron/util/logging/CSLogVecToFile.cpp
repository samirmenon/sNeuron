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
/* \file CSLogVecToFile.cpp
 *
 *  Created on: May 21, 2010
 *
 *  Copyright (C) 2010
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#include <stdlib.h>
#include <cassert>
#include <sstream>

#include "CSLogVecToFile.hpp"

using namespace std;

namespace sneuron
{

  CSLogVecToFile::CSLogVecToFile()
  {}

  CSLogVecToFile::~CSLogVecToFile()
  {
    //Close all the file streams
    vector<FILE *>::iterator it, ite;
    ite = fvec_.end();
    for(it=fvec_.begin();it != ite; ++it)
    {
      if(NULL!=(*it))
      { fclose((*it));  }
    }
  }

  bool CSLogVecToFile::add_vec_to_logger(std::vector<snFloat>* arg_vec,
      const std::string& file_name)
  {
    //It should log some vector
    if(SN_NULL == arg_vec)
    {
#ifdef SN_ENABLE_ASSERTS
      assert(false);
#endif
      return false;
    }

    //Check whether the logger already contains the vector
    std::vector<const std::vector<snFloat>*>::iterator it, ite;
    ite = vec_vec_.end();
    for(it=vec_vec_.begin();it != ite; ++it)
    {
      if(*it == arg_vec)
      {//Vector is already being logged
#ifdef SN_ENABLE_ASSERTS
      assert(false);
#endif
        return false;
      }
    }

    std::string outfile=file_name;
    //Check if the file is already open
    std::vector<string>::iterator itf, itfe;
    itfe = fnames_.end();
    for(itf=fnames_.begin();itf != itfe; ++itf)
    {
      if(outfile==*itf)
      {//File exists
        stringstream ss;
        ss<<vec_vec_.size();
        outfile = "./vec_log_" + ss.str() +".txt";
        break;
      }
    }

    //Open the file.
    FILE* f = fopen(outfile.c_str(),"r");
    if(SN_NULL == f)
    {//Couldn't open file
#ifdef SN_ENABLE_ASSERTS
      assert(false);
#endif
      return false;
    }
    fvec_.push_back(f);
    fnames_.push_back(outfile);
    vec_vec_.push_back(arg_vec);

    return true;
  }

  inline void CSLogVecToFile::log()
  {
    std::vector<const std::vector<snFloat>*>::iterator it, ite;
    std::vector<FILE*>::iterator itf, itfe;

    ite = vec_vec_.end();
    for(it=vec_vec_.begin();it != ite; ++it,++itf)
    {
#ifdef SN_ENABLE_ASSERTS
      if(itf==itfe)
        assert(false);
#endif
      //Dump the vector into the file
      std::vector<snFloat>::const_iterator itv,itve;
      itve = (*it)->end();
      for(itv=(*it)->begin();itv != itve; ++itv)
      {
        fprintf((*itf)," %lf", (*itv));
      }
      fprintf((*itf),"\n");
    }
  }

}
