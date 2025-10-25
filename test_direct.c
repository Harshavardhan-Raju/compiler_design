int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int result;
    int k = 5;
    result = factorial(k);
    printf("Factorial of 5 = %d", result);
    return 0;
}
