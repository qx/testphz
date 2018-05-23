#include "stdio.h"
#include "hulib.h"

void testhuxi() {
    //       2, 3, 4,
//                9, 19, 19,
//                14, 15, 16,
//                13, 13, 3,
//                12, 13, 14,
//                5, 5, 15,
//                6, 6, 16)

    char cards[] = {0, 1, 2, 1, 2, 2, 0, 0, 1, 0, 0, 1, 3, 2, 2, 2, 0, 0, 2, 0};
//    char cards[] = {0, 2, 1, 2, 2, 1, 0, 2, 1, 1, 0, 1, 0, 0, 1, 1, 2, 2, 0,
//                    1};// 4,5,6, 2,2,12, 17,20, 15,16,17 ,3,4,5,3,3,13,8,9,10
    printf("胡息: %d\n", get_huxi(cards));
}

int main() {
//    printf("Hello, World!\n");
    testhuxi();
    return 0;
}