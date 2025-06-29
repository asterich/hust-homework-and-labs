//
// Created by asterich on 2023/10/17.
//

#include <stdio.h>

long long int compute(long long int a, long long int b) {
    long long int sum = 0;
    while (a < b) {
        if (a % 2 == 0) {
            sum += a;
            a += 2;
        } else {
            sum += a * 2;
            a += 3;
        }
    }
    return sum;
}

int main() {
    long long int result = 0;
    for (int i = 1; i < 100; ++i) {
        result = compute(5, 100000005);
    }
    printf("Result: %lld\n", result);
    return 0;
}
