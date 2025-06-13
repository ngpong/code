#include "common.hpp"

// 双向快速排序
void solution_1(Array &arr, int32_t size) {
  make_y_combinator([&](auto qsort, int32_t low, int32_t high) -> void {
    if (low >= high) {
      return;
    }

    int32_t pivot = arr[low];

    int32_t lt = low, gt = high;
    while (lt < gt) {
      while (lt < gt && arr[gt] >= pivot) {
        gt--;
      }
      while (lt < gt && arr[lt] <= pivot) {
        lt++;
      }
      if (lt < gt) {
        std::swap(arr[lt], arr[gt]);
      }
    }
    std::swap(arr[low], arr[lt]);

    qsort(low, lt - 1);
    qsort(lt + 1, high);
  })(0, size - 1);
}

// 无递归快速排序
void solution_2(Array &arr, int32_t size) {
  auto partition = [&](int32_t low, int32_t high) -> int32_t {
    int32_t pivot = arr[low];

    int32_t lt = low, gt = high;
    while (lt < gt) {
      while (lt < gt && arr[gt] >= pivot) {
        gt--;
      }
      while (lt < gt && arr[lt] <= pivot) {
        lt++;
      }
      if (lt < gt) {
        std::swap(arr[lt], arr[gt]);
      }
    }
    std::swap(arr[lt], arr[low]);

    return lt;
  };

  std::stack<int32_t> s;
  s.push(0);
  s.push(size - 1);

  while (!s.empty()) {
    int32_t high = s.top(); s.pop();
    int32_t low  = s.top(); s.pop();
    if (low >= high) {
      continue;
    }

    int32_t mid = partition(low, high);
    s.push(low); s.push(mid - 1);
    s.push(mid + 1); s.push(high);
  }
}

// 单向快速排序
void solution_3(Array &arr, int32_t size) {
  [&](this const auto &qsort, int32_t low, int32_t high) -> void {
    if (low >= high) {
      return;
    }

    int32_t pivot = arr[low];

    int32_t lt = low, i = low + 1;
    while (i <= high) {
      if (arr[i] <= pivot) {
        std::swap(arr[i], arr[++lt]);
      }
      ++i;
    }
    std::swap(arr[low], arr[lt]);

    qsort(low, lt - 1);
    qsort(lt + 1, high);
  }(0, size - 1);
}

// 三向快速排序
void solution_4(Array &arr, int32_t size) {
  auto quick_sort = make_y_combinator([&](auto quick_sort, int32_t low, int32_t high) -> void {
    if (low >= high) {
      return;
    }

    int32_t p = arr[low];

    int32_t lt = low, gt = high + 1, i = low + 1;
    while (i < gt) {
      if (arr[i] < p) {
        std::swap(arr[i++], arr[lt++]);
      } else if (arr[i] > p) {
        std::swap(arr[i], arr[--gt]);
      } else {
        i++;
      }
    }

    quick_sort(low, lt - 1);
    quick_sort(gt, high);
  });

  quick_sort(0, size - 1);
}

// 双向快速排序（优化pivot的选择）
void solution_5(Array &arr, int32_t size) {
  // 该函数将序列分布为：mid...high...low
  auto select_pivot = make_y_combinator([&](auto select_pivot, int32_t low, int32_t high) -> void {
    int32_t mid = (low + high) / 2;

    if (arr[mid] < arr[high]) {
      std::swap(arr[mid], arr[high]);
    }

    if (arr[low] < arr[high]) {
      std::swap(arr[low], arr[high]);
    }

    if (arr[mid] < arr[low]) {
      std::swap(arr[mid], arr[low]);
    }
  });

  auto quick_sort = make_y_combinator([&](auto quick_sort, int32_t low, int32_t high) -> void {
    if (low >= high) {
      return;
    }

    select_pivot(low, high);

    int32_t p = arr[low];

    int32_t lt = low, gt = high;
    while (lt < gt) {
      while (lt < gt && arr[gt] >= p) {
        --gt;
      }
      while (lt < gt && arr[lt] <= p) {
        ++lt;
      }
      if (lt < gt) {
        std::swap(arr[lt], arr[gt]);
      }
    }
    std::swap(arr[lt], arr[low]);

    quick_sort(low, lt - 1);
    quick_sort(lt + 1, high);
  });

  quick_sort(0, size - 1);
}
void solution_6(Array &arr, int32_t size) {
  auto select_pivot = make_y_combinator([&](auto select_pivot, int32_t low, int32_t high) -> void {
    int32_t mid = (low + high) / 2;

    if (arr[high] < arr[low]) {
      std::swap(arr[high], arr[low]);
    }

    if (arr[high] < arr[mid]) {
      std::swap(arr[high], arr[mid]);
    }

    if (arr[high] < arr[mid]) {
      std::swap(arr[mid], arr[high]);
    }
  });

  auto quick_sort = make_y_combinator([&](auto quick_sort, int32_t low, int32_t high) -> void {
    if (low >= high) {
      return;
    }

    select_pivot(low, high);

    int32_t p = arr[low];

    int32_t lt = low, gt = high;
    while (lt < gt) {
      while (lt < gt && arr[gt] >= p) {
        --gt;
      }
      while (lt < gt && arr[lt] <= p) {
        ++lt;
      }
      if (lt < gt) {
        std::swap(arr[lt], arr[gt]);
      }
    }
    std::swap(arr[lt], arr[low]);

    quick_sort(low, lt - 1);
    quick_sort(lt + 1, high);
  });

  quick_sort(0, size - 1);
}
void solution_7(Array &arr, int32_t size) {
  auto fix_pivot = make_y_combinator([&](auto fix_pivot, int32_t low, int32_t high) -> void {
    int32_t mid = (low + high) / 2;

    int32_t l = arr[low];
    int32_t m = arr[mid];
    int32_t r = arr[high];

    if ((l <= m && m <= r) || (r <= m && m <= l)) {
      std::swap(arr[low], arr[mid]);
    } else if ((l <= r && r <= m) || (m <= r && r <= l)) {
      std::swap(arr[low], arr[high]);
    }
  });

  auto quick_sort = make_y_combinator([&](auto quick_sort, int32_t low, int32_t high) -> void {
    if (low >= high) {
      return;
    }

    fix_pivot(low, high);

    int32_t pivot = arr[low];

    int32_t lt = low, gt = high;
    while (lt < gt) {
      while (lt < gt && arr[gt] >= pivot) {
        --gt;
      }
      while (lt < gt && arr[lt] <= pivot) {
        ++lt;
      }
      if (lt < gt) {
        std::swap(arr[lt], arr[gt]);
      }
    }
    std::swap(arr[low], arr[lt]);

    quick_sort(low, lt - 1);
    quick_sort(lt + 1, high);
  });

  quick_sort(0, size - 1);
}

int32_t main(int32_t argc, char *argv[]) {
  std::srand(std::time(NULL));

  solution_test({
    { solution_1, "双向分区快速排序" },
    { solution_2, "递推快速排序" },
    { solution_3, "单向分区快速排序" },
    // { solution_4, "solution_4" },
    // { solution_5, "solution_5" },
    // { solution_6, "solution_6" },
    // { solution_7, "solution_7" },
  });

  solution_benchmark({
    { solution_1, "双向分区快速排序" },
    { solution_2, "递推快速排序" },
    { solution_3, "单向分区快速排序" },
    // { solution_4, "solution_4" },
    // { solution_5, "solution_5" },
    // { solution_6, "solution_6" },
    // { solution_7, "solution_7" },
  });

  return 0;
}
