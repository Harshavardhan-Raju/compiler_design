// #include <stdio.h>

int fib_iter(int n) {
    int a = 0;
    int b = 1;
    int temp;
    int i = 2;

    while (i <= n) {
        temp = a + b;
        a = b;
        b = temp;
        i = i + 1; // increment
    }

    return b;
}

int main() {
    int x = 7;
    int result = fib_iter(x);
    printf("Fibonacci(%d) = %d\n", x, result);
    return 0;
}
