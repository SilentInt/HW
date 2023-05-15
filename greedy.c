#include <limits.h>
#include <stdio.h>

#define MAX_G 20

int graph[MAX_G][MAX_G]; // 邻接矩阵
int dis[MAX_G];          // 距离矩阵
int path[MAX_G];         // 路径记录
int visited[MAX_G];      // 访问标记
int n;                   // 节点个数
int sta, end;            // 起点和终点

// 递归打印路径
void printPath(int i) {
  if (path[i] == -1) {
    return;
  }
  printPath(path[i]);
  printf("->%d", i);
}

int main() {
  printf("\e[33m计212 215216 赵桂龙\n实验环境：Ubuntu 22.04.2 "
         "LTS\nGCC:11.3.0\e[0m\n");
  printf("Input node cnt:");
  scanf("%d", &n);
  int eg; // 边数
  printf("Input edge cnt\n");
  scanf("%d", &eg);
  printf("input edges: sta end weight\n");
  // 初始化邻接矩阵
  for (int i = 0; i < eg; i++) {
    int x, y, w;
    scanf("%d %d %d", &x, &y, &w);
    graph[x][y] = w;
    graph[y][x] = w;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }
  // 输入起点和终点
  printf("Input sta and end:");
  scanf("%d%d", &sta, &end);
  // 初始化距离矩阵和路径记录
  for (int i = 0; i < n; ++i) {
    dis[i] = INT_MAX;
    path[i] = -1;
  }

  // 从起点开始
  dis[sta] = 0;
  for (int i = 0; i < n; ++i) {
    // 找到距离最近且未访问过的点
    int min = INT_MAX, min_idx;
    for (int j = 0; j < n; ++j) {
      // 找到距离最近且未访问过的点
      if (!visited[j] &&  // Not visited
          dis[i] != -1 && // Reachable
          dis[j] < min    // Shorter
      ) {
        min = dis[j];
        min_idx = j;
      }
    }
    // 将距离起点最近的点标记为已访问
    visited[min_idx] = 1;
    // 更新其邻接点的距离
    for (int j = 0; j < n; ++j) {
      if (graph[min_idx][j] && // Reachable
          visited[j] == 0 &&   // Not visited
          dis[min_idx] + graph[min_idx][j] <
              dis[j] // New distance shorter than before
      ) {
        // Update distance and path of neighbour node
        dis[j] = dis[min_idx] + graph[min_idx][j];
        path[j] = min_idx;
      }
    }
  }
  printf("Distance from sta to end:\n");
  for (int i = 0; i < n; ++i) {
    printf("%d ", dis[i]);
  }
  printf("\npath array:\n");
  for (int i = 0; i < n; i++) {
    printf("%d ", path[i]);
  }
  printf("\npath:\n%d", sta);
  printPath(end);
  printf("\n");
}
