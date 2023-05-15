#include <stdio.h>

#define MAX_N 100  // 最大物品数量
#define MAX_W 1000 // 最大背包容量

int n;                // 物品数量
int W;                // 背包容量
int w[MAX_N];         // 物品重量
int v[MAX_N];         // 物品价值
int path[MAX_N];      // 选择的物品
int best_path[MAX_N]; // 最优解
int max_v;            // 最大价值

// output the best_path
void output() {
  for (int i = 0; i < n; i++) {
    if (best_path[i]) {
      printf("%d ", i + 1);
    }
  }
  printf("\n");
}

// output the path
void output_path() {
  for (int i = 0; i < n; i++) {
    if (path[i]) {
      printf("%d ", i + 1);
    }
  }
  printf("\n");
}

/**
 * @brief 回溯法求解背包问题
 * @param i 当前物品编号
 * @param cw 当前背包重量
 * @param cv 当前背包价值
 */
void backtrack(int i, int cw, int cv) {
  // 所有物品都已经考察完毕
  if (i == n) {
    // 价值超过最优解
    if (cv > max_v) {
      max_v = cv;
      // 记录最优解
      for (int j = 0; j < n; j++) {
        best_path[j] = path[j];
      }
      printf("UpdP:");
      output();
      return;
    }
    // 价值没有超过最优解
    printf("SCut:");
    output_path();
    return;
  }
  //  选择第i个物品
  path[i] = 1;                              // 记录选择的物品
  if (cw + w[i] <= W) {                     // 重量超过背包容量
    backtrack(i + 1, cw + w[i], cv + v[i]); // 选第i个物品
  } else {
    // 重量超过背包容量
    printf("BCut:");
    output_path();
  }
  path[i] = 0; // 清除选择的物品
  // 不选第i个物品
  backtrack(i + 1, cw, cv);
}

int main() {
  printf("\e[33m计212 215216 赵桂龙\n实验环境：Ubuntu 22.04.2 "
         "LTS\nGCC:11.3.0\e[0m\n");
  // 读入数据
  scanf("%d %d", &n, &W);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &w[i], &v[i]);
  }
  backtrack(0, 0, 0);
  printf("Solution:");
  output();
  printf("Max value:%d\n", max_v);
  return 0;
}
