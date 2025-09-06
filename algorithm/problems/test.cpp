#include "common.hpp"

bool increasingTriplet(std::vector<int32_t>& nums) {
  int32_t n = nums.size();
  if (n < 3) {
    return false;
  }

  std::vector<int32_t> lmins(n);
  lmins[0] = nums[0];
  for (int32_t i = 1; i < n; i++) {
    lmins[i] = std::min(lmins[i - 1], nums[i]);
  }

  std::vector<int32_t> rmaxs(n);
  rmaxs[n - 1] = nums[n - 1];
  for (int32_t i = n - 2; i >= 0; i--) {
    rmaxs[i] = std::max(rmaxs[i + 1], nums[i]);
  }

  for (int32_t i = 1; i < n - 1; i++) {
    int32_t j = i - 1;
    int32_t k = i + 1;
    if (lmins[j] < nums[i] && nums[i] < rmaxs[k]) {
      return true;
    }
  }

  return false;
}

int32_t main(int32_t argc, char *argv[]) {
}
