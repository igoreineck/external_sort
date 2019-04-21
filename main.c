#include <stdio.h>
#include "extract_sort.h"

int main(void) {
    int PAGINATION_SIZE = 0;
    int OPTION = 0;

    printf("Which size of your pagination? ");
    scanf("%d", &PAGINATION_SIZE);

    printf("Which column you want to ordenate?\n");
    printf("1 -> Team A\n");
    printf("2 -> Team B\n");
    printf("3 -> Score A\n");
    printf("4 -> Score B\n");
    printf("5 -> Match Date\n");
    printf("6 -> Money raised\n");

    scanf("%d", &OPTION);

    read_extract_sort_data("backup_treated_data.txt", PAGINATION_SIZE, OPTION);

    printf("File sorted sucessfully!");

    return EXIT_SUCCESS;
}