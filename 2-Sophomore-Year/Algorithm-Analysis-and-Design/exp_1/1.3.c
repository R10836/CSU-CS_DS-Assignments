#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct Work { int id; int start; int end; int reward; };

int max(int a, int b){ return a > b ? a : b; }

int main() {
    int n; scanf("%d", &n); // 读取任务数量
    struct Work works[n]; // 声明一个包含 n 个 Work 结构体的数组

    // 读取每个任务的输入并初始化 works 数组
    for (int i = 0; i < n; i++) {
        int id, r, start_h, start_m, start_s, end_h, end_m, end_s;
        scanf("%d %d %d:%d:%d %d:%d:%d", &id, &r, &start_h, &start_m, &start_s, &end_h, &end_m, &end_s); 
        int start = start_h * 60 + start_m; // 将开始时间转换为分钟表示
        int end = end_h * 60 + end_m; // 将结束时间转换为分钟表示
        works[i].id = id; 
        works[i].start = start; 
        works[i].end = end; 
        works[i].reward = r; 
    }

    int pre[n], dp[n];
    memset(pre, -1, sizeof(pre)); // 初始化 pre 数组，表示每个任务的前一个任务索引
    memset(dp, 0, sizeof(dp)); // 初始化 dp 数组，表示到达每个任务时的最大奖励
    dp[0] = works[0].reward; // 第一个任务的最大奖励为其自身的奖励

    // 动态规划计算最大奖励
    for (int i = 1; i < n; i++) {
        dp[i] = works[i].reward; // 初始化当前任务的最大奖励为其自身的奖励
        for (int j = 0; j < i; j++) {
            if (works[j].end <= works[i].start) { // 如果任务 j 的结束时间早于等于任务 i 的开始时间
                // 更新最大奖励，并记录前一个任务索引
                dp[i] = max(dp[i], dp[j] + works[i].reward);
                if (dp[i] == dp[j] + works[i].reward) {
                    pre[i] = j; // 更新前一个任务索引为 j
                }
            }
        }
        if (dp[i] < dp[i - 1]) { // 如果当前任务的最大奖励小于前一个任务的最大奖励
            dp[i] = dp[i - 1]; // 取前一个任务的最大奖励作为当前任务的最大奖励
            pre[i] = pre[i - 1]; // 更新前一个任务索引
        }
    }
    
    int maxSet[n], cnt = 0, idx = n - 1;

    // 构建最大奖励的任务集合
    while (pre[idx] != -1) {
        maxSet[cnt++] = works[idx].id;
        idx = pre[idx];
    }
    maxSet[cnt++] = works[idx].id;
    
    printf("{");
    for (int i = cnt - 1; i >= 0; i--) {
        printf("%d", maxSet[i]);
        if (i > 0) {
            printf(",");
        }
    }
    printf("}\n%d", dp[n - 1]); // 输出最大奖励及任务集合
    
    return 0;
}