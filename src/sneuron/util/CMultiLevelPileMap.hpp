/* This file is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

Alternatively, you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This file is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License and a copy of the GNU General Public License along with
this file. If not, see <http://www.gnu.org/licenses/>.
*/
/* \file CMultiLevelPileMap.hpp
 *
 *  Created on: Jun 28, 2010
 *
 *  Copyright (C) 2010, Samir Menon <smenon@stanford.edu>
 */

#ifndef CMULTILEVELPILEMAP_HPP_
#define CMULTILEVELPILEMAP_HPP_

#include <sneuron/util/CPileMap.hpp>

#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

namespace sneuron
{

  /**
   * This template class contains a multi level linked list.
   *
   * It is an extension of a PileMap, which itself is a
   * collection of pointers (memory managed) stored in a
   * linked list.
   */
  template <typename Idx, typename T>
  class CMultiLevelPileMap  : public CPileMap<Idx,T>
  {
  public:
    /** Constructor : Empties the data structure */
    CMultiLevelPileMap();

    /** Destructor : Deallocates all the nodes if someone already hasn't
     * done so. */
    virtual ~CMultiLevelPileMap();

    /** Adds a node to the pilemap and inserts its vector into
     * the appropriate slot in the vector-list */
    virtual T* create(const Idx& arg_idx, const T &arg_node2add,
        const wUInt arg_priority);

    /** Adds a node to the pilemap and inserts its vector into
     * the appropriate slot in the vector-list. Uses the copy-constructor. */
    virtual T* create(const Idx& arg_idx, const wUInt arg_priority);

    /** Copy-Constructor : Does a deep copy of the branching structure to
     *  get a new one.
     * NOTE : This uses the passed pilemap's iterator construct. */
    virtual bool deepCopy(CMultiLevelPileMap<Idx,T>* arg_br);

    /** Erases an element from the list.
     * Referenced by the element's memory location */
    virtual bool erase(T* arg_t);

    /** Erases an element from the list.
     * Referenced by its index */
    virtual bool erase(const Idx& arg_idx);

    /** Clears all elements from the list */
    virtual bool clear();

    /** Returns the tasks at a level */
    std::vector<T*>* getSinglePriorityLevel(wUInt arg_pri);

    wUInt getNumPriorityLevels() const
    { return pri_levels_; }

    /** Returns the priority level of the element
     * Note: This returns an int because -1 is the error
     * condition*/
    wInt getPriorityLevel(T* arg_t);

    /** Returns the priority level of the element pointed
     * to by the index
     * Note: This returns an int because -1 is the error
     * condition*/
    wInt getPriorityLevel(const Idx & arg_idx);

    /** Create a node on the pilemap and also insert it into the vector
     * of lists. That way someone can lookup or iterate over the pilemap
     * and can also exploit the structure of the vec<list>
     */
    std::vector<std::vector<T*> > mlvec_;

  protected:
    /** Maintain a map of the node pointer to the priority levels as
     * well. This allows chaining to find out the pri level even from
     * the index (pri == map_nodeptr2pri_[map_[idx]]) &&
     * (pri == map_nodeptr2pri_[nodeptr]) */
    std::map<T*, wUInt> map_nodeptr2pri_;

    /** The priority levels this multi-level map has */
    wUInt pri_levels_;
  }; //End of template class

  /***************************************************************
   *******************************Function Definitions*************
   ****************************************************************
   */

  /**
   * Constructor. Sets default values.
   */
  template <typename Idx, typename T>
  CMultiLevelPileMap<Idx,T>::CMultiLevelPileMap() :
  CPileMap<Idx,T>::CPileMap()
  { mlvec_.clear(); pri_levels_ = 0; }

  /**
   * Does nothing itself.
   * Calls CPileMap::~CPileMap() which
   * destroys the (dynamically allocated)
   * nodes in the node linked list.
   */
  template <typename Idx, typename T>
  CMultiLevelPileMap<Idx,T>::~CMultiLevelPileMap()
  { mlvec_.clear(); map_nodeptr2pri_.clear(); pri_levels_=0; }


  /**
   * Adds a node at the given level and returns its address.
   */
  template <typename Idx, typename T>
  T* CMultiLevelPileMap<Idx,T>::create(
      const Idx& arg_idx, const T & arg_node2add,
      const wUInt arg_priority)
  {
    //Add the node.
    T* tLnk = CPileMap<Idx,T>::create(arg_idx,arg_node2add);

    if(NULL!=tLnk)
    {
      for(wUInt i=mlvec_.size(); i <= arg_priority; i++)
      {
        std::vector<T*> tmp;
        mlvec_.push_back(tmp);
        pri_levels_++;//Every push back increases pri levels.
      }
      mlvec_[arg_priority].push_back(tLnk);
      map_nodeptr2pri_.insert(std::pair<T*,wUInt>(tLnk,arg_priority));
    }
    return tLnk;
  }

  template <typename Idx, typename T>
  T* CMultiLevelPileMap<Idx,T>::create(
      const Idx& arg_idx, const wUInt arg_priority)
  {
    //Add the node.
    T* tLnk = CPileMap<Idx,T>::create(arg_idx);

    if(NULL!=tLnk)
    {
      for(wUInt i=mlvec_.size(); i <= arg_priority; i++)
      {
        std::vector<T*> tmp;
        mlvec_.push_back(tmp);
        pri_levels_++;//Every push back increases pri levels.
      }
      mlvec_[arg_priority].push_back(tLnk);
      map_nodeptr2pri_.insert(std::pair<T*,wUInt>(tLnk,arg_priority));
    }

    return tLnk;
  }

  template <typename Idx, typename T>
  bool CMultiLevelPileMap<Idx,T>::
  deepCopy(CMultiLevelPileMap<Idx,T>* arg_br)
  {//Deep copy.
    try
    {
    this->~CMultiLevelPileMap(); //Delete everything in the pilemap

    /**Set the current pilemap to the new pilemap**/
    if(0 == arg_br->size())
    {
      CPileMap<Idx,T>::head_ = W_NULL;
      CPileMap<Idx,T>::map_.clear();
      CPileMap<Idx,T>::size_ = 0;
      mlvec_.clear(); map_nodeptr2pri_.clear();
    }
    else
    {
      arg_br->resetIterator();
      while(arg_br->iterator_!=W_NULL)
      {
        T* tmp = CPileMap<Idx,T>::create(*(arg_br->iterator_->id_),
        *(arg_br->iterator_->data_));
        if(W_NULL == tmp)
        { throw(std::runtime_error("Deep copy failed. Resetting multi-level pilemap.")); }

        //Now recreate the priority map
        if(arg_br->map_nodeptr2pri_.find(tmp) ==
            arg_br->map_nodeptr2pri_.end())
        { throw(std::runtime_error("Did not find a node in the priority map.")); }

        wUInt pri = arg_br->map_nodeptr2pri_[tmp];
        map_nodeptr2pri_.insert(std::pair<T*,wUInt>(tmp,pri));

        //Now add the entry to the vector
        for(wUInt i=mlvec_.size(); i <= pri; i++)
        {
          std::vector<T*> tmp;
          mlvec_.push_back(tmp);
          pri_levels_++;//Every push back increases pri levels.
        }
        mlvec_[pri].push_back(tmp);

        //Move the iterator along
        arg_br->iterator_ = arg_br->iterator_->next_;
      }
      arg_br->resetIterator();
    }
    }
    catch(std::exception &e)
    {
      std::cerr<<"\nCMultiLevelPileMap<Idx,T>::deepCopy() Error :"<<e.what();
      clear();//Reset the pilemap.
      return false;
    }
    return true;
  }

  template <typename Idx, typename T>
  bool CMultiLevelPileMap<Idx,T>::erase(T* arg_t)
  {
    bool flag;
    if((W_NULL==CPileMap<Idx,T>::head_) || (W_NULL==arg_t))
    { return false;  }
    else
    {
      if(map_nodeptr2pri_.find(arg_t) ==
          map_nodeptr2pri_.end())
      { return false; }

      wUInt pri = map_nodeptr2pri_[arg_t];

      //Remove it from the priority level vectors
      typename std::vector<T*>::iterator it,ite;
      for(it = mlvec_[pri].begin(),ite = mlvec_[pri].end();
          it!=ite; ++it)
      {
        if(*it == arg_t)
        { mlvec_[pri].erase(it); break; }
      }

      if(pri == pri_levels_ -1)//Deleted from lowest level.
      {
        if(mlvec_[pri].size()==0)
        {//If last one is now empty, remove it (and others if possible)
          typename std::vector<std::vector<T*> >::reverse_iterator itr,itre;
          for(itr = mlvec_.rbegin(),itre = mlvec_.rend();
              itr!=itre; ++itr)
          {
            if((*itr).size() == 0)
              //Use rev_iter.base() func to convert it to normal iter
              //Can only erase a normal iter
              //reverse iterator points to one element closer to begin
              //than the base() function
            { mlvec_.erase((itr+1).base()); }
            else
            { break;  }
          }
        }
      }

      //Remove it from the nodeptr2pri map
      map_nodeptr2pri_.erase(arg_t);

      //Remove it from the pilemap (deallocate memory)
      flag = CPileMap<Idx,T>::erase(arg_t);
      if(false == flag)
      { return false; }
    }
    pri_levels_ = mlvec_.size();
    return true;
  }

  template <typename Idx, typename T>
  bool CMultiLevelPileMap<Idx,T>::erase(const Idx& arg_idx)
  {
    bool flag;
    if(W_NULL==CPileMap<Idx,T>::head_)
    { return false;  }
    else
    {
      T* t_ptr = CPileMap<Idx,T>::at(arg_idx);
      if(W_NULL == t_ptr)
      { return false; }

      if(map_nodeptr2pri_.find(t_ptr) ==
          map_nodeptr2pri_.end())
      { return false; }

      wUInt pri = map_nodeptr2pri_[t_ptr];

      //Remove it from the priority level vectors
      typename std::vector<T*>::iterator it,ite;
      for(it = mlvec_[pri].begin(),ite = mlvec_[pri].end();
          it!=ite; ++it)
      {
        if(*it == t_ptr)
        { mlvec_[pri].erase(it); break; }
      }

      if(pri == pri_levels_ -1)//Deleted from lowest level.
      {
        if(mlvec_[pri].size()==0)
        {//If last one is now empty, remove it (and others if possible)
          typename std::vector<std::vector<T*> >::reverse_iterator itr,itre;
          for(itr = mlvec_.rbegin(),itre = mlvec_.rend();
              itr!=itre; ++itr)
          {
            if((*itr).size() == 0)
              //Use rev_iter.base() func to convert it to normal iter
              //Can only erase a normal iter
              //reverse iterator points to one element closer to begin
              //than the base() function
            { mlvec_.erase((itr+1).base()); }
            else
            { break;  }
          }
        }
      }

      //Remove it from the nodeptr2pri map
      map_nodeptr2pri_.erase(t_ptr);

      //Remove it from the pilemap (deallocate memory)
      flag = CPileMap<Idx,T>::erase(arg_idx);
      if(false == flag)
      { return false; }
    }
    pri_levels_ = mlvec_.size();
    return true;
  }
  template <typename Idx, typename T>
    bool CMultiLevelPileMap<Idx,T>::clear()
    {
      CPileMap<Idx,T>::clear();
      mlvec_.clear();
      map_nodeptr2pri_.clear();
      pri_levels_=0;
      return true;
    }

  template <typename Idx, typename T>
  std::vector<T*>* CMultiLevelPileMap<Idx,T>::
  getSinglePriorityLevel(wUInt arg_pri)
  {
    if(arg_pri > mlvec_.size())
    { return NULL;  }
    else
    {
      std::vector<T*>* ret = &(mlvec_.at(arg_pri));
      return ret;
    }
  }

  template <typename Idx, typename T>
  wInt CMultiLevelPileMap<Idx,T>::
  getPriorityLevel(T* arg_t)
  {
    wInt ret;
    if(map_nodeptr2pri_.find(arg_t) ==
        map_nodeptr2pri_.end())
    { ret = -1; }
    else
    { ret = static_cast<wInt>(map_nodeptr2pri_[arg_t]);  }

    return ret;
  }

  template <typename Idx, typename T>
  wInt CMultiLevelPileMap<Idx,T>::
  getPriorityLevel(const Idx & arg_idx)
  {
    T* t_ptr = CPileMap<Idx,T>::at(arg_idx);
    if(W_NULL == t_ptr)
    { return -1;  }

    wInt ret;
    if(map_nodeptr2pri_.find(t_ptr) ==
        map_nodeptr2pri_.end())
    { ret = -1; }
    else
    { ret = static_cast<wInt>(map_nodeptr2pri_[t_ptr]);  }

    return ret;
  }

}//End of namespace sneuron_util

#endif /*CMULTILEVELPILEMAP_HPP_*/
