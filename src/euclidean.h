#ifndef EUCLIDEAN_H
#define EUCLIDEAN_H

#include <vector>
#include <map>
#include <string>


using std::string;
using std::map;
using std::vector;



class EmbeddedVector {
 private:
  string name_;
  vector<double> values_;

 public:
  EmbeddedVector(vector<string> vals);

  string get_name() const { return name_; }
  vector<double> get_values() const { return values_; }


  

};






/**
 * A cluster of numerical vectors 
 */
class Cluster {
 private:
  map<string,vector<double>> vectors_;
  string name_;

 public:
  void add_vector(const vector<string> &invec);



};





class Parser {
 private:
  map<char,Cluster> clustermap_;


 public:
  Parser(const string & path);




};









#endif
