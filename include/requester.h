#ifndef REQ_H
#define REQ_H
#include "shared.h"
#include <stdlib.h>

#define MAX_LEN 20

void get_possible_localisations_request(char *query);
void get_availability_request(char *location_cords, char *availability_request,
                              size_t possibilities_size);

void extract_cords(char *location_cords, char location_str[4][MAX_LEN]);

#endif
