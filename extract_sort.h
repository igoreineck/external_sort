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

struct file {
    FILE *f;
    int position;
    int MAX_POSITION;
    struct lineContent *buffer;
};

void _sort_buffer(struct lineContent *buffer, size_t buffer_length, int sort_option);
void read_extract_sort_data(char *name, int pagination, int sort_option);
void set_buffer(struct file *file, int K);
int search_lowest(struct file *file, int file_qty, int K, struct lineContent *lowest, int sort_option);
void save_file(char *name, struct lineContent *V, int length);
void merge(char *name, int file_qty, int K, int sort_option);
void external_merge_sort(char *name, int pagination, int sort_option);