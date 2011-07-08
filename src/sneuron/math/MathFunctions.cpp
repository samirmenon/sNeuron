/*
 * MathFunctions.cpp
 *
 *  Created on: May 18, 2010
 *      Author: Samir Menon
 */

#include <math.h>

#include <sneuron/math/MathFunctions.hpp>

#include <sneuron/SConstants.hpp>

using namespace std;

namespace sneuron
{

/**
 * Generates an alpha function waveform given rise and fall
 * time constants.
 *
 * Returns false if it fails.
 */
bool snAlphaWaveform(vector<snFloat>* arg_waveform,
                    const snFloat& arg_tau_rise,
                    const snFloat& arg_tau_fall)
{
  bool flag= false;
  if(SN_NULL == arg_waveform){ return false; }

  snFloat max=0.0,time=0.0;
  vector<snFloat>::iterator it,ite;
  ite=arg_waveform->end();

  //Compute the waveform in place
  for(it=arg_waveform->begin();it!=ite;++it)
  {
    *it = ( exp(-time/arg_tau_rise) - exp(-time/arg_tau_fall) )
                     / ( arg_tau_rise - arg_tau_fall );
    if(max < *it)
    { max = *it;  }

    time += sneuron::dt;
  }

  if(max<=0.0)
  { goto END; }

  flag = true;

  //Normalize waveform to peak at 1.
  for(it=arg_waveform->begin();it!=ite;++it)
  { *it = *it/max;  }

END:
  return flag;
}

bool snAlphaWaveform(Eigen::VectorXd & arg_waveform,
                     const Eigen::VectorXd & arg_time,
                     const snFloat& arg_tau_rise,
                     const snFloat& arg_tau_fall)
{
  arg_waveform.resize(arg_time.size());

  //Compute the waveform in place
  Eigen::VectorXd t1 = arg_time /  (-1*arg_tau_rise);
  Eigen::VectorXd t2 =  arg_time / (-1*arg_tau_fall);

  Eigen::VectorXd tmp1, tmp2;

  //NOTE TODO : Fix this.
//  tmp1 = t1.cwise().exp();
//  tmp2 = t2.cwise().exp();
//
//  arg_waveform =  tmp1 - tmp2;
//  arg_waveform /= ( arg_tau_rise - arg_tau_fall );
//
//  snFloat max = arg_waveform.maxCoeff();
//  if(max<=0.0) { return false; }
//
//  //Normalize waveform to peak at 1.
//  arg_waveform /= max;
//
  return true;
}

/**
 * Affine sigmoid:
 *
 * Given a vector 'x', and constants 'a' and 'b' the function returns
 * y = 1/ (1 + exp( ax+b))
 *
 * The user must handle the memory for the returned vector.
 */
std::vector<snFloat>* snSigmoid(const std::vector<snFloat> & x,
                               const snFloat & a, const snFloat & b)
  {
    std::vector<snFloat>* y = new std::vector<snFloat>();
    y->resize(x.size(),0.0);

    std::vector<snFloat>::const_iterator it, ite;
    ite = x.end();

    std::vector<snFloat>::iterator ity,itye;
    itye = y->end();

    for(it = x.begin(),ity=y->begin(); (it!=ite) && (ity!=itye); ++it,++ity)
    {
      snFloat tmp = 1 / (1+ exp(a*(*it) + b));
      (*ity) = tmp;
    }

    return y;
  }

/** Performs a tanh on a vector and stores its output in another vector */
void snTanhEig(const Eigen::VectorXd &arg_v, Eigen::VectorXd &arg_exp2v,
    Eigen::VectorXd &ret_v)
{
  arg_exp2v = arg_v.cwise().exp().cwise().pow(2);
  ret_v = (arg_exp2v.cwise()-1).cwise() / (arg_exp2v.cwise()+1);
}

/** Performs a sigmoid on a vector and stores its output in another vector */
void snSigmoidEig(const Eigen::VectorXd &arg_v, Eigen::VectorXd &arg_exp2v,
    Eigen::VectorXd &ret_v)
{
  arg_exp2v = arg_v.cwise().exp();
  ret_v = arg_exp2v.cwise() / (arg_exp2v.cwise()+1);
}

/** Compares two Eigen matrices */
bool snEigMatCompare(const Eigen::MatrixXd & arg_m1,
    const Eigen::MatrixXd & arg_m2)
{
  if(arg_m1.rows()!=arg_m2.rows())
  { std::cerr<<"\nsnEigMatCompare() : Row mismatch."; return false; }
  if(arg_m1.cols()!=arg_m2.cols())
  { std::cerr<<"\nsnEigMatCompare() : Col mismatch."; return false; }

  for(int i=0; i< arg_m1.rows(); ++i)
    for(int j=0; j< arg_m1.cols(); ++j)
      if(!snFloatEquals(arg_m1(i,j),arg_m2(i,j),0.0000001))
        { std::cerr<<"\nsnEigMatCompare() : Element mismatch ["<<i<<", "<<j<<"] ("
        <<arg_m1(i,j)<<") VS ("<<arg_m2(i,j)<<")"; return false; }
  return true;
}


/** Compares two Eigen vectors */
bool snEigVecCompare(const Eigen::VectorXd & arg_v1,
    const Eigen::VectorXd & arg_v2)
{
  if(arg_v1.size()!=arg_v2.size())
  { std::cerr<<"\nsnEigMatCompare() : Size mismatch."; return false; }

  for(int i=0; i< arg_v1.size(); ++i)
      if(!snFloatEquals(arg_v1(i),arg_v2(i),0.0000001))
        { std::cerr<<"\nsnEigVecCompare() : Element mismatch ["<<i<<"] ("
        <<arg_v1(i)<<") VS ("<<arg_v2(i)<<")"; return false; }
  return true;
}

}




