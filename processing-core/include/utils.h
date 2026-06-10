#ifndef DATAFLOW_UTILS_H
#define DATAFLOW_UTILS_H

#include <stddef.h>

#define MAX_RECORD_LEN    256
#define MAX_FIELD_LEN     128
#define MAX_RECORDS       1024
#define BUFFER_SIZE       512
#define MAX_PATH_LEN      260

/* Record structure for in-memory dataset */
typedef struct {
    int  id;
    char name[MAX_FIELD_LEN];
    char owner[MAX_FIELD_LEN];
    int  row_count;
    char description[MAX_RECORD_LEN];
} DataRecord;

/* Linked-list node for query result caching */
typedef struct CacheNode {
    char              *key;
    char              *value;
    struct CacheNode  *next;
} CacheNode;

/* ---- Function prototypes ---- */

/* Record parsing and management */
int   parse_csv_line(const char *line, DataRecord *record);
int   load_dataset(const char *filepath, DataRecord *records, int max_records);
char *format_record(const DataRecord *record);
void  print_record(const DataRecord *record);

/* Query and search */
int search_records(const DataRecord *records, int count,
                   const char *search_term, DataRecord *results, int max_results);

/* Cache management */
CacheNode *cache_create(const char *key, const char *value);
CacheNode *cache_lookup(CacheNode *head, const char *key);
void       cache_insert(CacheNode **head, const char *key, const char *value);
void       cache_free(CacheNode *head);
void       cache_remove(CacheNode **head, const char *key);

/* File I/O */
int   export_records(const char *output_path, const DataRecord *records, int count);
char *read_file_contents(const char *filepath);

/* String / data utilities */
void  copy_field(char *dest, const char *src);
int   safe_atoi(const char *str);
char *concat_strings(const char *a, const char *b);
void  log_message(const char *format, ...);

#endif /* DATAFLOW_UTILS_H */
