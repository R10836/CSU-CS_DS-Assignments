#include <stdio.h>
#include <string.h>

// 定义长整型
#define ll long long

// 定义常量
#define Size 1010
const int N = 3333;
const int MOD = 1e9;

// 大整数结构体
struct BigInt {
  ll *s; // 数组指针，用于存储大整数的每一位
  int c; // 有效位数

  // 初始化大整数
  void init() {
    s = new ll[20]; // 分配空间
    for (int i = 0; i < 20; i++)
      s[i] = 0; // 初始化每一位为0
    c = 0; // 有效位数为0
  }

  // 大整数与整数相加
  void add(int x) {
    s[0] += x; // 将整数加到最低位
    int i = 0;
    while (s[i] >= MOD) {
      s[i + 1] += s[i] / MOD; // 进位
      s[i] %= MOD; // 取模
      i++;
    }
    while (s[c + 1])
      c++; // 更新有效位数
  }

  // 大整数与另一个大整数相加
  void add(const BigInt &x) {
    int r = (c > x.c) ? c : x.c; // 取两个大整数有效位数的较大值
    for (int i = 0; i <= r; i++) {
      s[i] += x.s[i]; // 对应位相加
      if (s[i] >= MOD) {
        s[i + 1] += s[i] / MOD; // 进位
        s[i] %= MOD; // 取模
      }
    }
    c = (19 < r + 1) ? 19 : (r + 1); // 更新有效位数
    while (c && s[c] == 0)
      c--; // 去除高位的0
  }
};

// 字符串匹配自动机
struct ZXLZDJ {
  int ch[N][58]; // 状态转移数组，ch[i][j]表示状态i在字符j下一个状态的编号

  // 构建自动机
  void build(char *s, int Len) {
    for (int i = Len; i; i--) {
      for (int j = 0; j < 58; j++)
        ch[i - 1][j] = ch[i][j]; // 复制上一个状态的转移信息
      ch[i - 1][s[i] - 'A'] = i; // 更新当前状态的转移信息
    }
  }

  // 重载[]运算符，用于快速访问状态转移数组
  int *operator[](const int &i) { return ch[i]; }
} A, B;

bool vis[N][N]; // 记录状态是否已访问
char s1[N], s2[N]; // 输入字符串
int n, m, op; // 输入字符串的长度
char ans[N]; // 存储结果

// 深度优先搜索，用于输出所有LCS
void dfs(int u, int v, int tt) {
  ans[tt] = '\0'; // 在结果末尾添加字符串结束符
  if (strlen(ans + 1) > 1)
    printf("%s\n", ans + 1); // 输出LCS
  for (int i = 0; i < 58; i++) {
    if (A[u][i] == 0 || B[v][i] == 0)
      continue; // 当前字符不存在于两个字符串中
    ans[tt] = i + 'A'; // 将字符添加到结果中
    dfs(A[u][i], B[v][i], tt + 1); // 继续搜索下一个状态
  }
}

// 最长公共子序列长度和方向数组
int DP[Size][Size];
int DIR[Size][Size];

// 求解最长公共子序列的长度
int LCS_length(char *a, char *b) {
  int M = strlen(a); // 字符串a的长度
  int N = strlen(b); // 字符串b的长度
  for (int i = 1; i <= M; i++) {
    for (int j = 1; j <= N; j++) {
      if (a[i - 1] == b[j - 1]) {
        DP[i][j] = DP[i - 1][j - 1] + 1; // 当前字符相等，LCS长度加1
        DIR[i][j] = 1; // 方向标记为1，表示斜向上
      } else if (DP[i - 1][j] >= DP[i][j - 1]) {
        DP[i][j] = DP[i - 1][j]; // 当前字符不相等，LCS长度不变，选择上方的状态
        DIR[i][j] = 2; // 方向标记为2，表示向上
      } else {
        DP[i][j] = DP[i][j - 1]; // 当前字符不相等，LCS长度不变，选择左方的状态
        DIR[i][j] = 3; // 方向标记为3，表示向左
      }
    }
  }
  return DP[M][N]; // 返回最长公共子序列的长度
}

int main() {
  scanf(" %s", s1 + 1); // 输入字符串1
  scanf(" %s", s2 + 1); // 输入字符串2
  n = strlen(s1 + 1); // 计算字符串1的长度
  m = strlen(s2 + 1); // 计算字符串2的长度
  printf("%d\n", LCS_length(s1 + 1, s2 + 1)); // 输出最长公共子序列的长度
  A.build(s1, n); // 构建字符串1的自动机
  B.build(s2, m); // 构建字符串2的自动机
  dfs(0, 0, 1); // 深度优先搜索输出所有LCS
  return 0;
}
//求最长公共子序列长度的时间复杂度为o(m*n),空间复杂度为o(m*n)
//求两个字符串的所有公共子序列的时间复杂度为o(2^k),空间复杂度为o(k).其中 k表示最长公共子序列的长度。