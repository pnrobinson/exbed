#ifndef PHENOSERIES_H
#define PHENOSERIES_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class Phenoseries {
private:
  string name_;
  vector<int> genes_;


public:
  Phenoseries(const string &name,const vector<int> genelist):
    name_(name), genes_(genelist){}
  int gene_count() const { return genes_.size(); }
  vector<int> leaving_out_element_n(unsigned n) const;
  int element_n(int n) const
  { return genes_.at(n); }
  string get_name() const { return name_ ;}







};









#endif
