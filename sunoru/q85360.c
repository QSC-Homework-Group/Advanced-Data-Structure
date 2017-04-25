#include <stdio.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int favorite[220], order[220];
    int f[2][220];
    int n, m, l, i, j;
    int t, x, s;
    
    scanf("%d", &n);
    for (i = 0; i <= n; ++i) {
        order[i] = -1;
    }
    scanf("%d", &m);
    for (i = 0; i < m; ++i) {
        scanf("%d", &favorite[i]);
        order[favorite[i]] = i;
    }
    scanf("%d", &l);
    for (i = 0; i <= n; ++i) {
        f[0][i] = 0;
    }
    t = 0;
    for (i = 0; i < l; ++i) {
        t = 1 - t;
        scanf("%d", &x);
        if (order[x] == -1) {
            t = 1 - t;
            continue;
        }
        for (j = 0; j <= n; ++j) {
            f[t][j] = f[1 - t][j];
        }
        for (j = 0; j <= order[x]; ++j) {
            f[t][x] = max(f[t][x], f[1 - t][favorite[j]] + 1);
        }
    }
    s = 0;
    for (i = 0; i <= n; ++i) {
        s = max(s, f[t][i]);
    }
    printf("%d\n", s);

    return 0;
}
