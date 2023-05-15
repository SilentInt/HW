#include <stdio.h>

#define MAX_N 100
#define MAX_P 100
int x[MAX_N]; // 向量解
int w[MAX_N]; // 重量
int v[MAX_N]; // 权重
int dp[MAX_N][MAX_P];
int n;    // 物品个数
int pack; // 背包容量

int main() {
  printf("\e[33m计212 215216 赵桂龙\n实验环境：Ubuntu 22.04.2 "
         "LTS\nGCC:11.3.0\e[0m\n");
  printf("请输入物品个数:");
  scanf("%d", &n);
  printf("请输入背包容量:");
  scanf("%d", &pack);
  printf("请输入物品重量和价值\n");
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &w[i]);
    scanf("%d", &v[i]);
  }
  // 初始化dp表格
  for (int i = 0; i <= n; ++i) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= pack; ++i) {
    dp[0][i] = 0;
  }
  // 进行迭代
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= pack; ++j) {
      if (j < w[i]) {
        // 当背包装不下当前物品
        // 当前最大价值为装入该物品前的最大价值
        dp[i][j] = dp[i - 1][j];
      } else {
        // 当背包能装下当前物品
        // 当前最大价值为:1.装入当前物品前的最大价值 2.装入当前物品后的价值
        int new_v = dp[i - 1][j - w[i]] + v[i]; // 装入后的最大价值
        dp[i][j] = new_v > dp[i - 1][j] ? new_v : dp[i - 1][j];
      }
    }
  }
  // 求装入背包的物品
  int c = pack;
  for (int i = n; i > 0; i--) {
    if (dp[i][c] > dp[i - 1][c]) {
      x[i] = 1;
      c -= w[i];
    } else
      x[i] = 0;
  }
  printf("背包的最大价值为:%d\n", dp[n][pack]);
  printf("向量解为:{");
  for (int i = 1; i <= n; ++i) {
    printf("%d", x[i]);
  }
  printf("}\n");
  printf("压状dp表格为:\n");
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= pack; ++j) {
      printf("%3d ", dp[i][j]);
    }
    printf("\n");
  }
}
