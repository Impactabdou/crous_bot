#include "../include/gui.h"
#include "../include/parser.h"
#include "../include/requester.h"
#define INTERVAL 30
#define SAFE_LIMIT 20000000
#define MAX_POSSIBLE_LOCATIONS 5

int main() {
  char **locations;
  char **locations_cords;

  startup_page();

  locations = init_array(MAX_POSSIBLE_LOCATIONS, SUPER_MAX_LEN);
  locations_cords = init_array(MAX_POSSIBLE_LOCATIONS, SUPER_MAX_LEN);

  /* Getting location propositions */

  char city[MAX_LEN] = {0};
  char email[MAX_LEN] = {0};

  printf("Enter city name : ");
  scanf(" %s", city);
  printf("Enter your email : ");
  scanf("%s", email);

  print_statement("REQUESTING ZONES", FILL_CHAR, MAX_SIZE_STATEMENT);
  get_possible_localisations_request(city);

  parse_possible_locations(locations, locations_cords, MAX_POSSIBLE_LOCATIONS);

  print_statement("AVAILABLE ZONES", FILL_CHAR, MAX_SIZE_STATEMENT);

  print_array(locations, MAX_POSSIBLE_LOCATIONS);

  /* selecting the wanted proposed loacation */

  char choice_idx_str[MAX_LEN];
  int choice_idx;

  char request[SUPER_MAX_LEN];

  do {
    printf("Chose one available zone (type [1-4]) :");
    scanf(" %s", choice_idx_str);
  } while ((choice_idx = atoi(choice_idx_str)) == 0 ||
           !(choice_idx > 0 && choice_idx <= 4));

  char *choice = locations_cords[choice_idx - 1];

  unsigned int number_of_req = 0;

  print_statement("BOT LUNCH OK", FILL_CHAR, MAX_SIZE_STATEMENT);

  while (number_of_req < SAFE_LIMIT) {

    printf("Req° %d\n", number_of_req++);

    get_availability_request(choice, request, SUPER_MAX_LEN);

    system(request);

    FILE *fd = fopen("./ressources/location_res.json", "r");

    if (fd == NULL) {
      perror("Error while reading file : \n");
      return 1;
    }

    char buff[SUPER_MAX_LEN] = {0};

    fseek(fd, 29, SEEK_SET);

    int i = 0;

    while ((buff[i++] = getc(fd)) != ',')
      ;

    buff[strlen(buff) - 1] = '\0';

    if (strncmp(buff, "SON", 3) == 0) {
      print_statement("BAD NEWS", FILL_CHAR, MAX_SIZE_STATEMENT);
      printf("This location is not handled :/\n");
      fclose(fd);
      break;
    } else {
      int number_of_dispo = atoi(buff);
      if (number_of_dispo > 0) {
        print_statement("GOOD NEWS", FILL_CHAR, MAX_SIZE_STATEMENT);
        printf("\n\n    _________H ,%%&%%,\n");
        printf("   /\\     _   \\%%&&%%%%\n");
        printf("  /  \\___/^\\___\\%%&%%%%&\n");
        printf("  |  | []   [] |%%\\Y&%%'\n");
        printf("  |  |   .-.   | ||  \n");
        printf("~~@._|@@_|||_@@|~||~~~~~~~~~~~~~\n");
        printf("     `\"\"\") )\"\"\"`\n\n");

        printf("There are : %s disponibilites\n", buff);

        char email_cmd[SUPER_MAX_LEN] = {0};

        generate_email(email, email_cmd);

        printf("Sending mail...\n");

        /*system(email_cmd);*/
        printf("Mail sent\n");
        return 0;
      } else {
        print_statement("", FILL_CHAR, MAX_SIZE_STATEMENT);
        printf("Still nothing...\n");
      }

      print_statement("", FILL_CHAR, MAX_SIZE_STATEMENT);
    }
    fclose(fd);
    sleep(INTERVAL);
  }
  free_array(locations, MAX_POSSIBLE_LOCATIONS);
  free_array(locations_cords, MAX_POSSIBLE_LOCATIONS);

  print_statement("DON'T FORGOT TO CHECK MY GITHUB ;)", FILL_CHAR,
                  MAX_SIZE_STATEMENT);
  return 0;
}
