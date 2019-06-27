#define CATCH_CONFIG_MAIN


#include "catch.hpp"
#include "euclidean.h"
#include <string>
#include <vector>


using std::string;
using std::vector;



TEST_CASE("Test EmbeddedVector construction","[embeddedvector]") {
  vector<string> vals = {"id1","0.32","7.1"};
  EmbeddedVector embedded{vals};
  REQUIRE("id1" == embedded.get_name() );
  vector<double> nums = embedded.get_values();
  REQUIRE(nums.at(0) == Approx(0.32));
  REQUIRE(nums.at(1) == Approx(7.1));



}
