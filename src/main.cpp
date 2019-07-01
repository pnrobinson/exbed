

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "euclidean.h"
#include "phenoseries.h"


using std::string;
using std::vector;


vector<Phenoseries> parse_phenoseries(string path);
void evaluate_phenoseries(const Phenoseries & ps, const Cluster &cluster);

int main(int argc,char ** argv) {
  if (argc != 3) {
    std::cerr << "usage exbed ..hn2v-output-file  phenoseries-file\n";
    exit(EXIT_FAILURE);
  }
  Parser parser{argv[1]};
  parser.status();
  Cluster cluster = parser.get_cluster('d');


  vector<Phenoseries> phenoseries = parse_phenoseries(argv[2]);
  for (Phenoseries ps : phenoseries) {
    evaluate_phenoseries(ps,cluster);
  }



}


void evaluate_phenoseries(const Phenoseries & ps, const Cluster & cluster) {
  unsigned N = ps.gene_count();
  if (N<2) {
    std::cerr <<"[WARNING] phenoseries " << ps.get_name() << " had only one member\n";
    return;
  }
  int total = cluster.vector_count();
  for (unsigned i=0u; i<N; i++) {
    int gene_id = ps.element_n(i);
    vector<int> othergenes = ps.leaving_out_element_n(i);
    if (cluster.contains_gene(gene_id)) {
        int rank = cluster.rank(gene_id,othergenes);
        std::cout << "rank of " << gene_id << " was " << rank << "/" << total << "\n";
    }
  }



}


// split a string on tabs
vector<string> split_on_tab(const string& s)
{
   vector<string> tokens;
   string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, '\t')){
      tokens.push_back(token);
   }
   return tokens;
}


vector<Phenoseries> parse_phenoseries(string path) {
  vector<Phenoseries> srs;
  std::cout << "[INFO] Parsing " << path << "\n";
  std::ifstream infile(path);
    if (! infile.good()) {
      std::cerr <<"[ERROR] Could not open input file at "
        << path << "\n";
      std::exit(1);
    }
    std::string line;
    std::getline(infile,line); // discard first line
    while (std::getline(infile,line)) {
      vector<string> fields = split_on_tab(line);
      if (fields.empty()) {
        std::cerr << "[WARNING] skipping emtyp line\n";
        continue;
      }
      if (fields.size()==1) {
        std::cerr << "[WARNING] line had only one field: " << fields.at(0) << "\n";
        continue;
      }
      string name = fields.at(0);
      vector<int> genelist;
      for (auto i=1u;i<fields.size();i++) {
        int gene_id = stoi(fields.at(i));
        genelist.push_back(gene_id);
      }
      Phenoseries ps{name,genelist};
      srs.push_back(ps);
    }

    std::cout << "We parsed " << srs.size() << " phenoseries\n";
    return srs;
}
