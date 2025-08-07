#ifndef GUI_H
#include "shared.h"

#define MAX_SIZE_STATEMENT 117
#define FILL_CHAR '='

char **init_array(size_t row, size_t col);
void free_array(char **locations, size_t size);
void print_array(char **array, size_t size);
void startup_page();
void print_statement(const char *msg_str, char filler, size_t msg_size);
void generate_email(char *email_cmd, char *email,
                    char location_str[4][MAX_LEN]);
#endif // !GUI_H
