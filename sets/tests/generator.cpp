#include "generator.hpp"

#include <algorithm>
#include <cstdlib>

#include "common.hpp"

namespace {
std::string expectedResult(const std::string &a, const std::string &b,
                           const std::string &c, const std::string &d) {
  std::string result;
  for (char sym : UNIVERSE) {
    if (d.contains(sym) ||
        (a.contains(sym) && b.contains(sym) && c.contains(sym))) {
      result += sym;
    }
  }
  return result;
}
} // namespace

int randomNumber(int min, int max) {
  if (min > max) {
    std::swap(min, max);
  }
  return min + std::rand() % (max - min + 1);
}

std::string randomSubset(unsigned int power) {
  power = std::min(power, static_cast<unsigned int>(UNIVERSE_SIZE));
  std::array<char, UNIVERSE_SIZE> shuffled = UNIVERSE;

  for (int i = UNIVERSE_SIZE - 1; i > 0; --i) {
    const int j = std::rand() % (i + 1);
    std::swap(shuffled[i], shuffled[j]);
  }

  return std::string(shuffled.begin(), shuffled.begin() + power);
}

TestCase randomTest() {
  const std::string a =
      randomSubset(static_cast<unsigned int>(randomNumber(0, UNIVERSE_SIZE)));
  const std::string b =
      randomSubset(static_cast<unsigned int>(randomNumber(0, UNIVERSE_SIZE)));
  const std::string c =
      randomSubset(static_cast<unsigned int>(randomNumber(0, UNIVERSE_SIZE)));
  const std::string d =
      randomSubset(static_cast<unsigned int>(randomNumber(0, UNIVERSE_SIZE)));

  return TestCase(a, b, c, d, expectedResult(a, b, c, d));
}

std::vector<TestCase> generateTests(int count) {
  std::vector<TestCase> tests;
  if (count <= 0) {
    return tests;
  }

  tests.reserve(static_cast<std::size_t>(count));
  for (int i = 0; i < count; ++i) {
    tests.push_back(randomTest());
  }
  return tests;
}
