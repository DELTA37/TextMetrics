#include <TextMetrics/BLEU/bleu.h>
#include <iostream>
#include <string>

int main(void) {
  std::string s1;
  std::string s2;
  std::getline(std::cin, s1);
  std::getline(std::cin, s2);
  TextMetrics::BLEU metric(4);
  std::cout << "BLEU metric between \"" << s1 << "\" and \"" << s2 << "\" is " << metric(s1, s2) << std::endl;
}
