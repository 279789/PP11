#include <jansson.h>
typedef struct JObject {
    const char *name;
    int age;
    const char *email;
    struct JObject *next;
} JObject;

JObject* parse_json(const char *filename);
void     print_list(JObject *head);
void     free_list(JObject *head);
void remove_by_age(JObject **head, int age);
