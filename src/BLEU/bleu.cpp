#include <TextMetrics/BLEU/bleu.h>
#include <iostream>

namespace TextMetrics {

BLEU::BLEU(size_t _N) : N(_N) {}

double 
BLEU::operator()(std::string const& candidate, std::string const& reference) {
  std::vector<std::string> words_candidate;
  std::vector<std::string> words_reference;
  boost::split(words_candidate, candidate, boost::is_any_of(" \n"));
  boost::split(words_reference, reference, boost::is_any_of(" \n"));
  return (*this)(words_candidate, words_reference);
}

double
BLEU::operator()(std::vector<std::string> const& words_candidate, std::vector<std::string> const& words_reference) {
  double res = 0;
  NGramsSet ngrams_candidate; 
  NGramsSet ngrams_reference;

  double c = words_candidate.size();
  double r = words_reference.size();
  double precision = 0;

  for (size_t i = 1; i < N; ++i) {
    precision = 0;
    ngrams_candidate.clear();
    ngrams_reference.clear();

    make_ngrams(words_candidate, ngrams_candidate, i);
    make_ngrams(words_reference, ngrams_reference, i);

    for (auto& el : ngrams_candidate) {
      precision += std::min(el.second, ngrams_reference[el.first]);
    }
    precision /= (c - i + 1);
    res += std::log(precision) / N;
  }
  res += std::max(.0, 1 - r / c);
  return std::exp(res);
}

} // TextMetrics
