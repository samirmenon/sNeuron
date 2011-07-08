/*
 * MathFunctions.hpp
 *
 *  Created on: May 18, 2010
 *      Author: Samir Menon
 */

#ifndef MATHFUNCTIONS_HPP_
#define MATHFUNCTIONS_HPP_

#include <sneuron/SNDataTypes.hpp>

#include <Eigen/Core>

#include <vector>
#include <math.h>

//External math functions : Presently not-needed.
//#include <sneuron/util/MathExternal.hpp>

namespace sneuron
{

/**
 * Generates an alpha function waveform given rise and fall
 * time constants.
 *
 * Returns NULL if it fails.
 */
bool snAlphaWaveform(std::vector<snFloat>* arg_waveform,
                    const snFloat& arg_tau_rise,
                    const snFloat& arg_tau_fall);

/**
 * Generates an alpha function waveform given rise and fall
 * time constants.
 *
 * Returns NULL if it fails.
 *
 * Eigen version
 */
bool snAlphaWaveform(Eigen::VectorXd & arg_waveform,
                    const Eigen::VectorXd & arg_time,
                    const snFloat& arg_tau_rise,
                    const snFloat& arg_tau_fall);


/**
 * A float comparator function. Compares two floating point values within
 * a certain error margin.
 */
inline bool snFloatEquals(const snFloat & d1, const snFloat & d2, const snFloat & err=0.001)
{ return (fabs(d1 - d2) < err); }

/**
 * Affine sigmoid:
 *
 * Given a vector 'x', and constants 'a' and 'b' the function returns
 * 1/ (1 + exp( ax+b))
 *
 * The user must handle the memory for the returned vector.
 */
std::vector<snFloat>* snSigmoid(const std::vector<snFloat> & x,
                               const snFloat & a, const snFloat & b);

/** Performs a tanh on a vector and stores its output in another vector */
void snTanhEig(const Eigen::VectorXd &arg_v, Eigen::VectorXd &arg_exp2v,
    Eigen::VectorXd &ret_v);

/** Performs a sigmoid on a vector and stores its output in another vector */
void snSigmoidEig(const Eigen::VectorXd &arg_v, Eigen::VectorXd &arg_exp2v,
    Eigen::VectorXd &ret_v);

/** Compares two Eigen matrices */
bool snEigMatCompare(const Eigen::MatrixXd & arg_m1,
    const Eigen::MatrixXd & arg_m2);

/** Compares two Eigen vectors */
bool snEigVecCompare(const Eigen::VectorXd & arg_v1,
    const Eigen::VectorXd & arg_v2);
}
#endif /* MATHFUNCTIONS_HPP_ */
