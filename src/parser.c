#include "../include/parser.h"

void parse_possible_locations(char **locations, char **locations_cords,
                              size_t possibilities) {

  FILE *fd;
  char buff[SUPER_MAX_LEN];
  char data_json[DUPER_MAX_LEN];

  struct json_object *parsed_json;
  struct json_object *locations_json;

  size_t number_locations;

  fd = fopen("./ressources/locations.json", "r");

  if (fd == NULL) {
    perror("Error while reading ./ressources/locations.json\n");
    return;
  }

  while ((fgets(buff, SUPER_MAX_LEN, fd))) {
    strncat(data_json, buff, sizeof(data_json) - strlen(data_json) - 1);
  }

  fclose(fd);

  parsed_json = json_tokener_parse(data_json);

  json_object_object_get_ex(parsed_json, "features", &locations_json);

  number_locations = json_object_array_length(locations_json);

  for (size_t i = 0; i < number_locations; i++) {
    if (i >= possibilities) {
      break;
    }
    struct json_object *location_details_json;
    struct json_object *location_details_array_json;
    struct json_object *location_name;
    struct json_object *location_cords_json;

    location_details_json = json_object_array_get_idx(locations_json, i);

    json_object_object_get_ex(location_details_json, "properties",
                              &location_details_array_json);

    json_object_object_get_ex(location_details_array_json, "name",
                              &location_name);

    json_object_object_get_ex(location_details_array_json, "extent",
                              &location_cords_json);

    strncpy(locations[i], json_object_get_string(location_name),
            SUPER_SAFE_SIZE - strlen(locations[i]) - 1);

    if (location_cords_json == NULL) {
      strncpy(locations_cords[i], "NAN\0", 4);
      continue;
    }

    strncpy(locations_cords[i], json_object_get_string(location_cords_json),
            SUPER_SAFE_SIZE - strlen(locations_cords[i]) - 1);
  }
}
