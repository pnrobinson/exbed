#include "phenoseries.h"



vector<int>
Phenoseries::leaving_out_element_n(unsigned n) const {
  vector<int> ret;
  for (auto i=0u;i<genes_.size();i++) {
    if (i==n) continue;
    ret.push_back(genes_.at(i));
  }
  return ret;
}
