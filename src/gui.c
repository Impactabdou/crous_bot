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

void generate_email(char *email, char *email_cmd) {

  const char *email_header =
      "echo \"Un logement est disponible. Viens vite checker ça mon reuf :). "
      "site utile : https://trouverunlogement.lescrous.fr/\" "
      "| mailx -s \"Logement crous\" ";

  strncat(email_cmd, email_header, strlen(email_header));

  strncat(email_cmd, email, strlen(email));
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
  const char *prefix = "=================================================\0";
  char *temp_str = calloc(SUPER_MAX_LEN, sizeof(char));

  strncpy(temp_str, prefix, strlen(prefix));
  strncat(temp_str, msg_str, strlen(msg_str));

  for (size_t i = strlen(temp_str); i < msg_size; i++) {
    temp_str[i] = filler;
  }

  temp_str[strlen(temp_str)] = '\0';
  printf("%s\n", temp_str);

  free(temp_str);
  temp_str = NULL;
}
