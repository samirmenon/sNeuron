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
/* \file CImageAscii.cpp
 *
 *  Created on: Jan 8, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#include <sneuron/util/CImageAscii.hpp>

#include <sneuron/util/FileFunctions.hpp>
#include <sneuron/math/MathFunctions.hpp>

#include <Eigen/Core>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <ctime>


namespace sneuron
{

  CImageAscii::CImageAscii() : has_been_init_(false)
  {
    srand ( time(NULL) );

    r_ = 0;
    c_ = 0;

    sr_ = 0;
    sc_ = 0;
    stlx_ = 0;
    stly_ = 0;

    max_px_ = 0;
    min_px_ = 0;

    max_px_scaled_ = 0;
    min_px_scaled_ = 0;
  }

  CImageAscii::~CImageAscii()
  {
    // TODO Auto-generated destructor stub
  }

  bool CImageAscii::loadImage(const std::string & arg_file,
      unsigned int arg_rows,unsigned int arg_cols,
      const snBool arg_scale_px,
      const snFloat arg_min_px, const snFloat arg_max_px)
  {
    bool flag;
    try
    {
      flag = sneuron_util::readEigenMatFromFile(image_,arg_rows,arg_cols,arg_file);
      if(false==flag)
      { throw(std::runtime_error("Could not load image"));  }

      //Set max and min pixel info
      max_px_ = image_.maxCoeff();
      min_px_ = image_.minCoeff();

      //Scale the pixels.
      if(arg_scale_px)
      {
        if(!(arg_max_px > arg_min_px))
        { //If the supplied values don't make sense, set to defaults
          max_px_scaled_ = 1;
          min_px_scaled_ = 0;
        }
        else
        {
          max_px_scaled_ = arg_max_px;
          min_px_scaled_ = arg_min_px;
        }

        image_.array() -= image_.minCoeff(); //Get to zero
        image_ *= ( (max_px_scaled_ - min_px_scaled_) / (image_.maxCoeff()) ); //Scale
        image_.array() += min_px_scaled_; //Get to new min px
      }
      else
      {
        max_px_scaled_ = max_px_;
        min_px_scaled_ = min_px_;
      }

      //Convert it to a vector for later use
      int vecsz = image_.rows() * image_.cols();
      imagevec_.resize(vecsz);
      for(int i=0;i<vecsz;++i)
      { imagevec_(i) = image_(i); }

      has_been_init_ = true;
    }
    catch(std::exception& ee)
    { std::cout<<"CImageAscii::loadImage() : "<<ee.what(); }
    return has_been_init_;
  }

  Eigen::VectorXd* CImageAscii::genSubImage(
      const snInt arg_rows, const snInt arg_cols,
      const snInt arg_tlx, const snInt arg_tly)
  {
    try
    {
      if(!has_been_init_)
      { throw(std::runtime_error("No image loaded yet. Can't gen sub-image"));  }

      if(image_.rows() <= arg_rows)
      {
        std::stringstream ss;
        ss<<"Sub-image must have lesser rows ("<<arg_rows<<") than the image ("
            <<image_.rows()<<")";
        std::string str;
        str = ss.str();
        throw(std::runtime_error(str.c_str()));
      }

      if(image_.cols() <= arg_cols)
      {
        std::stringstream ss;
        ss<<"Sub-image must have lesser cols ("<<arg_cols<<") than the image ("
            <<image_.cols()<<")";
        std::string str;
        str = ss.str();
        throw(std::runtime_error(str.c_str()));
      }

      if(image_.rows() <= arg_tlx+arg_rows+1)
      {
        std::stringstream ss;
        ss<<"Sub-image top-left row ("<<arg_tlx<<") must lie within image ("
            <<image_.rows()<<")";
        std::string str;
        str = ss.str();
        throw(std::runtime_error(str.c_str()));
      }

      if(image_.cols() <= arg_tly+arg_cols+1)
      {
        std::stringstream ss;
        ss<<"Sub-image top-left col ("<<arg_tly<<") must lie within image ("
            <<image_.cols()<<")";
        std::string str;
        str = ss.str();
        throw(std::runtime_error(str.c_str()));
      }


      if(0>=arg_rows) //range 1 to image.rows()-1
      { sr_ = (rand())% (image_.rows()-2); sr_++; }
      else
      { sr_ = arg_rows; }

      if(0>=arg_cols) //range 1 to image.cols()-1
      { sc_ = (rand())% (image_.cols()-2); sc_++; }
      else
      { sc_ = arg_cols; }

      if(0>arg_tlx)
      { stlx_ = (rand())% (image_.rows()-sr_-1); }
      else
      { stlx_ = arg_tlx;  }

      if(0>arg_tly)
      { stly_ = (rand())% (image_.cols()-sc_-1); }
      else
      { stly_ = arg_tly;  }

      subimage_ = image_.block(stlx_, stly_, sr_, sc_);

      subimagevec_.resize(sr_*sc_);
      for(unsigned int i=0;i<sr_;++i)
        for(unsigned int j=0;j<sc_;++j)
        { subimagevec_(i*sc_+j) = subimage_(i,j); }

      return &subimagevec_;
    }
    catch(std::exception& ee)
    {
      std::cout<<"CImageAscii::genSubImage() : "<<ee.what();
      return SN_NULL;
    }

  }
}
