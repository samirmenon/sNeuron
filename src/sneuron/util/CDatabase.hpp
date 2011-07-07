/* This file is part of Busylizzy, a control and simulation library
for robots and biomechanical models.

Busylizzy is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

Alternatively, you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

Busylizzy is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License and a copy of the GNU General Public License along with
Busylizzy. If not, see <http://www.gnu.org/licenses/>.
*/
/* \file CDatabase.hpp
 *
 *  Created on: Jul 2, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

/** \file CDatabase.hpp */

#ifndef CDATABASE_HPP_
#define CDATABASE_HPP_

#include <wbc/util/CDynamicTypeBase.hpp>

namespace wbc_util
{
  /** A Database is a singleton object that implements:
   *
   * 1. Shared memory for objects and/or threads across a process.
   * 2. Dynamic typing for custom user types.
   *
   * Typically, a program contains/uses only ONE such object.
   *
   * Note: This class requires a call to createDb to create the
   * database and a call to destroyDb to delete it.
   *
   * TODO : Thread safety : 1-writer + n-readers for different
   * subcomponents */
  template <typename SDataStruct>
  class CDatabase {
    //*****************************************************************
    //                  Shared Memory Code
    //*****************************************************************
  public:
    /** The publicly available data that will be shared across
     * the different subsystems */
    SDataStruct data_;

    //*****************************************************************
    //                  Dynamic Typing Code
    //*****************************************************************
  public:
    /** Support for dynamic type instantiation */
    bool registerType(const std::string& arg_type,
        wbc_util::CDynamicTypeBase& arg_dyn_type_creator);

    bool getObjectForType(const std::string & arg_type,
        void*& ret_object);

    /** The destructor deletes the (factory) objects in the typemap */
    ~CDatabase();

  private:
    /** A map to store the various dynamic types */
    std::map<std::string,wbc_util::CDynamicTypeBase*> typemap_;

    //*****************************************************************
    //                      Singleton Code
    //*****************************************************************
  public:
    /** Accessor function to database singleton
     * @return Returns the singleton database if it has been created */
    static CDatabase* getDb();

    /** Creates the singleton database */
    static bool createDb();

    /** Destroys the singeton database */
    static void destroyDb();

  private:
    /** Private constructor : for the singleton */
    CDatabase();

    /** Private constructor : for the singleton */
    CDatabase(const CDatabase&);

    /** Private operator : for the singleton */
    CDatabase& operator= (const CDatabase&);

    /** The singleton instance */
    static CDatabase* db_;
  };

}

#endif /* CDATABASE_HPP_ */
