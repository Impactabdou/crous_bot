#ifndef PARSER_H
#define PARSER_H
#include "shared.h"
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <json-c/json_types.h>
#include <unistd.h>

#define DUPER_MAX_LEN 80000

void parse_possible_locations(char **locations, char **locations_cords,
                              size_t possibilities);

#endif // !PARSER_H
