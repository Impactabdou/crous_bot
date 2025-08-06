#ifndef GUI_H
#include "shared.h"

#define MAX_SIZE_STATEMENT 117
#define FILL_CHAR '='

char **init_array(size_t row, size_t col);
void free_array(char **locations, size_t size);
void print_array(char **array, size_t size);
void generate_email(char *email, char *email_cmd);
void startup_page();
void print_statement(const char *msg_str, char filler, size_t msg_size);

#endif // !GUI_H
