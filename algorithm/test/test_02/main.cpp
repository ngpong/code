#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>

static constexpr int32_t array_size = 20;

using Array = std::array<int32_t, array_size>;

Array init() {
  return { 7, 1, 7, 2, 4, 7, 8, 10, 1, 2, 15, 2, 2, 3, 1, 12, 11, 7, 13, 14 };
}

void quick_sort_1(Array &arr, int32_t low, int32_t high) {
  if (low >= high)
    return;

  int32_t pivot = arr[low];

  int32_t i = low, lt = low, gt = high + 1;

  while (i < gt) {
    if (arr[i] < pivot) {
      std::swap(arr[i++], arr[lt++]);
    } else if (pivot < arr[i]) {
      std::swap(arr[i], arr[--gt]);
    } else {
      i++;
    }
  }

  quick_sort_1(arr, low, lt - 1);
  quick_sort_1(arr, gt, high);
}

void quick_sort_2(Array &arr, const int32_t low, const int32_t high) {
  if (low >= high) {
    return;
  }

  int32_t pivot = arr[low];

  int32_t lt = low;
  int32_t gt = high + 1;
  int32_t i  = low + 1;

  while (i < gt) {
    if (arr[i] < pivot) {
      std::swap(arr[i], arr[lt + 1]);
      i++;
      lt++;
    } else if (arr[i] > pivot) {
      std::swap(arr[i], arr[gt - 1]);
      gt--;
    } else {
      i++;
    }
  }

  std::swap(arr[lt], arr[low]);

  quick_sort_2(arr, low, lt - 1);
  quick_sort_2(arr, lt + 1, high);
}

int32_t _find_topk_1(Array &datas, int32_t kth, int32_t low, int32_t high) {
  if (low >= high) {
    return datas[low];
  }

  int32_t p = datas[low];

  int32_t lt = low, gt = high + 1, i = low + 1;
  while (i < gt) {
    if (datas[i] < p) {
      std::swap(datas[i++], datas[lt++]);
    } else if (datas[i] > p) {
      std::swap(datas[i], datas[--gt]);
    } else {
      i++;
    }
  }

  if (kth < lt) {
    return _find_topk_1(datas, kth, low, lt - 1);
  } else if (kth >= gt) {
    return _find_topk_1(datas, kth, gt, high);
  } else {
    return p;
  }
}
void find_topk_1(Array &datas, int32_t k) {
  _find_topk_1(datas, k, 0, datas.size() - 1);
}

int32_t _find_topk_2(Array &datas, int32_t k, int32_t low, int32_t high) {
  if (low >= high) {
    return datas[low];
  }

  int32_t p = datas[low];

  int32_t lt = low, gt = high;
  while (lt < gt) {
    while (lt < gt && datas[gt] >= p) {
      --gt;
    }
    while (lt < gt && datas[lt] <= p) {
      ++lt;
    }
    if (lt < gt) {
      std::swap(datas[lt], datas[gt]);
    }
  }
  std::swap(datas[low], datas[lt]);

  if (k == lt) {
    return p;
  } else if (k < lt) {
    return _find_topk_2(datas, k, low, lt - 1);
  } else {
    return _find_topk_2(datas, k, lt + 1, high);
  }
}
void find_topk_2(Array &datas, int32_t k) {
  _find_topk_2(datas, k, 0, datas.size() - 1);
}

int32_t main(int32_t argc, char *argv[]) {
  Array arr = init();

  {
    Array arr1 = arr;

    find_topk_1(arr1, 3);
  }

  {
    Array arr2 = arr;

    find_topk_2(arr2, 3);
  }

  return 0;
}
