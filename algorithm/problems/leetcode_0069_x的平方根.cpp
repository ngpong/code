#include "common.hpp"

int32_t solution(int32_t x) {
  int32_t lt = 0, gt = x / 2 + 1;
  while (lt <= gt) {
    int32_t mid = (lt + gt) >> 1;
    int32_t sqt = mid * mid;

    if (x < sqt) {
      gt = mid - 1;
    } else if (x > sqt) {
      lt = mid + 1;
    } else {
      return mid;
    }
  }

  if (gt < lt) {
    return gt;
  } else {
    return lt;
  }
}
