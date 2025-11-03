// // Corrected Fibonacci - Changed i++ to i = i + 1

// int fib_iter(int n) {
//     int a = 0;
//     int b = 1;
//     int temp;
//     int i;
//     for (i = 2; i <= n; i = i + 1) {  // Changed i++ to i = i + 1
//         temp = a + b;
//         a = b;
//         b = temp;
//     }
//     return b;
// }

// int main() {
//     int x = 7;
//     int result = fib_iter(x);
//     printf("Fibonacci(%d) = %d\n", x, result);
//     return 0;
// }

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int result;
    result = factorial(5);
    printf("Factorial = %d\n", result);
    return 0;
}

// int main(){
//     int a = 2;
//     int b;
//     b = 2 + "hello";
//     printf("%d",b);
//     return 0;
// }