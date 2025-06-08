#include "common.hpp"

void solution_bubble_sort(Array &arr, int32_t size) {
  for (int32_t i = 0; i < size; i++) {
    for (int32_t j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void solution_selection_sort(Array &arr, int32_t size) {
  for (int32_t i = 0; i < size; i++) {
    int32_t min = i;
    for (int32_t j = i + 1; j < size; j++) {
      if (arr[j] < arr[min]) {
        min = j;
      }
    }
    std::swap(arr[i], arr[min]);
  }
}

void solution_insert_sort(Array &arr, int32_t size) {
  for (int32_t i = 1; i < size; i++) {
    int32_t k = arr[i];

    int32_t j = i - 1;
    for (; j >= 0 && k < arr[j]; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = k;
  }
}

void solution_shell_sort(Array &arr, int32_t size) {
  for (int32_t gs = size / 2; gs > 0; gs /= 2) {
    for (int32_t i = gs; i < size; i++) {
      int32_t k = arr[i];

      int32_t j = i;
      for (; j >= gs && k < arr[j - gs]; j -= gs) {
        arr[j] = arr[j - gs];
      }
      arr[j] = k;
    }
  }
}

void solution_bucket_sort(Array &arr, int32_t size) {
  int32_t max = arr[0];
  for (int32_t i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  max++;

  Array bucket(max, 0x0);
  for (int32_t i = 0; i < size; i++) {
    bucket[arr[i]]++;
  }

  int32_t k = 0;
  for (int32_t i = 0; i < max; i++) {
    for (int32_t j = 0; j < bucket[i]; j++) {
      arr[k++] = i;
    }
  }
}

void solution_counting_sort(Array &arr, int32_t size) {
  int32_t max = arr[0];
  for (int32_t i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  max++;

  Array bucket(max, 0x0);
  Array sorter(size, 0x0);

  for (int32_t i = 0; i < size; i++) {
    bucket[arr[i]]++;
  }

  for (int32_t i = 1; i < max; i++) {
    bucket[i] += bucket[i - 1];
  }

  for (int32_t i = 0; i < size; i++) {
    sorter[--bucket[arr[i]]] = arr[i];
  }

  for (int32_t i = 0; i < size; i++) {
    arr[i] = sorter[i];
  }
}

void solution_heap_sort(Array &arr, int32_t size) {
  auto heapify = [&](int32_t n, int32_t i) -> void {
    while (true) {
      int32_t l = i * 2 + 1;
      int32_t r = i * 2 + 2;

      int32_t m = i;
      if (l <= n && arr[l] > arr[m]) {
        m = l;
      }
      if (r <= n && arr[r] > arr[m]) {
        m = r;
      }

      if (m == i) {
        break;
      }

      std::swap(arr[m], arr[i]);
      i = m;
    }
  };

  int32_t n = size - 1;
  for (int32_t i = (n - 1) / 2; i >= 0; i--) {
    heapify(n, i);
  }
  for (int32_t i = n; i > 0; i--) {
    std::swap(arr[0], arr[i]);
    heapify(i - 1, 0);
  }
}

void solution_quicksort_normal(Array &arr, int32_t size) {
  auto quick_sort = make_y_combinator([&](auto quick_sort, int32_t low, int32_t high) -> void {
    if (low >= high) {
      return;
    }

    int32_t p = arr[low];

    int32_t lt = low, i = low + 1;
    while (i <= high) {
      if (arr[i] <= p) {
        std::swap(arr[i], arr[++lt]);
      }
      ++i;
    }
    std::swap(arr[low], arr[lt]);

    quick_sort(low, lt - 1);
    quick_sort(lt + 1, high);
  });

  quick_sort(0, size - 1);
}

void solution_quicksort_nonrecursive(Array &arr, int32_t size) {
  auto partition = make_y_combinator([&](auto partition, int32_t low, int32_t high) -> int32_t {
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

    return lt;
  });

  std::stack<int32_t> s;

  if (size > 1) {
    s.push(0);
    s.push(size - 1);
  }

  while (!s.empty()) {
    int32_t high = s.top();
    s.pop();
    int32_t low = s.top();
    s.pop();

    int32_t mid = partition(low, high);

    if (low < mid - 1) {
      s.push(low);
      s.push(mid - 1);
    }

    if (high > mid + 1) {
      s.push(mid + 1);
      s.push(high);
    }
  }
}

void solution_quicksort_2way(Array &arr, int32_t size) {
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
    std::swap(arr[lt], arr[low]);

    qsort(low, lt - 1);
    qsort(lt + 1, high);
  })(0, size - 1);
}

void solution_quicksort_3way(Array &arr, int32_t size) {
  auto quick_sort = make_y_combinator([&](auto quick_sort, int32_t low, int32_t high) {
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

void solution_merge_sort(Array &arr, int32_t size) {
  auto merge = [&](int32_t l, int32_t m, int32_t r) -> void {
    int32_t lsize = m - l;
    Array larr(lsize);
    for (int32_t i = l; i < m; i++) {
      larr[i - l] = arr[i];
    }

    int32_t rsize = r - m + 1;
    Array rarr(rsize);
    for (int32_t i = m; i <= r; i++) {
      rarr[i - m] = arr[i];
    }

    int32_t i = 0, j = 0;
    int32_t k = l;
    while (i < lsize && j < rsize) {
      if (larr[i] < rarr[j]) {
        arr[k++] = larr[i++];
      } else {
        arr[k++] = rarr[j++];
      }
    }

    while (i < lsize) {
      arr[k++] = larr[i++];
    }

    while (j < rsize) {
      arr[k++] = rarr[j++];
    }
  };

  make_y_combinator([&](auto merge_sort, int32_t low, int32_t high) -> void {
    if (low == high) {
      return;
    }

    int32_t mid = (low + high) / 2;
    merge_sort(low, mid);
    merge_sort(mid + 1, high);

    merge(low, mid + 1, high);
  })(0, size - 1);
}

void solution_radix_sort(Array &arr, int32_t size) {
  auto digit = [](int32_t num, int32_t exp) -> int32_t {
    return (num / exp) % 10;
  };

  auto radix_count = [&](int32_t exp) -> void {
    Array sorter(size, 0x0);
    Array bucket(10, 0x0);

    for (int32_t i = 0; i < size; i++) {
      bucket[digit(arr[i], exp)]++;
    }

    for (int32_t i = 1; i < 10; i++) {
      bucket[i] += bucket[i - 1];
    }

    for (int32_t i = size - 1; i >= 0; i--) {
      sorter[--bucket[digit(arr[i], exp)]] = arr[i];
    }

    for (int32_t i = 0; i < size; i++) {
      arr[i] = sorter[i];
    }
  };

  int32_t max = arr[0];
  for (int32_t i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  for (int32_t exp = 1; max / exp > 0; exp *= 10) {
    radix_count(exp);
  }
}

int32_t main(void) {
  solution_test({
    { solution_radix_sort,             "solution_radix_sort"             },
    { solution_merge_sort,             "solution_merge_sort"             },
    // { solution_quicksort_normal,       "solution_quicksort_normal"       },
    // { solution_quicksort_nonrecursive, "solution_quicksort_nonrecursive" },
    { solution_quicksort_2way,         "solution_quicksort_2way"         },
    // { solution_quicksort_3way,         "solution_quicksort_3way"         },
    { solution_heap_sort,              "solution_heap_sort"              },
    { solution_counting_sort,          "solution_counting_sort"          },
    { solution_bucket_sort,            "solution_bucket_sort"            },
    { solution_shell_sort,             "solution_shell_sort"             },
    { solution_insert_sort,            "solution_insert_sort"            },
    { solution_selection_sort,         "solution_selection_sort"         },
    { solution_bubble_sort,            "solution_bubble_sort"            },
  });

  solution_benchmark({
    { solution_radix_sort,             "solution_radix_sort"             },
    { solution_merge_sort,             "solution_merge_sort"             },
    // { solution_quicksort_normal,       "solution_quicksort_normal"       },
    // { solution_quicksort_nonrecursive, "solution_quicksort_nonrecursive" },
    { solution_quicksort_2way,         "solution_quicksort_2way"         },
    // { solution_quicksort_3way,         "solution_quicksort_3way"         },
    { solution_heap_sort,              "solution_heap_sort"              },
    { solution_counting_sort,          "solution_counting_sort"          },
    { solution_bucket_sort,            "solution_bucket_sort"            },
    { solution_shell_sort,             "solution_shell_sort"             },
    { solution_insert_sort,            "solution_insert_sort"            },
    { solution_selection_sort,         "solution_selection_sort"         },
    { solution_bubble_sort,            "solution_bubble_sort"            },
  });

  return 0;
}
