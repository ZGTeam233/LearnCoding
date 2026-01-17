#include <stdio.h>

//判断质数逻辑
int isPrime(const int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    //输入两个数
    int m;
    int n;
    printf("Please enter two numbers.\nThe first number must be less than or equal to the second number.\nEnter first number: ");
    scanf("%d", &m);
    printf("Enter second number: ");
    scanf("%d", &n);

    //防崩溃
    if (m > n) {
        printf("ERROR!\nThe numbers must less than or equal to the numbers.\n");
        return 0;
    }
    if (n - m > 511) {
        printf("ERROR!\nTooooo long!\n0");
        return 0;
    }

    //判断与输出
    for (int j = m; j <= n; j++) {
        if (isPrime(j)) {
            printf("%d is a prime number.\n", j);
        }
    }
    return 0;
}

