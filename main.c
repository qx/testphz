#include "stdio.h"
#include "hulib.h"

void testhuxi() {
//    char cards[] = {0, 1, 2, 1, 2, 2, 0, 0, 1, 0, 0, 1, 3, 2, 2, 2, 0, 0, 2, 0};
    char cards[] = {0, 2, 1, 2, 2, 1, 0, 2, 1, 1, 0, 1, 0, 0, 1, 1, 2, 2, 0, 1};
    printf("胡息: %d\n", get_huxi(cards));
}
int main() {
    printf("Hello, World!\n");
    testhuxi();
    return 0;
}