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
/* \file CSLogVecToFile.hpp
 *
 *  Created on: May 21, 2010
 *
 *  Copyright (C) 2010
 *
 *  Author: Samir Menon <smenon@stanford.edu>
 */

#ifndef CSLOGVECTOFILE_HPP_
#define CSLOGVECTOFILE_HPP_

#include <stdio.h>
#include <vector>
#include <string>

#include <sneuron/SNeuronDataTypes.hpp>
#include <sneuron/SConstants.hpp>

namespace sneuron
{

  /**
   * Takes a set of vectors of snFloats and logs them
   * to a set of files.
   *
   * Manages file i/o
   */
  class CSLogVecToFile
  {
  protected:
    /**
     * Each vector is written to a unique file.
     *
     * The name of the file is the id of the vector
     * (a) by default, or (b) if the filename is taken.
     * Eg. "./vec_log_0.txt", "./vec_log_1.txt"
     */
    std::vector<FILE *> fvec_;
    std::vector<std::string> fnames_;

    /**
     * Vector of vectors which are to be logged.
     */
    std::vector<const std::vector<snFloat>*> vec_vec_;

  public:
    /**
     * Constructor : Does nothing.
     */
    CSLogVecToFile();
    /**
     * Destructor. Closes files.
     */
    virtual ~CSLogVecToFile();

    /**
     * Adds a vector to the list along with a
     * file
     *
     * The name of the file is the id of the vector
     * (a) by default, or (b) if the filename is taken
     * and the files are stored in the same directory.
     * Eg. "./vec_log_0.txt", "./vec_log_1.txt"
     *
     * Existing logs are overwritten.
     *
     * Returns false if it can't open the output file.
     */
    bool add_vec_to_logger(std::vector<snFloat>* arg_vec,
                           const std::string& file_name="");

    /**
     * Logs all the vectors to a file
     */
    inline void log();
  };

}

#endif /* CSLOGVECTOFILE_HPP_ */
