#include "make-dot.h"

int main(int argc, char **argv) {
  int c;

  int option_index = 0;
  while (1) {
    static struct option long_opts[] = {{"help", no_argument, 0, 'h'},
                                        {"set", required_argument, 0, 's'},
                                        {0, 0, 0, 0}};

    c = getopt_long(argc, argv, "hs:", long_opts, &option_index);

    if (c == -1)
      break;
    switch (c) {
    case 0:
      if (long_opts[option_index].flag != 0)
        break;
      printf("option %s", long_opts[option_index].name);
      if (optarg)
        printf(" with arg %s\n", optarg);
      printf("\n");
      break;

    case 's':
      printf("option -s with value %s \n", optarg);
      break;
    }
  }

  // this is for getting only one args without options
  if (argc - optind != 1) {
    fprintf(stderr, "args has more than two");
    return -1;
  }

  char releavtive_path[PATH_MAX];
  strcpy(releavtive_path, argv[optind]);

  add_dotfiles(releavtive_path);

  //
  // // get home directory
  // char *home_path = getpwuid(getuid())->pw_dir;
  //
  // int start = strlen(home_path);
  // int end = strlen(full_path);
  //
  // char *target_location = malloc(end - start);
  // strncpy(target_location, full_path + start, end - start);
  //
  // char *token = strtok(target_location, "/");

  // free(full_path);
  // while (token != NULL) {
  //   // check if folder or files have . in side
  //   char *find = strstr(token, ".");
  //   if (find != NULL) {
  //     int offset = find - token;
  //     printf("%s\n", token + offset + 1);
  //   }
  //   else {
  //     printf("%s\n", token);
  //   }
  //
  //   // if (find != NULL) {
  //   //   int offset = find - token;
  //   //   printf("%d\n", offset);
  //   // }
  //   // free(token_cpy);
  //   token = strtok(NULL, "/");
  // }
}
