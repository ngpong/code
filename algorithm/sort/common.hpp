#include <algorithm>
#include <array>
#include <chrono>
#include <thread>
#include <future>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <stack>
#include <list>
#include <fstream>
#include <benchmark/benchmark.h>

#define MAX_TEST_CASE 1000

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

using Array      = std::vector<int32_t>;
using Solution_F = std::function<void(Array &, int32_t)>;

template <class F>
struct y_combinator {
  F f; // the lambda will be stored here

  // a forwarding operator():
  template <class... Args>
  decltype(auto) operator()(Args &&...args) const {
    // we pass ourselves to f, then the arguments.
    return f(*this, std::forward<Args>(args)...);
  }
};

// helper function that deduces the type of the lambda:
template <class F>
y_combinator<std::decay_t<F>> make_y_combinator(F &&f) {
  return { std::forward<F>(f) };
}

std::ostream &operator<<(std::ostream &os, const std::vector<int32_t> &datas) {
  for (const auto &data : datas) {
    std::cout << data << " ";
  }

  return os;
}

using __MapValueType = std::tuple<Array, Array, std::string>;

// 部分有序数组
std::tuple<Array, Array, std::string> get_partially(int32_t size) {
  static std::map<int32_t, std::tuple<Array, Array, std::string>> mm;

  if (!mm.count(size)) {
    auto &tp = mm.emplace(size, std::make_tuple<Array, Array, std::string>(std::vector<int32_t>(size, 0x0), {}, __FUNCTION__)).first->second;

    std::mt19937 rng(std::random_device{}());

    // 前70%部分有序
    int orderedPartSize = size * 0.7;
    for (int i = 0; i < orderedPartSize; ++i) {
      std::get<0>(tp)[i] = i;
    }

    // 剩余30%部分随机
    std::uniform_int_distribution<int> dist(0, size * 2);
    for (int i = orderedPartSize; i < size; ++i) {
      std::get<0>(tp)[i] = dist(rng);
    }

    // 在有序部分中随机交换少量元素（10%）
    int swapCount = orderedPartSize * 0.1;
    for (int i = 0; i < swapCount; ++i) {
      int idx1 = rng() % orderedPartSize;
      int idx2 = rng() % orderedPartSize;
      std::swap(std::get<0>(tp)[idx1], std::get<0>(tp)[idx2]);
    }

    std::get<1>(tp) = std::get<0>(tp);
    std::sort(std::get<1>(tp).begin(), std::get<1>(tp).end());
  }

  return mm[size];
}

// 波浪形数组：交替递增和递减的数组
std::tuple<Array, Array, std::string> get_wave(int size) {
  static std::map<int32_t, std::tuple<Array, Array, std::string>> mm;

  if (!mm.count(size)) {
    auto &tp = mm.emplace(size, std::make_tuple<Array, Array, std::string>(std::vector<int32_t>(size, 0x0), {}, __FUNCTION__)).first->second;

    for (int i = 0; i < size; ++i) {
      std::get<0>(tp)[i] = (i % 2 == 0) ? i : size - i;
    }

    std::get<1>(tp) = std::get<0>(tp);
    std::sort(std::get<1>(tp).begin(), std::get<1>(tp).end());
  }

  return mm[size];
}

std::tuple<Array, Array, std::string> get_duplicates2() {
  static std::map<int32_t, std::tuple<Array, Array, std::string>> mm;

  if (!mm.count(1)) {
    std::vector<int32_t> nums = {};
    std::ifstream f("nums");
    int32_t num;
    while (f >> num) {
      nums.push_back(num);
    }
    f.close();

    std::vector<int32_t> sortnums = nums;
    std::sort(sortnums.begin(), sortnums.end());

    mm.emplace(1, std::make_tuple<Array, Array, std::string>(std::move(nums), std::move(sortnums), __FUNCTION__));
  }

  return mm[1];
}

// 大量重复元素的数组
std::tuple<Array, Array, std::string> get_duplicates(int size) {
  static std::map<int32_t, std::tuple<Array, Array, std::string>> mm;

  if (!mm.count(size)) {
    auto &tp = mm.emplace(size, std::make_tuple<Array, Array, std::string>(std::vector<int32_t>(size, 0x0), {}, __FUNCTION__)).first->second;

    // 设定随机数种子
    std::srand(static_cast<unsigned>(std::time(0)));

    // 填充数组
    for (int i = 0; i < size; ++i) {
      std::get<0>(tp)[i] = std::rand() % size;
    }

    // 增加重复元素的概率
    for (int i = 0; i < size; ++i) {
      int index          = std::rand() % size;
      std::get<0>(tp)[i] = std::get<0>(tp)[index];
    }

    std::get<1>(tp) = std::get<0>(tp);
    std::sort(std::get<1>(tp).begin(), std::get<1>(tp).end());
  }

  return mm[size];
}

// 完全无序的数组（不包含重复元素）
std::tuple<Array, Array, std::string> get_random(int size) {
  static std::map<int32_t, std::tuple<Array, Array, std::string>> mm;

  if (!mm.count(size)) {
    auto &tp = mm.emplace(size, std::make_tuple<Array, Array, std::string>(std::vector<int32_t>(size, 0x0), {}, __FUNCTION__)).first->second;

    for (int i = 0; i < size; ++i) {
      std::get<0>(tp)[i] = i;
    }

    std::mt19937 rng(std::random_device{}());
    std::shuffle(std::get<0>(tp).begin(), std::get<0>(tp).end(), rng);

    std::get<1>(tp) = std::get<0>(tp);
    std::sort(std::get<1>(tp).begin(), std::get<1>(tp).end());
  }

  return mm[size];
}

// 升序排序的数组
std::tuple<Array, Array, std::string> get_sorted_asc(int size) {
  static std::map<int32_t, std::tuple<Array, Array, std::string>> mm;

  if (!mm.count(size)) {
    auto &tp = mm.emplace(size, std::make_tuple<Array, Array, std::string>(std::vector<int32_t>(size, 0x0), {}, __FUNCTION__)).first->second;

    for (int i = 0; i < size; ++i) {
      std::get<0>(tp)[i] = i;
    }

    std::get<1>(tp) = std::get<0>(tp);
    std::sort(std::get<1>(tp).begin(), std::get<1>(tp).end());
  }

  return mm[size];
}

// 降序排序的数组
std::tuple<Array, Array, std::string> get_sorted_desc(int size) {
  static std::map<int32_t, std::tuple<Array, Array, std::string>> mm;

  if (!mm.count(size)) {
    auto &tp = mm.emplace(size, std::make_tuple<Array, Array, std::string>(std::vector<int32_t>(size, 0x0), {}, __FUNCTION__)).first->second;

    for (int i = 0; i < size; ++i) {
      std::get<0>(tp)[i] = size - i;
    }

    std::get<1>(tp) = std::get<0>(tp);
    std::sort(std::get<1>(tp).begin(), std::get<1>(tp).end());
  }

  return mm[size];
}

void solution_test(std::vector<std::pair<Solution_F, std::string>> regs) {
  std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

  for (auto &pair : regs) {
    auto &func = pair.first;
    auto &name = pair.second;

    auto __solution_test = [&](std::tuple<Array, Array, std::string> tp) {
      auto &source_datas = std::get<0>(tp);
      auto &sorted_datas = std::get<1>(tp);
      auto &datas_name   = std::get<2>(tp);

      std::string outpur_msg = name + "/" + datas_name + ":";

      func(source_datas, source_datas.size());

      if (std::equal(source_datas.begin(), source_datas.end(), sorted_datas.begin())) {
        int32_t space_length = 84 - (outpur_msg.size() + 3);
        for (int32_t i = 0; i < space_length; ++i) {
          outpur_msg += " ";
        }
        outpur_msg = outpur_msg + GREEN + "OK!" + RESET;
      } else {
        int32_t space_length = 84 - (outpur_msg.size() + 4);
        for (int32_t i = 0; i < space_length; ++i) {
          outpur_msg += " ";
        }
        outpur_msg = outpur_msg + RED + "OPS!" + RESET;
      }

      std::cout << outpur_msg << std::endl;
    };

    auto t1 = get_random(MAX_TEST_CASE);
    auto t2 = get_sorted_asc(MAX_TEST_CASE);
    auto t3 = get_sorted_desc(MAX_TEST_CASE);
    auto t4 = get_duplicates(MAX_TEST_CASE);
    auto t5 = get_duplicates2();
    auto t6 = get_wave(MAX_TEST_CASE);
    auto t7 = get_partially(MAX_TEST_CASE);

    __solution_test(t1);
    __solution_test(t2);
    __solution_test(t3);
    __solution_test(t4);
    __solution_test(t5);
    __solution_test(t6);
    __solution_test(t7);
  }

  std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
}

void solution_benchmark(std::vector<std::pair<Solution_F, std::string>> regs) {
  std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

  benchmark::Initialize(nullptr, nullptr);

  for(auto& t : {
    get_random(MAX_TEST_CASE),
    get_sorted_asc(MAX_TEST_CASE),
    get_sorted_desc(MAX_TEST_CASE),
    get_duplicates(MAX_TEST_CASE),
    get_duplicates2(),
    get_wave(MAX_TEST_CASE),
    get_partially(MAX_TEST_CASE)
  }) {
    for (auto &pair : regs) {
      auto &func = pair.first;
      auto &name = pair.second;

      benchmark::RegisterBenchmark(std::get<2>(t) + "/" + name, [=](benchmark::State &state) {
        for (auto _ : state) {
          Array datas = std::get<0>(t);
          func(datas, datas.size());
        }
      });
    }
  }

  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();

  std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
}
