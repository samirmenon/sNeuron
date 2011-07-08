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
/* \file FileFunctions.cpp
 *
 *  Created on: May 18, 2010
 *
 *  Copyright (C) 2010, Samir Menon <smenon@stanford.edu>
 */

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "FileFunctions.hpp"

#include <sneuron/WbcDataTypes.hpp>

using namespace std;
using namespace sneuron;

namespace sneuron_util
{

  bool readEigenVecFromFile(Eigen::VectorXi & arg_vec,
      const std::string & arg_file)
  {
    ifstream ipfile;
    ipfile.open(arg_file.c_str(), std::ios::in);//read only

    if(!ipfile)
    { return false; }

    std::vector<wInt> vec;
    while (!ipfile.eof())
    {
      wInt tmp;
      ipfile>>tmp;
      vec.push_back(tmp);
    }

    //Set the eigen vector's size to be equal to the
    //loaded std::vector. And then copy over the elements.
    wInt sz = vec.size();
    arg_vec.resize(sz);
    for(int i=0;i<sz;i++)
    { arg_vec[i] = vec.at(i); }

    ipfile.close();
    return true;
  }


  bool readEigenVecFromFile(Eigen::VectorXd & arg_vec, const int len,
      const std::string & arg_file)
  {
    ifstream ipfile;
    ipfile.open(arg_file.c_str(), std::ios::in);//read only

    if(!ipfile)
    { return false; }

    //  std::vector<wFloat> vec;
    //  while (!ipfile.eof())
    //  {
    //    wFloat tmp;
    //    ipfile>>tmp;
    //    vec.push_back(tmp);
    //  }

    //Set the eigen vector's size to be equal to the
    //loaded std::vector. And then copy over the elements.
    //  wInt sz = vec.size();
    //  arg_vec.resize(sz);
    for(int i=0;i<len;i++)
    { ipfile>>arg_vec(i); }

    ipfile.close();
    return true;
  }

  bool writeEigenVecToFile(const Eigen::VectorXd & arg_vec,
      const std::string & arg_file)
  {
    ofstream opfile;
    opfile.open(arg_file.c_str(),std::ios::out);//write

    if(!opfile)
    { return false; }

    //Set the eigen vector's size to be equal to the
    //loaded std::vector. And then copy over the elements.
    wInt sz = arg_vec.size();
    for(int i=0;i<sz;i++)
    { opfile<< arg_vec[i]<<"\n"; }

    opfile.close();

    return true;
  }

  bool readEigenMatFromFile(Eigen::MatrixXd & arg_mat,
      unsigned int arg_rows, unsigned int arg_cols,
      const std::string & arg_file)
  {
    try
    {
      ifstream ipfile;
      ipfile.open(arg_file.c_str(),std::ios::in);//write//read only

      if(!ipfile)
      { throw(std::runtime_error("Could not open file")); }

      arg_mat.resize(arg_rows,arg_cols);//Size the matrix

      for(unsigned int i=0;i<arg_rows;++i)
      {
        for(unsigned int j=0;j<arg_cols;++j)
        {
          if(ipfile.eof())
          {throw(std::runtime_error("Given file doesn't have data with specified dimensions")); }
          wFloat tmp;
          ipfile>>tmp;
          arg_mat(i,j) = tmp;
        }
      }

      ipfile.close();
    }
    catch(std::exception& e)
    {
      std::cerr<<"\nreadEigenMatFromFile() : "<<e.what();
      return false;
    }
    return true;
  }

  bool writeEigenMatToFile(const Eigen::MatrixXd & arg_mat,
      const std::string & arg_file)
  {
    try
    {
      ofstream opfile;
      opfile.open(arg_file.c_str(),std::ios::out);//write only

      if(!opfile)
      { throw(std::runtime_error("Could not open file")); }

      int rows = arg_mat.rows();
      int cols = arg_mat.cols();

      for(int i=0;i<rows;++i)
      {
        for(int j=0;j<cols;++j)
        {
          opfile<<arg_mat(i,j);
          opfile<<" ";
        }
        opfile<<"\n";
      }

      opfile.close();
    }
    catch(std::exception& e)
    {
      std::cerr<<"\nwriteEigenMatToFile() : "<<e.what();
      return false;
    }
    return true;
  }

}
