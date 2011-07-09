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
/* \file database_tests.hpp
 *
 *  Created on: Jul 2, 2010
 *
 *  Copyright (C) 2010
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef TEST_DATABASE_HPP_
#define TEST_DATABASE_HPP_

#include <sneuron/SNDataTypes.hpp>
#include <sneuron/database/SDatabase.hpp>
#include <sneuron/util/CSingleton.hpp>
#include <sneuron/util/CSystemClock.hpp>

#include <iostream>
#include <stdexcept>

namespace sneuron_test
{
  /**
   * Tests the database
   * @param arg_id : The id of the test
   */
  void test_database(sneuron::snInt arg_id)
  {
    //sneuron::snBool flag = true;
    sneuron::snUInt test_id=0;

    try
    {
      //Temporary typedef to refrain from typing this over and over
      typedef sneuron_util::CSingleton<sneuron::SDatabase> CDb;
      sneuron::SDatabase *db, *db2;

      db = CDb::getData();
      if(NULL == db) { throw(std::runtime_error("Database returned NULL after creation")); }
      else  { std::cout<<"\nTest Result ("<<test_id++<<") Tested database not NULL"; }

      //Double check singleton mechanism
      db2 = CDb::getData();
      if(db2 != db) { throw(std::runtime_error("Singleton failed: Database pointer changed after creation")); }
      else  { std::cout<<"\nTest Result ("<<test_id++<<") Singleton works"; }

      std::cout<<"\nTest #"<<arg_id<<" (Database Test) Successful";
    }
    catch(std::exception& ee)
    {
      std::cout<<"\nTest Error ("<<test_id++<<") "<<ee.what();
      std::cout<<"\nTest #"<<arg_id<<" (Database Test) Failed";
    }
  }

}


#endif /* TEST_DATABASE_HPP_ */
