#include <math.h>
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

    if (strlen(buffer[0].team_a) > 0) {
        char file_name[30];
        _sort_buffer(buffer, buffer_length, sort_option);
        sprintf(file_name, "./data/temp_%d.txt", fileCount);
        FILE *last_output = fopen(file_name, "a");

        for (int i = 0; i < pagination; i++) {
            if (strlen(buffer[i].team_a) > 0) {
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
        }

        fclose(last_output);
    }

    fclose(file);
}

void set_buffer(struct file *file, int K) {
    if (file->f == NULL)
        return;

    file->position = 0;
    file->MAX_POSITION = 0;

    for (int i = 0; i < K; i++) {
        if (!feof(file->f)) {
            fscanf(
                file->f,
                "%s\t%s\t%d\t%d\t%s\t%d",
                file->buffer[file->MAX_POSITION].team_a,
                file->buffer[file->MAX_POSITION].team_b,
                &file->buffer[file->MAX_POSITION].score_a,
                &file->buffer[file->MAX_POSITION].score_b,
                file->buffer[file->MAX_POSITION].match_date,
                &file->buffer[file->MAX_POSITION].money_raised
            );

            file->MAX_POSITION++;
        } else {
            fclose(file->f);
            file->f = NULL;
            break;
        }
    }
}

int search_lowest(struct file *file, int file_qty, int K, struct lineContent *lowest, int sort_option) {
    int index = -1;
    
    for (int i = 0; i < file_qty; i++) {
        if (file[i].position < file[i].MAX_POSITION) {
        // if (file[i].position == file[i].MAX_POSITION || file[i].position < file[i].MAX_POSITION) {

            if (index == -1) {
                index = i;
            } else {
                switch (sort_option) {
                    case 1:
                        if (strcmp(file[i].buffer[file[i].position].team_a, file[index].buffer[file[index].position].team_a))
                            index = i;
                        break;
                    case 2:
                        if (strcmp(file[i].buffer[file[i].position].team_b, file[index].buffer[file[index].position].team_b))
                            index = i;
                        break;
                    case 3:
                        if (file[i].buffer[file[i].position].score_a < file[index].buffer[file[index].position].score_a)
                            index = i;
                        break;
                    case 4:
                        if (file[i].buffer[file[i].position].score_b < file[index].buffer[file[index].position].score_b)
                            index = i;
                        break;
                    case 5:
                        if (strcmp(file[i].buffer[file[i].position].match_date, file[index].buffer[file[index].position].match_date))
                            index = i;
                        break;
                    case 6:
                        if (file[i].buffer[file[i].position].money_raised < file[index].buffer[file[index].position].money_raised)
                            index = i;
                        break;
                }
            }
        }
    }

    if (index != -1) {
        *lowest = file[index].buffer[file[index].position];

        file[index].position++;

        if (file[index].position == file[index].MAX_POSITION) {
            set_buffer(&file[index], K);
        }

        return 1;
    }

    return 0;
}

void save_file(char *name, struct lineContent *V, int length) {
    FILE *file = fopen(name, "a");

    for (int i = 0; i < length - 1; i++) {
        fprintf(
            file,
            "%s\t%s\t%d\t%d\t%s\t%d\n",
            V[i].team_a,
            V[i].team_b,
            V[i].score_a,
            V[i].score_b,
            V[i].match_date,
            V[i].money_raised
        );
    }

    fclose(file);
}

void merge(char *name, int file_qty, int K, int sort_option) {
    char temp_filename[30];
    struct lineContent *buffer = (struct lineContent *) malloc(K * sizeof(struct lineContent));

    struct file *file = (struct file*) malloc(file_qty * sizeof(struct file));

    for (int i = 0; i < file_qty; i++) {
        sprintf(temp_filename, "./data/temp_%d.txt", i);
        file[i].f = fopen(temp_filename, "r");
        file[i].MAX_POSITION = 0;
        file[i].position = 0;
        file[i].buffer = (struct lineContent *) malloc(K * sizeof(struct lineContent));
        set_buffer(&file[i], K);
    }

    struct lineContent lowest;
    int buffer_qty = 0;

    while (search_lowest(file, file_qty, K, &lowest, sort_option) == 1) {
        buffer[buffer_qty] = lowest;
        buffer_qty++;

        if (buffer_qty == K) {
            save_file(name, buffer, K);
            buffer_qty = 0;
        }
    }

    if (buffer_qty != 0) {
        save_file(name, buffer, buffer_qty);
    }

    for (int i = 0; i < file_qty; i++) {
        free(file[i].buffer);
    }

    free(file);
    free(buffer);
}

void external_merge_sort(char *name, int pagination, int sort_option) {
    char new[30];
    int file_qty = 7;
    int K = pagination / ceil(file_qty + 1);

    merge(name, file_qty, K, sort_option);

    for (int i = 0; i < file_qty; i++) {
        sprintf(new, "./data/temp_%d.txt", i);
        // remove(new);
    }
}





