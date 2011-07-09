/* This file is part of Sneuron, a control and simulation library
for neural networks.

Sneuron is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

Alternatively, you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

Sneuron is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License and a copy of the GNU General Public License along with
Sneuron. If not, see <http://www.gnu.org/licenses/>.
*/
/* \file CSingleton.hpp
 *
 *  Created on: Jul 8, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef CSINGLETON_HPP_
#define CSINGLETON_HPP_

namespace sneuron_util
{

  template<typename SDataStruct>
  class CSingleton
  {
  private:
    /** Shared Memory: The publicly available data that will be
     * shared across the different subsystems */
    SDataStruct data_;

  public:
    /** The function used to get the data */
    static SDataStruct* getData();

    /** Default destructor : Does nothing */
    virtual ~CSingleton();

  private:
    /** Private constructor : for the singleton */
    CSingleton(){}

    /** Private constructor : for the singleton */
    CSingleton(const CSingleton&){}

    /** Private operator : for the singleton */
    CSingleton& operator= (const CSingleton&){}
  };

  template<typename SDataStruct>
  SDataStruct* CSingleton<SDataStruct>::getData()
  {
    /** The singleton instance */
    static CSingleton* db = NULL;

    if (NULL == db)  // is it the first call?
    {
      db = new CSingleton<SDataStruct>(); // create sole instance
      if(NULL == db)
      {
        std::cout<<"\nCDatabase::createDb() Error: Could not dynamically allocate the database";
        return NULL;
      }
    }
    return &(db->data_);
  }

  template<typename SDataStruct>
  CSingleton<SDataStruct>::~CSingleton()
  {
    //NOTE TODO : Implement this
  }
}

#endif /* CSINGLETON_HPP_ */
