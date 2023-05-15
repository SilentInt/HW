#include <stdio.h>
#define MAX_W 100

int weight[MAX_W];
int back[MAX_W];
int n;
int contain;
int max_w;
int cur_w;
void bk(int cur) {
  if (cur == n - 1) {
    cur_w = cur_w + weight[cur];
    if (cur_w < contain && cur_w > max_w) {
      max_w = cur_w;
    }
  }
}
int main() {
  printf("How many things:\n");
  scanf("%d", &n);
  printf("Input contain of back:\n");
  scanf("%d", &contain);
  printf("Input weights:\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", &weight[i]);
  }
}
