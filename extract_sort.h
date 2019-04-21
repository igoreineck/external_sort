#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lineContent {
    char team_a[50];
    char team_b[50];
    int score_a;
    int score_b;
    char match_date[10];
    int money_raised;
};

void _sort_buffer(struct lineContent *buffer, size_t buffer_length, int sort_option);
void read_extract_sort_data(char *name, int pagination, int sort_option);