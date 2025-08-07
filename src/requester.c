#include "../include/requester.h"

void get_possible_localisations_request(char *query) {
  const char *start_curl_command = "curl -G \"https://photon.komoot.io/api\" "
                                   "--data-urlencode \"q=";
  const char *end_curl_command =
      "\" "
      "--data-urlencode \"limit=18\" "
      "--data-urlencode \"lang=fr\" "
      "--data-urlencode \"osm_tag=amenity:college\" "
      "--data-urlencode \"osm_tag=amenity:library\" "
      "--data-urlencode \"osm_tag=amenity:school\" "
      "--data-urlencode \"osm_tag=amenity:university\" "
      "--data-urlencode \"osm_tag=place:country\" "
      "--data-urlencode \"osm_tag=place:region\" "
      "--data-urlencode \"osm_tag=place:state\" "
      "--data-urlencode \"osm_tag=place:city\" "
      "--data-urlencode \"osm_tag=place:town\" "
      "--data-urlencode \"osm_tag=place:village\" "
      "--data-urlencode \"osm_tag=place:house\" "
      "--data-urlencode \"osm_tag=landuse:residential\""
      "> ./ressources/locations.json";

  char cmd_str[SUPER_MAX_LEN] = {0};

  unsigned int safe_size = sizeof(cmd_str) - strlen(cmd_str) - 1;

  strncat(cmd_str, start_curl_command, safe_size);
  safe_size = sizeof(cmd_str) - strlen(cmd_str) - 1;
  strncat(cmd_str, query, safe_size);
  safe_size = sizeof(cmd_str) - strlen(cmd_str) - 1;
  strncat(cmd_str, end_curl_command, safe_size);
  system(cmd_str);
}

void get_availability_request(char *availability_request,
                              char location_cords_str[4][MAX_LEN],
                              size_t possibilities_size) {
  char body_req[SUPER_MAX_LEN];

  const char *start_req =
      "curl -X POST 'https://trouverunlogement.lescrous.fr/api/fr/search/41'   "
      "-H 'Content-Type: application/json'   --data-raw '{\n"
      "\"idTool\":41,\n"
      "\"need_aggregation\":true,\n"
      "\"page\":1,\n"
      "\"pageSize\":24,\n"
      "\"sector\":null,\n"
      "\"occupationModes\":[],\n"
      "\"location\":[\n";

  snprintf(body_req, SUPER_MAX_LEN - 1,
           "{\"lon\":%s,\"lat\":%s},{\"lon\":%s,\"lat\":%s}],\n",
           location_cords_str[0], location_cords_str[1], location_cords_str[2],
           location_cords_str[3]);

  const char *end_req = "\"residence\":null,\n"
                        "\"precision\":6,\n"
                        "\"equipment\":[],\n"
                        "\"adaptedPmr\":false,\n"
                        "\"toolMechanism\":\"residual\"\n"
                        "}' > ./ressources/location_res.json";
  snprintf(availability_request, possibilities_size - 1, "%s%s%s", start_req,
           body_req, end_req);
}

void extract_cords(char *location_cords, char location_str[4][MAX_LEN]) {

  if (strncmp(location_cords, "NAN", 4) == 0) {
    printf("Location not loaded\n");
    return;
  }

  size_t i = 2;
  size_t j = 0;
  size_t turn = 0;

  while (i < strlen(location_cords)) {
    if (turn > 4 || j > SUPER_SAFE_SIZE || i > SUPER_SAFE_SIZE) {
      break;
    }
    if (location_cords[i] != '[' && location_cords[i] != ' ' &&
        location_cords[i] != ']' && location_cords[i] != ',') {
      location_str[turn][j++] = location_cords[i];
    } else if (location_cords[i] != ',') {
      location_str[turn][j] = '\0';
      turn++;
      j = 0;
    }
    i++;
  }
}
