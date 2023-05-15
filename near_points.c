#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

typedef struct Node {
  int x;
  int y;
} Node;

Node P[N];

/**
 * Give the distance between two P
 * @param a Point a
 * @param b Point b
 * @return The distance between two P
 */
double point_dist(Node a, Node b) {
  double d2 = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
  return sqrt(d2);
}

/**
 * Find the min distance between two P in x area [left, right]
 * @param left Left limit of point index
 * @param right Right limit of point index
 * @return The min distance
 */
double min_dist(int left, int right) {
  if (right - left == 1) {
    return point_dist(P[left], P[right]);
  }
  if (right - left == 2) {
    double d1 = point_dist(P[left], P[left + 1]);
    double d2 = point_dist(P[left + 1], P[right]);
    double d3 = point_dist(P[left], P[right]);
    double d = d1 < d2 ? d1 : d2;
    return d < d3 ? d : d3;
  }
  // 分成左右两部分求解
  int mid = (left + right) >> 1;
  double lmin = min_dist(left, mid);
  double rmin = min_dist(mid, right);
  double d = lmin < rmin ? lmin : rmin;
  // 求解d区间
  double d_area = d;
  // 左右2d区间范围
  int lend = P[mid].x - (int)ceil(d);
  int rend = P[mid].x + (int)ceil(d);
  // 左右2d节点范围
  int point_sta = mid;
  int point_end = mid;
  for (int i = mid; i >= left && P[i].x >= lend; --i)
    point_sta = i;
  for (int i = mid; i <= right && P[i].x <= rend; ++i)
    point_end = i;
  // 遍历区间所有两点间距离
  for (int i = point_sta; i < mid; ++i) {
    for (int j = mid; j <= point_end; ++j) {
      double cur_dist = point_dist(P[i], P[j]);
      if (cur_dist < d_area)
        d_area = cur_dist;
    }
  }
  return d < d_area ? d : d_area;
}

/**
 * Sort the P' list
 * @param left
 * @param right
 */
void quick_sort(int left, int right) {
  if (left < right) {
    int lp = left, rp = right;
    while (lp < rp) {
      while (lp < rp && P[lp].x < P[rp].x)
        lp++;
      if (lp < rp) {
        Node t = P[lp];
        P[lp] = P[rp];
        P[rp] = t;
        rp--;
      }
      // 右侧扫描
      while (lp < rp && P[lp].x <= P[rp].x)
        rp--;
      if (lp < rp) {
        Node t = P[lp];
        P[lp] = P[rp];
        P[rp] = t;
        lp++;
      }
      // 左侧扫描
    }
    int pivot = lp;
    quick_sort(left, pivot - 1);
    quick_sort(pivot + 1, right);
  }
}

double force_d() {
  double d = sqrt(500 * 500);
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      double t = point_dist(P[i], P[j]);
      if (t < d)
        d = t;
    }
  }
  return d;
}

int main() {
  clock_t start, enddiv, endforce;

  printf("\e[33m计212 215216 赵桂龙\n实验环境：Ubuntu 22.04.2 "
         "LTS\nGCC:11.3.0\e[0m\n");

  srand((unsigned)time(0));
  // 数据生成
  for (int i = 0; i < 100; ++i) {
    P[i].x = rand() % 500;
    P[i].y = rand() % 500;
  }

  start = clock();
  quick_sort(0, N - 1);
  double div_d = min_dist(0, N - 1);
  enddiv = clock();
  double len = force_d();
  endforce = clock();
  printf("分治法:%lf\n", div_d);
  printf("蛮力法:%lf\n", len);
  // 打印时间
  printf("分治法用时:%lf\n", (double)(enddiv - start) / CLOCKS_PER_SEC);
  printf("蛮力法用时:%lf\n", (double)(endforce - enddiv) / CLOCKS_PER_SEC);

  return 0;
}
