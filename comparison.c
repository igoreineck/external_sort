#include "extract_sort.h"
#include "comparison.h"

int compare_team_a(const void *a, const void *b) {
    struct lineContent *field_a = (struct lineContent *)a;
    struct lineContent *field_b = (struct lineContent *)b;
    
    return strcmp(field_a->team_a, field_b->team_a);
}

int compare_team_b(const void *a, const void *b) {
    struct lineContent *field_a = (struct lineContent *)a;
    struct lineContent *field_b = (struct lineContent *)b;

    return strcmp(field_a->team_b, field_b->team_b);
}

int compare_score_a(const void *a, const void *b) {
    struct lineContent *field_a = (struct lineContent *)a;
    struct lineContent *field_b = (struct lineContent *)b;

    return field_a->score_a - field_b->score_a;
}

int compare_score_b(const void *a, const void *b) {
    struct lineContent *field_a = (struct lineContent *)a;
    struct lineContent *field_b = (struct lineContent *)b;

    return field_a->score_b - field_b->score_b;
}

int compare_match_date(const void *a, const void *b) {
    struct lineContent *field_a = (struct lineContent *)a;
    struct lineContent *field_b = (struct lineContent *)b;

    return strcmp(field_a->match_date, field_b->match_date);
}

int compare_money_raised(const void *a, const void *b) {
    struct lineContent *field_a = (struct lineContent *)a;
    struct lineContent *field_b = (struct lineContent *)b;

    return field_a->money_raised - field_b->money_raised;
}