#pragma once

#include <optional>
#include <string>
#include <vector>

struct TestCase {
  std::string a;
  std::string b;
  std::string c;
  std::string d;
  std::optional<std::string> expected;
};

int randomNumber(int min, int max);
std::string randomSubset(unsigned int power);
TestCase randomTest();
std::vector<TestCase> generateTests(int count);
