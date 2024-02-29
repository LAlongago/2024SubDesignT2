#include <stdio.h>

int main() {
    int autoVar = 0;
    for (int i = 0; i < 10; i++) {
        autoVar += i;
    }
    printf("autoVar: %d\n", autoVar);
    return 0;
}
