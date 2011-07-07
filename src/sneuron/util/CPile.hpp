/*
 * Copyright : Stanford University
 *
 * Author : Samir Menon (smenon@stanford.edu)
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>
 *
 *
 * CPile.hpp
 *
 *  Created on: Jun 28, 2010
 */

#ifndef CPILE_HPP_
#define CPILE_HPP_

#include <cassert>

namespace sneuron
{

/**
 * A linked list to allocate memory for objects and
 * store them, allowing pointer access.
 *
 * Main use : Manage a single data store for memory
 * that many must access.
 *
 * NOTE : Most operations on the pile are quite inefficient.
 * It is mainly intended to manage a bunch of data in a unified
 * structure while enabling pointer access.
 *
 * DO NOT use it in intensive loops.
 *
 * NOTE : This is will be replaced by CPileMap since the latter is
 * always used instead of this..
 */
template <typename T>
class CPile
{
  /**
   * A node in the linked list
   */
  template <typename TS>
  class SNode
  {
  public:
    TS* data_;
    SNode<TS> *next_;

    SNode()
    {
      data_=NULL;
      next_=NULL;
    }
  };

  /**
   * Pointers to the head of the list
   */
  SNode<T> *head_;

  int size_;

public:
  /***
   * Constructor : Does nothing.
   */
  CPile()
  { head_ = NULL; size_ = 0; }

  /***
   * Destructor : Deallocates all the nodes if someone already hasn't
   * done so.
   */
  ~CPile();

  /***
   * Creates an element, inserts an element into the list
   * and returns the pointer
   */
  T* create();

  /***
   * Copies the given element, inserts the copied element into the list
   * and returns the pointer to the copied element
   */
  T* create(const T& arg_t);

  /***
   * Returns the element at the given index
   */
  T* at(int idx);

  /***
   * Erases an element from the list
   */
  bool erase(T* arg_t);

  /***
   * Returns the size of the pile
   */
  int size(){ return size_; }

  /***
   * Clears all elements from the list
   */
  bool clear();
};

template <typename T>
CPile<T>::~CPile()
{
  SNode<T> *t, *t2;
  t = head_;
  if(SN_NULL!=t)
  { t2 = head_->next_;  }
  while(NULL!=t)
  {
    if(NULL!=t->data_)
    { delete t->data_;  }
    delete t;

    t = t2;
    if(NULL!=t)
    { t2 = t->next_;  }
  }
}

template <typename T>
T* CPile<T>::create()
{
  SNode<T> * tmp = new SNode<T>();

  if(NULL==tmp) //Memory not allocated
  { return NULL; }

  tmp->data_ = new T();
  tmp->next_ = head_;
  head_ = tmp;
  tmp = NULL;
  size_++;

  return head_->data_;
}

template <typename T>
T* CPile<T>::create(const T& arg_t)
{
  SNode<T> * tmp = new SNode<T>();

  if(NULL==tmp) //Memory not allocated
  { return NULL; }

  tmp->data_ = new T(arg_t);
  tmp->next_ = head_;
  head_ = tmp;
  tmp = NULL;
  size_++;

  return head_->data_;
}

template <typename T>
T* CPile<T>::at(int idx)
{
  if(NULL==head_)
  { return NULL;  }
  else
  {
    if(idx > size_)
    { return SN_NULL; }

    SNode<T> * t = head_;

    for(int i=0; i<idx; ++i)
    {
      assert(i<=size_);

      if(NULL==t)
      { return NULL;  }
      t = t->next_;
    }
    if(NULL==t)
    { return NULL;  }

    return t->data_;
  }
}

template <typename T>
bool CPile<T>::erase(T* arg_t)
{
  SNode<T> * t, *tpre;

  //Head is a special case
  if(head_->data_ == arg_t)
  {
    t = head_;
    head_ = head_->next_;

    if(NULL!= t->data_)
    {
      delete t->data_;
      size_--;
      delete t;
      return true; // Deleted head.
    }

    return false;//Head was NULL --> Error condition.
  }
  else
  {
    //The head doesn't match.
    tpre = head_;
    t = head_->next_;

    //Find the node
    while(NULL!=t)
    {
      if(t->data_ == arg_t)
      {
        tpre->next_ = t->next_;
        if(NULL!= t->data_)
        {
          delete t->data_;
          size_--;
          delete t;
          return true; // Deleted node.
        }
        else
        { return false; }//Node to delete was NULL --> Error condition.
      }
      tpre = t;
      t = t->next_;
    }
    return false; // Didn't delete anything.
  }//End of if/else
}

template <typename T>
bool CPile<T>::clear()
{
  SNode<T> *tpre;
  tpre = head_;

  if(tpre == NULL)
  {
    size_=0;
    return true;
  } //Nothing in the list.

  head_ = head_->next_;

  while(NULL!=tpre)
  {
    if(NULL!=tpre->data_)
    { delete tpre->data_; }
    delete tpre;

    tpre = head_;
    if(NULL==tpre)//Reached the end.
    { break; }
    head_ = head_->next_;
  }

  size_=0;
  return true;
}

}

#endif /* CPILE_HPP_ */
