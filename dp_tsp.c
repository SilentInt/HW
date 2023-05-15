#include <limits.h>
#include <stdio.h>

#define N 7         // 城市个数
#define INF INT_MAX // 无穷大

int graph[N][N];     // 城市之间的距离
int path[N][1 << N]; // 存储最短路径向量解
int memo[N][1 << N]; // 记忆化数组
int n;               // 城市个数
int sta;             // 起点

/*
 * @brief 旅行商问题
 * @param v 当前所在节点
 * @param S 当前已经访问过的节点集合
 * @return 从v出发，经过集合S中所有节点，最终回到起点的最短路径长度
 */
int tsp(int v, int S) {
  if (S == ((1 << n) - 1)) { // 集合S包含所有节点，回到起点
    return graph[v][sta];
  }
  if (memo[v][S] != -1) { // 记忆化，避免重复计算
    return memo[v][S];
  }
  int res = INF;
  for (int i = 0; i < n; i++) {
    if (!(S & (1 << i))) {      // 如果i不在集合S中，即i还未被访问
      int new_S = S | (1 << i); // 将i加入集合S中
      int sub_res = tsp(
          i,
          new_S); // 递归计算从i出发，经过new_S集合中所有点，最终到达点v的最短路径长度
      if (sub_res + graph[v][i] < res) { // 更新最短路径长度
        res = sub_res + graph[v][i];
        memo[v][S] = res; // 更新动态规划数组
        path[v][S] = i;   // 当前状态向下一个状态转移的最优解
      }
    }
  }
  return res;
}

// 输出路径函数
void print_path(int s, int u) {
  if (s == (1 << n) - 1) // 已经访问完所有节点
    return;
  int v = path[u][s];
  printf("%d->", v);           // 输出下一个节点
  print_path(s | (1 << v), v); // 递归访问下一个节点
}

int main() {
  printf("\e[33m计212 215216 赵桂龙\n实验环境：Ubuntu 22.04.2 "
         "LTS\nGCC:11.3.0\e[0m\n");
  // 输入节点个数
  printf("Input Node cnt\n");
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (1 << n); j++) {
      memo[i][j] = -1; // 初始化记忆化数组
    }
  }
  // 输入权值矩阵
  printf("Input weight matrix\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &graph[i][j]);
    }
  }
  printf("Start node:"); // 开始节点
  scanf("%d", &sta);
  int shortest_path = tsp(sta, 1 << sta); // 计算最短路径和权值

  // 输出最短路径和权值
  printf("Shortest path: %d\n", shortest_path);
  printf("Path: %d->", sta);
  print_path(1 << sta, sta);
  printf("%d\n", sta);
  printf("状态压缩dp数组:\n");
  // 输出状态压缩dp数组
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 1 << n; ++j) {
      if (memo[i][j] != -1)
        printf("%d\t", memo[i][j]);
      else
        printf(" \t");
    }
    printf("\n");
  }
}
