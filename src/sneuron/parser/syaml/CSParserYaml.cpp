/*
 * CSParserYaml.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: samir
 */

#include "CSParserYaml.hpp"

#include <iostream>
#include <stdexcept>

namespace sneuron
{

  CSParserYaml::CSParserYaml()
  {
    // TODO Auto-generated constructor stub
  }

  CSParserYaml::~CSParserYaml()
  {
    // TODO Auto-generated destructor stub
  }

  /** Returns a list of the neural networks in the file */
  virtual bool listNetworksInFile(const std::string& arg_file,
      std::vector<sneuron::string2>& arg_network_name_type)
  {
    bool flag;
    try
    {
      /** Add code to read network names from a file here */
      return true;
    }
    catch(std::exception& e)
    { std::cerr<<"\nCSParserYaml::listNetworksInFile() Error : "<<e.what(); }
    return false;
  }

  /** Reads in a neural network from the given file. */
  bool CSParserYaml::readNetworkFromFile(const std::string& arg_file,
      /** The network which will be read into the passed data structure */
      const std::string& arg_network_name,
      /** The network's data will be filled into this data structure */
      sneuron::SNeuralNetwork& arg_network)
  {
    bool flag;
    try
    {
      /** Add code to read a network from a file here */
      return true;
    }
    catch(std::exception& e)
    { std::cerr<<"\nCSParserYaml::listNetworksInFile() Error : "<<e.what(); }
    return false;
  }

  /** Saves a network definition to file. */
  bool CSParserYaml::saveNetworkToFile(const std::string &arg_file,
      /** The network to be saved to a file */
      const sneuron::SNeuralNetwork& arg_network)
  {
    bool flag;
    try
    {
      /** Add code to save a network to a file here */
      return true;
    }
    catch(std::exception& e)
    { std::cerr<<"\nCSParserYaml::listNetworksInFile() Error : "<<e.what(); }
    return false;
  }

}
