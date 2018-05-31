#include "stdio.h"
#include "hulib.h"

void testhuxi() {
//    char cards[] = {0, 2, 1, 2, 2, 1, 0, 2, 1, 1, 0, 1, 0, 0, 1, 1, 2, 2, 0, 1};
    char cards[] = {0, 3, 0, 0, 0, 2, 1, 1, 1, 2, 0, 2, 1, 1, 0, 1, 1, 2, 1, 2};

    printf("胡息: %d\n", get_huxi(cards));
}
int main() {
    printf("Hello, World!\n");
    testhuxi();
    return 0;
}