#include "common.hpp"

int solution(std::vector<int> &height) {
  int max = 0;

  int i = 0, j = height.size() - 1;
  while (i < j) {
    int height_i = height[i];
    int height_j = height[j];

    if (height_i == height_j) {
      i++;
      j--;
      max = std::max(max, height_i * (j - i));
    } else if (height_i < height_j) {
      i++;
      max = std::max(max, height_i * (j - i));
    } else if (height_j < height_i) {
      j--;
      max = std::max(max, height_j * (j - i));
    }
  }

  return max;
}
