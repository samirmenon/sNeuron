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
/* \file CImageAscii.hpp
 *
 *  Created on: Jan 8, 2011
 *
 *  Copyright (C) 2011
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef CIMAGEASCII_HPP_
#define CIMAGEASCII_HPP_

#include <string>

#include <Eigen/Core>

#include <sneuron/SNeuronDataTypes.hpp>

namespace sneuron
{
  /** Operations on a grayscale image stored in an ASCII file. */
  class CImageAscii
  {
  public:
    /** Constructor does nothing */
    CImageAscii();

    /** Destructor does nothing */
    virtual ~CImageAscii();

    /** Loads an image (a matrix stored in an ascii file).
     * Also scales the image's pixel intensities, if required.
     * Default scaling is between 0 and 1
     *
     * @param arg_file : The file to load an image matrix from
     * @param arg_rows : The rows in the image matrix
     * @param arg_cols : The columns in the image matrix
     * @param arg_scale_px : Whether to scale the pixel intensities
     * @param arg_min_px : The minimum pixel intensity
     * @param arg_max_px : The maximum pixel intensity
     * @return : true if successful
     */
    bool loadImage(const std::string & arg_file,
        const snUInt arg_rows, const snUInt arg_cols,
        const snBool arg_scale_px = false,
        const snFloat arg_min_px=0.0, const snFloat arg_max_px=1.0);

    /**
     * Samples a patch out of the present image and returns a pointer to it.
     * If rows, cols, tlx or tly are -1 (default), it randomizes the values.
     *
     * @param arg_rows : The rows in the sub-image
     * @param arg_cols : The columns in the sub-image
     * @param arg_tlx : Top left x
     * @param arg_tly : Top left y
     * @return : A pointer to the sub-image vector
     */
    Eigen::VectorXd* genSubImage(
        const snInt arg_rows=0, const snInt arg_cols=0,
        const snInt arg_tlx=-1, const snInt arg_tly=-1);

    /** Returns a reference to the image */
    Eigen::MatrixXd & getImage()
    { return image_;  }

    /** Returns an image as a vector */
    Eigen::VectorXd & getImageAsVec()
    { return imagevec_; }

    /** Returns a reference to the image */
    Eigen::MatrixXd & getSubImage()
    { return subimage_;  }

    /** Returns an image as a vector */
    Eigen::VectorXd & getSubImageAsVec()
    { return subimagevec_; }

  private:
    /** Grayscale image as a matrix */
    Eigen::MatrixXd image_;

    /** Matrix unfolded into a vector : Column major */
    Eigen::VectorXd imagevec_;

    /** Cache a generated subimage */
    Eigen::MatrixXd subimage_;

    /** Cache a generated subimage as a vector */
    Eigen::VectorXd subimagevec_;

    //! Rows, columns of the entire image
    snUInt r_, c_;

    //! Rows, columns, top left of the current sub-image
    snUInt sr_, sc_, stlx_, stly_;

    //! Max, min pixel intensity (for restoring a scaled image)
    snFloat max_px_, min_px_;

    //! Max, min pixel intensity (for scaling an image)
    snFloat max_px_scaled_, min_px_scaled_;

    /** Whether it has loaded an image */
    bool has_been_init_;
  };
}

#endif /* CIMAGEASCII_HPP_ */
