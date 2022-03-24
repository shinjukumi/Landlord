#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//每张牌出现的次数
// a0:3
// a1:4
//..
// a10:K
// a11:A
// a12:2
// a13:王1
// a14:王2
int a[15];
//出牌次数:num0
int num0;
//中间变量nu
int nu = 0;

//初步统计出牌次数（每张牌的个数为0-4，故可以把每张牌作为一个整体出牌）
int first() {
    for (int i = 0; i < 13; i++) {
        if (a[i] != 0) {
            nu++;
        }
    }
    if (a[13] == 1 || a[14] == 1) {
        nu++;
    }
    return nu;
}

void dfs(int n) {
    if (n >= num0){
        return;
    }
    int n1 = 0;
    nu = 0;
    n1 = first(); //计算剩下的a[] 的牌的种类数
    if (n1 + n < num0) {
        num0 = n1 + n;
    }
    if (n1 == 0) { //如果没有牌剩下
        if (num0 > n) {
            num0 = n;
        }
        return;
    }

    //顺子（5个及以上）
    for (int i = 0; i < 8; i++) {
        int index = i;
        int numm = 0;
        while (a[index] >= 1 && index < 13) {
            index++;
            numm++;
        }
        if (numm >= 5) {
            for (int ii = i; ii < index; ii++) {
                a[ii]--;
            }
            dfs(n + 1);
            for (int ii = i; ii < index; ii++) {
                a[ii]++;
            }
        }
    }
    //两个个及以上trio
    for (int i = 0; i < 11; i++) {
        int index = i;
        int numm = 0;
        while (a[index] >= 3 && index < 13) {
            index++;
            numm++;
        }
        if (numm >= 2) {
            for (int ii = i; ii < index; ii++) {
                a[ii] = a[ii] - 3;
            }
            dfs(n + 1);
            for (int ii = i; ii < index; ii++) {
                a[ii] = a[ii] + 3;
            }
        }
    }
    //三个个及以上pair
    for (int i = 0; i < 10; i++) {
        int index = i;
        int numm = 0;
        while (a[index] >= 2 && index < 13) {
            index++;
            numm++;
        }
        if (numm >= 3) {
            for (int ii = i; ii < index; ii++) {
                a[ii] = a[ii] - 2;
            }
            dfs(n + 1);
            for (int ii = i; ii < index; ii++) {
                a[ii] = a[ii] + 2;
            }
        }
    }
    //三带一
    for (int i = 0; i < 13; i++) {
        if (a[i] >= 3) {
            a[i] = a[i] - 3;
            for (int ii = 0; ii < 15; ii++) {
                if (a[ii] >= 1 && ii != i) {
                    a[ii]--;
                    dfs(n + 1);
                    a[ii]++;
                }
            }
            a[i] = a[i] + 3;
        }
    }
    //三带一对
    for (int i = 0; i < 13; i++) {
        if (a[i] >= 3) {
            a[i] = a[i] - 3;
            for (int ii = 0; ii < 15; ii++) {
                if (a[ii] >= 2 && ii != i) {
                    a[ii] = a[ii] - 2;
                    dfs(n + 1);
                    a[ii] = a[ii] + 2;
                }
            }

            a[i] = a[i] + 3;
        }
    }

    //四带二
    for (int i = 0; i < 13; i++) {
        if (a[i] == 4) {
            a[i] = a[i] - 4;
            for (int ii = 0; ii < 15; ii++) {
                if (a[ii] >= 1) {
                    a[ii] = a[ii] - 1;
                    for (int iii = ii + 1; iii < 15; iii++) {
                        if (a[iii] >= 1 && iii != 14) {
                            a[iii] = a[iii] - 1;
                            dfs(n + 1);
                            a[iii] = a[iii] + 1;
                        }
                    }
                    a[ii] = a[ii] + 1;
                }
            }
            a[i] = a[i] + 4;
        }
    }
    //四带二对
    for (int i = 0; i < 13; i++) {
        if (a[i] == 4) {
            a[i] = a[i] - 4;
            for (int ii = 0; ii < 15; ii++) {
                if (a[ii] >= 2) {
                    a[ii] = a[ii] - 2;
                    for (int iii = ii + 1; iii < 15; iii++) {
                        if (a[iii] >= 2) {
                            a[iii] = a[iii] - 2;
                            dfs(n + 1);
                            a[iii] = a[iii] + 2;
                        }
                    }
                    a[ii] = a[ii] + 2;
                }
            }
            a[i] = a[i] + 4;
        }
    }
}

int main() {
    int T;
    int n;
    int *c = (int *)malloc(sizeof(int) * (n + 7));
    scanf("%d %d", &T, &n); 
    while (T--) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &c[i]);
        }
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n; i++) {
            if (c[i] == 1) {
                a[11]++;
            } else if (c[i] == 2) {
                a[12]++;
            } else if (c[i] == 14) {
                a[13]++;
            } else {
                a[c[i] - 3]++;
            }
        }
        //如果有两张王，将两张王作为两个单张存在与数组中 分别为c13和c14
        if (a[13] == 2) {
            a[13] = 1;
            a[14] = 1;
        }
        nu = 0;
        num0 = first(); //初步寻找次数
        dfs(0);
        printf("%d\n", num0);
    }
    free(c);
    return 0;
}