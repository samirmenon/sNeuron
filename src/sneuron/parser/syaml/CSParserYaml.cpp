/*
 * CSParserYaml.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: samir
 */

#include "CSParserYaml.hpp"

#include <yaml-cpp/yaml.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
static unsigned int uid=0;

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
  bool CSParserYaml::listNetworksInFile(const std::string& arg_file,
      std::vector<sneuron::string2>& arg_network_name_type)
  {
    bool flag;
    try
    {
      std::ifstream fin(arg_file.c_str());
      YAML::Parser parser(fin);
      YAML::Node doc;
      flag = parser.GetNextDocument(doc);
      if(false == flag)
      { throw(std::runtime_error("Could not read any document in the yaml test file"));  }

      /**code to read network names from a file here */
      for( unsigned int i=0; i<doc.size(); i++)
      {
        //Extract names
        sneuron::string2 ss;
        doc[i]["name"] >> ss.str1;
        doc[i]["type"] >> ss.str2;

        //Push into the list of networks
        arg_network_name_type.push_back(ss);
      }
      return true;
    }
    catch(std::exception& e)
    { std::cerr<<"\nCSParserYaml::listNetworksInFile() Error : "<<e.what(); }
    return false;
  }
  /**
   * overloading operator ">>" to read encoders into vector
   */
  void operator >> (const YAML::Node& node, Eigen::VectorXd& v)
  {
    //Resize the vector to the length of node.
    v.resize(node.size());
    for(unsigned int i=0; i<node.size(); i++)
    {
      node[i] >> v(i);
    }

  }
  /**
   * overloading operator ">>" to read a linear neuron's parameters to data structure SNeuronLinear
   */
  void operator >> (const YAML::Node& node, SNeuronLinear& n)
  {
    node["name"] >> n.name_;
    node["type"] >> n.type_;
    node["id"] >> n.id_;
    node["a"] >> n.a_;
    node["b"] >> n.b_;
    node["tref"] >> n.t_ref_;
    node["encoders"] >> n.encoder_;
    n.uid_ = uid++;
  }

  /**
   * overloading operator ">>" to read neuron sets to data structure SNeuralSet
   */
  void operator >> (const YAML::Node& node, SNeuronSet& set)
  {
    try
    {
      node["name"] >> set.name_;
      node["n-neurons"] >> set.n_neurons_;
      node["input-dimension"] >> set.input_dim_;
      const YAML::Node& neurons = node["neurons"];
      const YAML::Node& linear_neurons = neurons["lif"];
      for(unsigned i=0;i<linear_neurons.size();i++)
      {
        //First, read the name of this neuron so we can create a unique entry in
        //the pilemap
        std::string str;
        linear_neurons[i]["name"] >> str;

        //Now create an entry in the pilemap (NOTE the ** because SNeuron is a super-class).
        SNeuron** s = set.neurons_.create(str,NULL);
        if(NULL==s) { throw(std::runtime_error("Couldn't create an object on the PileMap")); }

        //Now create a linear neuron into which the yaml parser will read the data
        *s = new SNeuronLinear();
        if(NULL==*s) { throw(std::runtime_error("Couldn't create an object of subclass")); }

        //Dynamic cast the new pointer to a type that the yaml parser can process
        SNeuronLinear *tmp;
        tmp = dynamic_cast<SNeuronLinear*>(*s);
        if(NULL == tmp){throw(std::runtime_error("Pointer of SNeuronLinear not created"));}

        //Now read in the data from the yaml parser
        linear_neurons[i] >> *tmp;
      }
    }
    catch(std::exception& e)
    { std::cerr<<"\nCSParserYaml::operator >> (YAML node,SNeuronSet) Error : "<<e.what(); }
  }

  /**
   * overloading operator ">>" to read network to data structure SNeuralNetwork
   */
  void operator >> (const YAML::Node& node, SNeuralNetwork& network)
  {
    try
    {
      node["name"] >> network.name_;
      node["type"] >> network.type_;
      const YAML::Node& pools = node["set"];

      //Loop over all the sets in the network and extract their data
      for(unsigned i=0;i<pools.size();i++)
      {
        //This variable will store the name of the set being explored
        std::string str;
        pools[i]["name"] >> str;

        //Create a pilemap entry
        SNeuronSet* s = network.sets_.create(str);
        if(NULL==s) { throw(std::runtime_error("Couldn't create an object on the PileMap"));}

        //Read data into this newly created object
        pools[i] >> *s;
      }
    }
    catch(std::exception& e)
    { std::cerr<<"\noperator >> (YAML node,SNeuralNetwork) Error : "<<e.what(); }
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
      std::ifstream fin(arg_file.c_str());
      YAML::Parser parser(fin);
      YAML::Node doc;
      flag = parser.GetNextDocument(doc);
      //Check for yaml function
      if(false == flag)
      { throw(std::runtime_error("Could not read any document in the yaml test file"));  }

      //found variable is set to true when we find the network with the given name
      bool found=false;
      for(unsigned int i=0; i<doc.size(); i++){
        std::string str;
        doc[i]["name"] >> str;
        if(str==arg_network_name)
        {
          found=true;

          //If found read that network into the passed argument
          doc[i] >> arg_network;
        }
      }
      if(false==found)
      { throw(std::runtime_error("Network not found")); }

      return true;
    }
    catch(std::exception& e)
    { std::cerr<<"\nCSParserYaml::readNetworksInFile() Error : "<<e.what(); }
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
