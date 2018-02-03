#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <algorithm>
#include <boost/functional/hash.hpp>

namespace TextMetrics {

struct BLEU {
  // bilingual evaluation understudy
  size_t N;

  explicit BLEU(size_t N);
  double operator()(
    std::string const& candidate, 
    std::string const& reference
  );
  double operator()(
    std::vector<std::string> const& words_candidate, 
    std::vector<std::string> const& words_reference
  );
private:  
  struct HashForVector {
    size_t operator()(std::vector<std::string> const& v) const noexcept {
      return boost::hash_value(v);
    }
  };

  typedef std::unordered_map<std::vector<std::string>, unsigned int, BLEU::HashForVector> NGramsSet;

  void make_ngrams(std::vector<std::string> const& v, NGramsSet& out, size_t ngram) {
    std::unordered_map<std::vector<std::string>, unsigned int, BLEU::HashForVector> a;
    size_t length = v.size();
    assert(length >= ngram);

    for (size_t i = 0; i < length - ngram + 1; ++i) {
      ++out[std::vector<std::string>(v.begin() + i, v.begin() + i + ngram)];
    }
  }

};

} // TextMetrics
