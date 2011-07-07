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
/* \file CDatabase.cpp
 *
 *  Created on: May 19, 2010
 *
 *  Copyright (C) 2010
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#include <wbc/database/CDatabase.hpp>

#include <stdexcept>

namespace wbc_util
{
  //*****************************************************************
  //                  Dynamic Typing Code
  //*****************************************************************
  CDatabase::~CDatabase()
  {
    std::map<std::string,CDynamicTypeBase*>::iterator it, ite;
    for(it = typemap_.begin(), ite = typemap_.end();
        it!=ite; ++it)
    { delete (*it).second;  }
  }

  bool CDatabase::registerType(const std::string& arg_type,
      CDynamicTypeBase& arg_dyn_type_creator)
  {
    try
    {
      //We will create a new object of this type and use it to create other
      //objects of this type.
      //NOTE : If the arg_dyn_type_creator object stores the pointer and
      //deletes it later, the CDatabase object will crash
      //at the destructor, and other stuff might crash earlier.
      CDynamicTypeBase* tmp;
      tmp = dynamic_cast<CDynamicTypeBase*>(arg_dyn_type_creator.createDynamicTypeSubclass());
      if(tmp == NULL)
      { throw(std::runtime_error("The passed object's createObject() function did not work.")); }

      if(typemap_.find(arg_type) != typemap_.end())
      { throw(std::runtime_error("The passed type is already registered.")); }

      typemap_.insert(std::pair<std::string,CDynamicTypeBase*>(arg_type,tmp));
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr<<"\nCDatabase::registerType() Error : "<<e.what();
      return false;
    }
  }

  bool CDatabase::getObjectForType(const std::string & arg_type,
      void*& ret_object)
  {
    try
    {
      if(typemap_.find(arg_type) == typemap_.end())
      { throw(std::runtime_error("The passed type has not been registered.")); }

      if(ret_object != NULL)
      { throw(std::runtime_error("The passed void* pointer is not NULL.")); }

      if(typemap_[arg_type] == NULL)
      { throw(std::runtime_error("The typemap is corrupted. A typecreator object pointer is NULL.")); }

      //Be really careful.
      ret_object = typemap_[arg_type]->createObject();
      if(ret_object == NULL)
      { throw(std::runtime_error("The type's object's createObject() function did not work.")); }

      return true;
    }
    catch(std::exception& e)
    {
      std::cerr<<"\nCDatabase::getObjectForType() Error : "<<e.what();
      return false;
    }
  }

  //*****************************************************************
  //                      Singleton Code
  //*****************************************************************
  CDatabase* CDatabase::db_ = NULL;// initialize pointer

  CDatabase::CDatabase(){}

  CDatabase* CDatabase::getDb()
  {
    if (db_ == NULL)  // is it the first call?
    { return NULL; }// Do nothing
    return db_; // address of sole instance
  }

  bool CDatabase::createDb()
  {
    try
    {
      if (db_ == NULL)  // is it the first call?
      {
        db_ = new CDatabase(); // create sole instance
        if(W_NULL == db_)
        { throw(std::runtime_error("Could not dynamically allocate the database"));  }
      }
      return true;
    }
    catch(std::exception& ee)
    {
      std::cerr<<"CDatabase::createDb() : "<<ee.what();
      return false;
    }
  }

  void CDatabase::destroyDb()
  {
    if (db_ != NULL)  // is it the first call?
    { delete db_; } //delete the instance
    db_ = W_NULL;
  }
}
