#include <chrono>
#include <iostream>
#include <string>

#include "common.hpp"
#ifdef WITH_STRUCTURES
#include "structures/array_set.hpp"
#include "structures/bit_array_set.hpp"
#include "structures/list_set.hpp"
#include "structures/machine_word_set.hpp"
#else
#include "classes/array_set.hpp"
#include "classes/bit_array_set.hpp"
#include "classes/list_set.hpp"
#include "classes/machine_word_set.hpp"
#endif
#include "generator.hpp"

inline constinit const unsigned long long BENCHMARK_REPEAT_COUNT = 100000000;
inline constinit const int BENCHMARK_TEST_COUNT = 1;
inline constinit const int TEST_COUNT = 1000;

namespace {
template <typename Set> auto solveFormula(const TestCase &test) {
    Set a = fromString<Set>(test.a);
    Set b = fromString<Set>(test.b);
    Set c = fromString<Set>(test.c);
    Set d = fromString<Set>(test.d);

    Set result = solve(a, b, c, d);
    std::string resultStr = toString(result);

    return resultStr;
}

template <typename Set> auto benchmarkFormula(const TestCase &test) {
    std::chrono::nanoseconds total = {};

    Set a = fromString<Set>(test.a);
    Set b = fromString<Set>(test.b);
    Set c = fromString<Set>(test.c);
    Set d = fromString<Set>(test.d);

    for (uint i = 0; i < BENCHMARK_REPEAT_COUNT; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        [[maybe_unused]] Set result = solve(a, b, c, d);
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }

    return total;
}

void printHelp() {
    std::cout << "Использование:\n"
              << "  ./sets -m, --manual       ручной ввод 4 множеств\n"
              << "  ./sets -t, --test         запуск автоматических тестов\n"
              << "  ./sets -b, --benchmark    запуск бенчмарка\n"
              << "  ./sets -v, --verbose      подробный вывод для тестов\n"
              << "  ./sets -h, --help         справка\n";
}

std::string formatSet(const std::string &s) {
    if (s.empty()) {
        return "{}";
    }

    std::string result = "{";
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (i != 0) {
            result += ", ";
        }
        result += s[i];
    }
    result += "}";
    return result;
}

bool isValidSubsetInput(const std::string &line) {
    for (char c : line) {
        if (!isValidChar(c)) {
            std::cout << "Ошибка: множество должно содержать только символы из U = {"
                      << UNIVERSE_STR << "}.\n";
            return false;
        }
    }
    return true;
}

std::string inputSet(const char *prompt) {
    std::string line;
    do {
        std::cout << prompt;
        std::getline(std::cin, line);
    } while (!isValidSubsetInput(line));

    std::string result;
    for (char c : line) {
        if (!result.contains(c)) {
            result += c;
        }
    }

    return result;
}

TestCase inputManual() {
    const std::string A = inputSet("A = ");
    const std::string B = inputSet("B = ");
    const std::string C = inputSet("C = ");
    const std::string D = inputSet("D = ");
    return TestCase(A, B, C, D, std::nullopt);
}

void print(const TestCase &test, const std::string &arrayResult, const std::string &listResult,
           const std::string &bitArrayResult, const std::string &machineWordResult, bool passed) {
    std::cout << "====================================================\n"
              << "Входные данные:\n"
              << "  A = " << formatSet(test.a) << '\n'
              << "  B = " << formatSet(test.b) << '\n'
              << "  C = " << formatSet(test.c) << '\n'
              << "  D = " << formatSet(test.d) << '\n'
              << "\nРезультаты:\n"
              << "  [Массив]         E = " << formatSet(arrayResult) << '\n'
              << "  [Список]         E = " << formatSet(listResult) << '\n'
              << "  [Массив битов]   E = " << formatSet(bitArrayResult) << '\n'
              << "  [Машинное слово] E = " << formatSet(machineWordResult) << '\n'
              << "====================================================\n";

    if (test.expected.has_value()) {
        std::cout << "Ожидалось:\n";
        std::cout << "  E = " << formatSet(test.expected.value()) << '\n';
        std::cout << "Статус: " << (passed ? "пройден" : "ошибка") << '\n';
    }
    std::cout << '\n';
}

bool run(const TestCase &test, bool verbose = false) {
    const std::string arrayResult = solveFormula<ArraySet>(test);
    const std::string listResult = solveFormula<ListSet>(test);
    const std::string bitArrayResult = solveFormula<BitArraySet>(test);
    const std::string machineWordResult = solveFormula<MachineWordSet>(test);

    const bool passed =
        !test.expected.has_value() ||
        (arrayResult == test.expected.value() && listResult == test.expected.value() &&
         bitArrayResult == test.expected.value() && machineWordResult == test.expected.value());

    if (verbose || !passed) {
        print(test, arrayResult, listResult, bitArrayResult, machineWordResult, passed);
    }

    return passed;
}

void run(const std::vector<TestCase> &tests, bool verbose = true) {
    int passed = 0;
    int failed = 0;

    for (const TestCase &test : tests) {
        const bool passedCurrent = run(test, verbose);
        if (passedCurrent) {
            ++passed;
        } else {
            ++failed;
        }
    }

    std::cout << "Итог:\n"
              << "  проверено: " << tests.size() << '\n'
              << "  пройдено:  " << passed << '\n'
              << "  ошибок:    " << failed << '\n';
}

void printBenchmarkResult(const char *name, std::chrono::nanoseconds time) {
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
    std::cout << "  " << name << ": " << milliseconds << "  мс\n";
}

void runBenchmarks() {
    const std::vector<TestCase> tests = generateTests(BENCHMARK_TEST_COUNT);

    const std::chrono::nanoseconds arrayTime = benchmarkFormula<ArraySet>(tests[0]);
    const std::chrono::nanoseconds listTime = benchmarkFormula<ListSet>(tests[0]);
    const std::chrono::nanoseconds bitArrayTime = benchmarkFormula<BitArraySet>(tests[0]);
    const std::chrono::nanoseconds machineWordTime = benchmarkFormula<MachineWordSet>(tests[0]);

    std::cout << "Бенчмарк:\n"
              << "  тестов:   " << BENCHMARK_TEST_COUNT << '\n'
              << "  повторов: " << BENCHMARK_REPEAT_COUNT << '\n'
              << "Время:\n";
    printBenchmarkResult("Массив", arrayTime);
    printBenchmarkResult("Список", listTime);
    printBenchmarkResult("Массив битов", bitArrayTime);
    printBenchmarkResult("Машинное слово", machineWordTime);
}
} // namespace

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printHelp();
        return -1;
    }

    bool manual = false;
    bool testing = false;
    bool benchmarking = false;
    bool verbose = false;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            printHelp();
            return 1;
        } else if (arg == "-t" || arg == "--test") {
            testing = true;
        } else if (arg == "-b" || arg == "--benchmark") {
            benchmarking = true;
        } else if (arg == "-v" || arg == "--verbose") {
            verbose = true;
        } else if (arg == "-m" || arg == "--manual") {
            manual = true;
        } else {
            printHelp();
            return 1;
        }
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (testing) {
        run(generateTests(TEST_COUNT), verbose);
    }
    if (benchmarking) {
        runBenchmarks();
    }
    if (manual) {
        const TestCase test = inputManual();
        run(test, true);
    }
    return 0;
}
