#include "extract_sort.h"
#include "comparison.h"

void _sort_buffer(struct lineContent *buffer, size_t buffer_length, int sort_option) {
    switch (sort_option) {
        case 1:
            qsort(buffer, buffer_length, sizeof(struct lineContent), compare_team_a);
            break;
        case 2:
            qsort(buffer, buffer_length, sizeof(struct lineContent), compare_team_b);
            break;
        case 3:
            qsort(buffer, buffer_length, sizeof(struct lineContent), compare_score_a);
            break;
        case 4:
            qsort(buffer, buffer_length, sizeof(struct lineContent), compare_score_b);
            break;
        case 5:
            qsort(buffer, buffer_length, sizeof(struct lineContent), compare_match_date);
            break;
        case 6:
            qsort(buffer, buffer_length, sizeof(struct lineContent), compare_money_raised);
            break;
        default:
            qsort(buffer, buffer_length, sizeof(struct lineContent), compare_team_a);
            break;
    }
}

void read_extract_sort_data(char *name, int pagination, int sort_option) {
    char mode[] = "r";
    FILE *file = fopen(name, mode);

    int counter = 0;
    int fileCount = 0;
    struct lineContent buffer[pagination];
    size_t buffer_length = sizeof(buffer) / sizeof(struct lineContent);

    while (!feof(file)) {
        if (counter == pagination) {
            char output_file_name[30];

            _sort_buffer(buffer, buffer_length, sort_option);
            sprintf(output_file_name, "./data/temp_%d.txt", fileCount);
            FILE *output = fopen(output_file_name, "a");
            
            for (int i = 0; i < pagination; i++) {
                fprintf(
                    output, 
                    "%s\t%s\t%d\t%d\t%s\t%d\n",
                    buffer[i].team_a,
                    buffer[i].team_b,
                    buffer[i].score_a,
                    buffer[i].score_b,
                    buffer[i].match_date,
                    buffer[i].money_raised
                );
            }

            counter = 0;
            fileCount++;
            fclose(output);
            memset(buffer, 0, sizeof(buffer));
            memset(output_file_name, 0, sizeof(output_file_name));
        }

        struct lineContent* line = (struct lineContent*) malloc(sizeof(struct lineContent));

        fscanf(
            file, 
            "%s\t%s\t%d\t%d\t%s\t%d\n",
            line->team_a, 
            line->team_b,
            &line->score_a, 
            &line->score_b,
            line->match_date,
            &line->money_raised
        );

        strcpy(buffer[counter].team_a, line->team_a);
        strcpy(buffer[counter].team_b, line->team_b);
        buffer[counter].score_a = line->score_a;
        buffer[counter].score_b = line->score_b;
        strcpy(buffer[counter].match_date, line->match_date);
        buffer[counter].money_raised = line->money_raised;

        free(line);
        counter++;
    }

    // FIX: the parser i'll sort data with NULL values
    if (strcmp(buffer[0].team_a, "") > 0) {
        char file_name[30];
        _sort_buffer(buffer, buffer_length, sort_option);
        sprintf(file_name, "./data/temp_%d.txt", fileCount);
        FILE *last_output = fopen(file_name, "a");

        for (int i = 0; i < pagination; i++) {
            fprintf(
                last_output,
                "%s\t%s\t%d\t%d\t%s\t%d\n",
                buffer[i].team_a,
                buffer[i].team_b,
                buffer[i].score_a,
                buffer[i].score_b,
                buffer[i].match_date,
                buffer[i].money_raised
            );
        }

        fclose(last_output);
    }

    fclose(file);
}