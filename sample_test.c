
#include <stdio.h>
#include <string.h>

// This is a sample program to test lexical analyzer
int main() {
    int a = 10, b = 20;
    char ch = 'Z';
    float pi = 3.14;

    /* Multi-line comment
       explaining variables */

    for(int i = 0; i < b; i++) {
        if(i % 2 == 0) {
            printf("Even number: %d\n", i);
        } else {
            printf("Odd number: %d\n", i);
        }
    }

    // Unterminated string error test
    printf("Hello World\n);

    // Unknown char test: @
    return 0;
}
