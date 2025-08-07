#include "../include/gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **init_array(size_t row, size_t col) {
  char **array = calloc(row, sizeof(char *));
  for (size_t i = 0; i < row; i++) {
    array[i] = malloc(sizeof(char) * col);
  }
  return array;
}

void free_array(char **locations, size_t size) {

  for (size_t i = 0; i < size; i++) {
    free(locations[i]);
    locations[i] = NULL;
  }
  free(locations);
  locations = NULL;
}
void print_array(char **array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    printf("%ld=> %s\n", i + 1, array[i]);
  }
}

void generate_url(char *url, char location_str[4][MAX_LEN]) {
  size_t offset = 0;
  for (size_t i = 0; i < 4; i++) {
    size_t location_str_size = strlen(location_str[i]);
    strncat(url, location_str[i], location_str_size);
    if (i == 3) {
      break;
    }
    url[strlen(url) - 1] = '_';
    offset += location_str_size + 1;
  }
}

void generate_email(char *email_cmd, char *email,
                    char location_str[4][MAX_LEN]) {

  char url[SUPER_MAX_LEN] = {0};

  const char *echo_cmd =
      "echo \"Un logement est disponible. Viens vite checker ça mon reuf "
      ":). "
      "site utile : "
      "https://trouverunlogement.lescrous.fr/tools/41/search?bounds=\0";

  const char *mailx_cmd = " | mailx -s \"Logement crous\" \0";

  generate_url(url, location_str);

  size_t email_cmd_size = 0;

  strncat(email_cmd, echo_cmd, strlen(echo_cmd));
  strncat(email_cmd, url, strlen(url));

  email_cmd_size += strlen(url) + strlen(echo_cmd);

  email_cmd[email_cmd_size] = '"';

  strncat(email_cmd, mailx_cmd, strlen(mailx_cmd));

  strncat(email_cmd, email, strlen(email));

  email_cmd_size += 1 + strlen(email) + strlen(mailx_cmd);

  email_cmd[email_cmd_size] = '\0';
}

void startup_page() {
  system("clear");
  printf(" ░▒▓██████▓▒░░▒▓███████▓▒░ "
         "░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░░▒▓███████▓▒░▒▓█▓▒░▒▓████████▓▒░▒▓█▓▒░▒▓███"
         "█████▓▒░▒▓███████▓▒░  \n");
  printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      "
         "░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n");
  printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      "
         "░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n");
  printf("░▒▓█▓▒░      "
         "░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░▒▓██████▓▒"
         "░ ░▒▓█▓▒░▒▓██████▓▒░ ░▒▓███████▓▒░  \n");
  printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      "
         "░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n");
  printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      "
         "░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n");
  printf(" ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ "
         "░▒▓██████▓▒░░▒▓███████▓▒░░▒▓█▓▒░▒▓█▓▒░      "
         "░▒▓█▓▒░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░ \n");

  print_statement("", FILL_CHAR, MAX_SIZE_STATEMENT);
  printf("AUTHOR @IMPACTABDOU\n");
  printf("HOW DOES IT WORK : \n\t1-chose a city from those proposed to "
         "you\n\t2-Let the magic happen\n\t3-When ever there is an "
         "availability an email will be sent to your mailbox\n");
  printf("PRESS ENTER TO START");
  getc(stdin);
  system("clear");
}

void print_statement(const char *msg_str, char filler, size_t msg_size) {
  const char *prefix = "=================================================";
  char *temp_str = calloc(SUPER_MAX_LEN, sizeof(char));
  size_t total_size = 0;
  strncpy(temp_str, prefix, strlen(prefix));
  strncat(temp_str, msg_str, strlen(msg_str));

  total_size += strlen(prefix) + strlen(msg_str);

  for (size_t i = strlen(temp_str); i < msg_size; i++) {
    temp_str[i] = filler;
    total_size++;
  }

  temp_str[total_size] = '\0';
  printf("%s\n", temp_str);

  free(temp_str);
  temp_str = NULL;
}
