#include "common.hpp"

// Lookup table for fast calculation of bits set in 8-bit unsigned char.
static constexpr unsigned char popcount8[] = {
  //  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
  //  =====================================================
      0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, // 0x0_
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 0x1_
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 0x2_
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 0x3_
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 0x4_
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 0x5_
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 0x6_
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // 0x7_
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 0x8_
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 0x9_
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 0xA_
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // 0xB_
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 0xC_
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // 0xD_
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // 0xE_
      4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8  // 0xF_
};
unsigned char popcount16(unsigned short x) {
  return popcount8[x >> 8] +
         popcount8[x &  0xff];
}
unsigned char popcount32(unsigned int x) {
  return popcount16(x >> 16) +
         popcount16(x &  0xffff);
}
std::vector<int> solution1(unsigned int n) {
  std::vector<int> ret;
  for (int32_t i = 0; i <= n; i++) {
    ret.push_back(popcount32(i));
  }

  return ret;
}

std::vector<int> solution2(unsigned int n) {
  std::vector<int> ret;

  for (int32_t i = 0; i <= n; i++) {
    int count = 0;
    for (; n; ++count) {
      // 将 n 的最低位的 1 变成 0；并将后续的所有位都反转；
      unsigned int mask = n - 1;

      // 在上一步完成后，此时最低位的 1 此时为 0；且后续的所有位都被反转；

      // 此时与 mask 执行逻辑与操作的后就能够直接剔除掉找到的那一位至最低位的所有位；
      // 除非被剔除位置到最高位还有 1，否则结束循环；
      n &= mask;
    }
    ret.push_back(count);
  }

  return ret;
}

std::vector<int> solution4(unsigned int n) {
  std::vector<int> ret;

  for (int32_t i = 0; i <= n; i++) {
    int count = 0;
    for (; n; ++count) {
      // 统计从 num 低位开始直到到达1时需要经过几个 0
      unsigned int i = __builtin_ctz(n);

      // 左移 i 位并得到 __builtin_ctz 具体操作的那一位
      unsigned int mask = 1 << i;

      // 从 n 中移除那一位，并继续下一轮循环
      n &= ~mask;
    }

    ret.push_back(count);
  }

  return ret;
}

std::vector<int> solution4(int n) {
  std::vector<int> ret(n);
  ret[0] = 0;
  for (int i = 1; i <= n; i++) {
    if (i % 2 > 0) { // odd
      ret[i] = ret[i - 1] + 1;
    } else {
      ret[i] = ret[i / 2];
    }
  }
  return ret;
}
