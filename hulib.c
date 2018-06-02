#include <string.h>
#include "stdio.h"

int get_shun_huxi_xiao(char *cards);

int get_shun_huxi_da(char *cards);

int get_shun_huxi_da_without_2_7_10(char *cards, int num);

int get_huxi(char *cards) {

    int sum = 0;
    for (int i = 0; i < 20; i++) {
        sum += cards[i];
    }

    // 不带将
    if (sum % 3 == 0) {
        // 除坎以外的顺子的胡息
        int other_huxi = get_shun_huxi_xiao(cards);
        if (other_huxi < 0) {
            return -1;
        }
        return other_huxi;
    }

    // 带将
    int max_huxi = -1;
    char tmp_cards[20];
    for (int i = 0; i < 20; i++) {
        if (cards[i] != 2) continue;//无将直接-1
        memcpy(tmp_cards, cards, 20);
        tmp_cards[i] -= 2;
        int other_huxi = get_shun_huxi_xiao(tmp_cards);
        if (other_huxi > max_huxi) max_huxi = other_huxi;
    }

    if (max_huxi < 0) return -1;

    return max_huxi;
}

struct Item {
    int card;    // 是哪张牌
    int i;        // 第几种拆法
    int j;      // 正在进行第几种拆法
    int huxi;    // 胡息是多少
};

int get_shun_huxi_xiao(char *cards) {
    struct Item items[7];
    memset(items, 0, sizeof(items));

    int cur_card = 0;
    int cur_item = -1;//算法下标
    int find = 1;
    int max_huxi = -1;

    // 先拆小的
    while (1) {
        if (find) {
            find = 0;
            int finded = 0;
            if (cur_item == 7) {
                *(int *) 0 = 0;
            }
            // 找到第一张牌
            for (int i = cur_card; i < 10; i++) {
                if (cards[i] != 0) {
                    cur_card = i;
                    ++cur_item;
                    items[cur_item].card = cur_card;
                    finded = 1;
                    break;
                }
            }

            if (finded == 0) {
                // 小牌胡息
                int huxi = 0;
                for (int i = 0; i <= cur_item; ++i) {
                    huxi += items[i].huxi;
                }
                int da_huxi = get_shun_huxi_da(cards);
                if (da_huxi >= 0) {
                    if (da_huxi + huxi > max_huxi) {
                        max_huxi = da_huxi + huxi;
                    }
                }
                goto huisu;
            }
        }
        printf("当前算法:items  j------------------------------------>cur_item %d 第%d种\n", cur_item, items[cur_item].j);
        // 顺子
        if (items[cur_item].i == 0) {
            items[cur_item].i = 1;
            if (cur_card < 8 && cards[cur_card + 1] > 0 && cards[cur_card + 2] > 0) {
                items[cur_item].j = 1;
                items[cur_item].card = cur_card;
                --cards[cur_card];
                --cards[cur_card + 1];
                --cards[cur_card + 2];
                find = 1;
                printf("小顺子  ------------------------------------> %d", cur_card + 1);
                printf(" %d", cur_card + 2);
                printf(" %d\n", cur_card + 3);
                if (cur_card == 0) {
                    items[cur_item].huxi = 3;
                }
                continue;
            }
        }

        // 小小大绞
        if (items[cur_item].i == 1) {
            items[cur_item].i = 2;
            if (cards[cur_card] >= 2 && cards[cur_card + 10] >= 1) {
                items[cur_item].j = 2;
                cards[cur_card] -= 2;
                --cards[cur_card + 10];
                find = 1;
                printf("小小绞------------------------------------> %d", cur_card + 1);
                printf(" %d", cur_card + 1);
                printf(" %d\n", cur_card + 11);

                continue;
            }
        }

        // 大大小绞
        if (items[cur_item].i == 2) {
            items[cur_item].i = 3;
            if (cards[cur_card + 10] >= 2) {
                items[cur_item].j = 3;
                cards[cur_card + 10] -= 2;
                --cards[cur_card];
                find = 1;
                printf("大大绞------------------------------------> %d", cur_card + 11);
                printf(" %d", cur_card + 11);
                printf(" %d\n", cur_card + 1);
                continue;
            }
        }

        // 2 7 10
        if (items[cur_item].i == 3) {
            items[cur_item].i = 4;
            if (cur_card == 1 && cards[6] > 0 && cards[9] > 0) {
                items[cur_item].j = 4;
                items[cur_item].huxi = 3;

                find = 1;
                --cards[1];
                --cards[6];
                --cards[9];
                printf("2/7/10------------------------------------> %d,", 2);
                printf(" %d,", 7);
                printf(" %d\n", 10);

                continue;
            }
        }


        //小坎
        if (items[cur_item].i == 4) {
            items[cur_item].i = 5;
            if (cards[cur_card] == 3) {
                items[cur_item].j = 5;
                items[cur_item].huxi = 6;
                find = 1;
                cards[cur_card] -= 3;
                printf("小坎------------------------------------> %d,%d,%d", cur_card + 1, cur_card + 1, cur_card + 1);
                printf(" %d,", cur_card + 1);
                printf(" %d\n", cur_card + 1);
                continue;
            }
        }


        huisu:    // 回溯

        if (cur_item < 0) goto finish;

        printf("当前算法:------------------------------------>第%d种\n",items[cur_item].j);

        if (items[cur_item].i == 0 || (items[cur_item].i == 5 && items[cur_item].j != 5)) {
            memset(&items[cur_item], 0, sizeof(struct Item));
            if (cur_item == 0) {
                printf("<------------------------------------ 遍历结束\n");
                goto finish;
            }


            --cur_item;
            printf("\n------------------------------------ 遍历 card %d", items[cur_item].card);
            printf("------------------------------------ cur_item %d\n", cur_item);
            goto huisu;
        }

        cur_card = items[cur_item].card;
        if (items[cur_item].i > 0 && items[cur_item].i == items[cur_item].j) {
            items[cur_item].huxi = 0;
            if (items[cur_item].j == 1) {
                printf("<------------------------------------回溯顺子 %d ", cur_card + 1);
                printf(" %d", cur_card + 2);
                printf(" %d \n", cur_card + 3);
                ++cards[cur_card];
                ++cards[cur_card + 1];
                ++cards[cur_card + 2];
            } else if (items[cur_item].j == 2) {
                printf("<------------------------------------回溯小小大绞 %d ", cur_card + 1);
                printf(" %d ", cur_card + 1);
                printf(" %d \n", cur_card + 11);
                cards[cur_card] += 2;
                ++cards[cur_card + 10];
            } else if (items[cur_item].j == 3) {
                printf("<------------------------------------回溯大大小绞 %d ", cur_card + 11);
                printf(" %d ", cur_card + 11);
                printf(" %d \n", cur_card + 1);
                cards[cur_card + 10] += 2;
                ++cards[cur_card];
            } else if (items[cur_item].j == 4) {
                printf("<------------------------------------回溯2,7,10 \n ");
                ++cards[1];
                ++cards[6];
                ++cards[9];
            } else if (items[cur_item].j == 5) {
                cards[cur_card] += 3;
                printf("<------------------------------------回溯坎 %d\n ", cur_card + 1);

                memset(&items[cur_item], 0, sizeof(struct Item));
                if (cur_item == 0) goto finish;
                --cur_item;
                goto huisu;
            }
        }
    }
    finish:

    return max_huxi;
}

int get_shun_huxi_da(char *cards) {
    printf("11,12,13的张数------------------------------------> %d,%d,%d\n", cards[10], cards[11], cards[12]);
//    if (cards[10] > cards[11] || cards[10] > cards[12]) return -1;
    int min_123 = 0;
    if (cards[10] > cards[11]) {
        if (cards[11] > cards[12]) {
            min_123 = cards[12];
        } else {
            min_123 = cards[11];
        }
    } else {
        if (cards[10] > cards[12]) {
            min_123 = cards[12];
        } else {
            min_123 = cards[10];
        }
    }
    int sum = 0;
    for (int i = 10; i < 20; ++i) {
        sum += cards[i];
    }
    if (sum == 0) {
        return 0;
    }
    // 只需要拆2 7 10 和顺子
    char tmp_cards[10];
    memcpy(tmp_cards, &cards[10], 10);
//  int n_123 = tmp_cards[0];
    int n_123 = min_123;
    tmp_cards[0] -= n_123;
    tmp_cards[1] -= n_123;
    tmp_cards[2] -= n_123;

    int max_huxi = -1;

    for (int i = 0; i < 5; ++i) {
        memcpy(tmp_cards, &cards[10], 10);
        tmp_cards[0] -= n_123;
        tmp_cards[1] -= n_123;
        tmp_cards[2] -= n_123;
        if (tmp_cards[1] < i || tmp_cards[6] < i || tmp_cards[9] < i) {
            break;
        }
        printf("大123对数------------------------------------> %d\n", n_123);
        int huxi = get_shun_huxi_da_without_2_7_10(tmp_cards, i);
        if (huxi < 0) continue;
        if (huxi + n_123 * 6 > max_huxi) max_huxi = huxi + n_123 * 6;
    }
    int n_threes = 0;
    for (int i = 0; i < 10; ++i) {
        memcpy(tmp_cards, &cards[10], 10);
        if (tmp_cards[i] == 3) {
            printf("大坎------------------------------------>%d %d %d\n", i + 1 + 10, i + 1 + 10, i + 1 + 10);
            n_threes++;
        }
    }
    if (n_threes > 0) {
        if (max_huxi == -1) {
            max_huxi = 0;
        }
    }
    max_huxi = max_huxi + n_threes * 9;
    return max_huxi;
}

int get_shun_huxi_da_without_2_7_10(char *cards, int num) {
    char tmp_cards[10];
    memcpy(tmp_cards, cards, 10);
    tmp_cards[1] -= num;
    tmp_cards[6] -= num;
    tmp_cards[9] -= num;
    for (int i = 0; i < 10; ++i) {
        int n = tmp_cards[i];
        if (n == 0) continue;
        if (i + 2 >= 10) return -1;
        if (tmp_cards[i + 1] < n || tmp_cards[i + 2] < tmp_cards[i + 1]) return -1;
        tmp_cards[i + 1] -= n;
        tmp_cards[i + 2] -= n;
        printf("大顺子  ------------------------------------> %d", i + 1 + 10);
        printf(" %d", i + 2 + 10);
        printf(" %d\n", i + 3 + 10);
    }
    printf("大2710对数------------------------------------> %d\n", num);
    return num * 6;
}
