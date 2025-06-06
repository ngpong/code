#include "common.hpp"

// 题目：
// 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
//
// 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
//
// 返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

// 由题目可知，我们需要找的是 i < j && max(prices[i] < prices[j]) 配对；也就是说，理论情况下最佳收益额应当 = 某一天的收益 - 最小收益；
//
// 从左到右枚举卖出价格 prices[i]，那么要想获得最大利润，我们需要知道第 i 天之前，股票价格的最小值是什么，也就是从
// prices[0] 到 prices[i−1] 的最小值，把它作为买入价格，这可以用一个变量维护（请注意，该变量维护的是 prices[i] 左侧
// 元素的最小值）。
int32_t maxProfit(std::vector<int32_t> prices) {
  int32_t ans  = 0;               // 总收益；
  int32_t cost = *prices.begin(); // 最低收益价格；

  // 向后遍历序列中给定往后的所有当天收益情况；
  for (int32_t i = 0; i < prices.size(); ++i) {
    // 在序列 [i...end] 的部分未知的情况下，即便之前已获得了一个看似较佳的收益总额也还是要替换掉收益更小那一项以在后续的迭代中寻找到收益额最佳或者说相较于之前更加的配对；
    cost = std::min(cost, prices[i]);
    // 计算当天 i 的收益与最小收益额的差可知：如果在第i天买入卖出，则理应的最佳收益额是多少；替换收益额更大的那一项；
    ans = std::max(ans, prices[i] - cost);
  }

  return ans;
}

int main(void) {
  std::vector<int32_t> datas = { 1, 2, 5, 6, 7, 0, 9 };

  std::cout << maxProfit(datas) << std::endl;

  return EXIT_SUCCESS;
}
