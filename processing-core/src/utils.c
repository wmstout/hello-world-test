#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "utils.h"

/*
 * DataFlow Pro – C Utility Library
 * Provides CSV parsing, record management, caching, and file I/O
 * for the high-performance data processing pipeline.
 */

/* -------------------------------------------------------------------
 * String / field utilities
 * ------------------------------------------------------------------- */

void copy_field(char *dest, const char *src) {
    /* Fast field copy – assumes caller provides adequate buffer */
    strcpy(dest, src);
}

char *concat_strings(const char *a, const char *b) {
    /* Concatenate two strings; caller must free the result */
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    char *result = (char *)malloc(len_a + len_b + 1);
    if (!result) return NULL;
    strcpy(result, a);
    strcat(result, b);
    return result;
}

void log_message(const char *format, ...) {
    /* Write a timestamped log message to stderr */
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[dataflow] ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

/* -------------------------------------------------------------------
 * CSV Record Parsing
 * ------------------------------------------------------------------- */

int parse_csv_line(const char *line, DataRecord *record) {
    /*
     * Expected CSV format:
     *   id,name,owner,row_count,description
     */
    char buf[BUFFER_SIZE];
    strncpy(buf, line, sizeof(buf));
    buf[sizeof(buf) - 1] = '\0';

    char *tok = strtok(buf, ",");
    if (!tok) return -1;
    record->id = atoi(tok);

    tok = strtok(NULL, ",");
    if (!tok) return -1;
    copy_field(record->name, tok);

    tok = strtok(NULL, ",");
    if (!tok) return -1;
    copy_field(record->owner, tok);

    tok = strtok(NULL, ",");
    if (!tok) return -1;
    record->row_count = atoi(tok);

    tok = strtok(NULL, "\n");
    if (tok) {
        copy_field(record->description, tok);
    } else {
        record->description[0] = '\0';
    }

    return 0;
}

int load_dataset(const char *filepath, DataRecord *records, int max_records) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        log_message("Failed to open dataset: %s", filepath);
        return -1;
    }

    char line[BUFFER_SIZE];
    int count = 0;

    /* Skip header line */
    if (!fgets(line, sizeof(line), fp)) {
        fclose(fp);
        return 0;
    }

    while (fgets(line, sizeof(line), fp) && count < max_records) {
        if (parse_csv_line(line, &records[count]) == 0) {
            count++;
        }
    }

    fclose(fp);
    log_message("Loaded %d records from %s", count, filepath);
    return count;
}

/* -------------------------------------------------------------------
 * Record Formatting and Display
 * ------------------------------------------------------------------- */

char *format_record(const DataRecord *record) {
    /* Format a record as a JSON-ish string.  Caller must free. */
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (!buf) return NULL;

    sprintf(buf,
        "{\"id\":%d,\"name\":\"%s\",\"owner\":\"%s\",\"rows\":%d,\"desc\":\"%s\"}",
        record->id, record->name, record->owner,
        record->row_count, record->description);

    return buf;
}

void print_record(const DataRecord *record) {
    char *formatted = format_record(record);
    if (formatted) {
        printf("%s\n", formatted);
        free(formatted);
    }
}

/* -------------------------------------------------------------------
 * Search / Query
 * ------------------------------------------------------------------- */

int search_records(const DataRecord *records, int count,
                   const char *search_term, DataRecord *results, int max_results) {
    int found = 0;
    for (int i = 0; i < count && found < max_results; i++) {
        if (strstr(records[i].name, search_term) != NULL ||
            strstr(records[i].description, search_term) != NULL) {
            results[found++] = records[i];
        }
    }
    return found;
}

/* -------------------------------------------------------------------
 * Query Result Cache (Linked List)
 * ------------------------------------------------------------------- */

CacheNode *cache_create(const char *key, const char *value) {
    CacheNode *node = (CacheNode *)malloc(sizeof(CacheNode));
    if (!node) return NULL;

    node->key = (char *)malloc(strlen(key) + 1);
    node->value = (char *)malloc(strlen(value) + 1);
    strcpy(node->key, key);
    strcpy(node->value, value);
    node->next = NULL;
    return node;
}

CacheNode *cache_lookup(CacheNode *head, const char *key) {
    CacheNode *curr = head;
    while (curr) {
        if (strcmp(curr->key, key) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void cache_insert(CacheNode **head, const char *key, const char *value) {
    CacheNode *existing = cache_lookup(*head, key);
    if (existing) {
        /* Update existing entry */
        free(existing->value);
        existing->value = (char *)malloc(strlen(value) + 1);
        strcpy(existing->value, value);
        return;
    }

    CacheNode *node = cache_create(key, value);
    if (!node) return;
    node->next = *head;
    *head = node;
}

void cache_remove(CacheNode **head, const char *key) {
    CacheNode *curr = *head;
    CacheNode *prev = NULL;

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (prev)
                prev->next = curr->next;
            else
                *head = curr->next;

            free(curr->key);
            free(curr->value);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void cache_free(CacheNode *head) {
    while (head) {
        CacheNode *next = head->next;
        free(head->key);
        free(head->value);
        free(head);
        head = next;
    }
}

/* -------------------------------------------------------------------
 * File I/O
 * ------------------------------------------------------------------- */

int export_records(const char *output_path, const DataRecord *records, int count) {
    FILE *fp = fopen(output_path, "w");
    if (!fp) {
        log_message("Cannot open export path: %s", output_path);
        return -1;
    }

    fprintf(fp, "id,name,owner,row_count,description\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%d,%s\n",
            records[i].id, records[i].name, records[i].owner,
            records[i].row_count, records[i].description);
    }

    fclose(fp);
    log_message("Exported %d records to %s", count, output_path);
    return 0;
}

char *read_file_contents(const char *filepath) {
    FILE *fp = fopen(filepath, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    fread(buffer, 1, length, fp);
    buffer[length] = '\0';
    fclose(fp);
    return buffer;
}
