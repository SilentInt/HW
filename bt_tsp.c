#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20
#define INF INT_MAX

int n;
int graph[MAX_N][MAX_N];
int visited[MAX_N];  // 记录节点是否访问过
int path[MAX_N];     // 记录路径
int path_min[MAX_N]; // 记录最短路径
int min_len = INF;   // 记录最短路径长度
int cur;             // 当前起点
int cur_min;         // 当前最短路径start

void print_path() {
  for (int i = 0; i < n; i++) {
    printf("%d->", path[i]);
  }
  printf("%d\n", cur);
}

void print_path_min() {
  for (int i = 0; i < n; i++) {
    printf("%d->", path_min[i]);
  }
  printf("%d\n", cur_min);
}

/**
 * @param current 当前节点
 * @param len 当前路径长度
 * @param count 当前已经走过的节点数
 */
void tsp(int current, int len, int count) {
  if (count == n) {
    // 从最后一个节点回到起点
    if (!graph[current][cur]) {
      // 如果回不到起点，直接返回
      return;
    } else if (len + graph[current][cur] < min_len) {
      min_len = len + graph[current][cur];
      cur_min = cur;
      printf("UpdP:");
      // 打印路径
      print_path();
      // 更新path_min
      for (int i = 0; i < n; i++) {
        path_min[i] = path[i];
      }
    } else {
      printf("BCut:");
      print_path();
    }
    return;
  }

  // 从当前节点出发，遍历所有未访问过的节点
  for (int i = 0; i < n; i++) {
    // 如果节点未访问过
    if (!visited[i] && graph[current][i]) {
      visited[i] = 1;                             // 标记为已访问
      path[count] = i;                            // 记录路径
      tsp(i, len + graph[current][i], count + 1); // 继续遍历下一个节点
      visited[i] = 0;                             // 回溯, 标记为未访问
    }
  }
}

int main() {
  printf("\e[33m计212 215216 赵桂龙\n实验环境：Ubuntu 22.04.2 "
         "LTS\nGCC:11.3.0\e[0m\n");
  printf("Input node cnt:\n");
  scanf("%d", &n); // 读入节点数

  // 读入图
  printf("Input graph matrix\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &graph[i][j]);
    }
  }

  for (int i = 0; i < n; i++) {
    printf("Start from %d\n", i);
    cur = i; // 记录起点
    visited[i] = 1;
    path[0] = i;
    tsp(i, 0, 1);
    visited[i] = 0;
    path[i] = 0;

    // 清空path
    for (int j = 0; j < n; j++) {
      path[j] = 0;
    }
  }
  printf("Current min vector:");
  print_path_min();

  printf("min length: %d\n", min_len);

  return 0;
}
