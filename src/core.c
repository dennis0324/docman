#include "core.h"
#include "misc.h"
#include <linux/limits.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void add_dotfiles(char *relative_path) {
  char dest_path[PATH_MAX] = {0};
  char temp[255] = {0};
  char *home_path = getpwuid(getuid())->pw_dir;

  if (access(relative_path, F_OK) != 0) {
    fprintf(stderr, "Can not find file: %s", relative_path);
    return;
  }

  realpath(relative_path, dest_path);

  // path_from_home
  int start = strlen(home_path);
  int end = strlen(dest_path);
  strncpy(dest_path, dest_path + start, end - start);
  dest_path[end - start] = '\0';

  // TODO: need to make `/` compatible with window and unix
  int offset = 0;
  char *find_pos;
  while ((find_pos = strstr(dest_path + ++offset, "/")) != NULL) {
    offset = find_pos - dest_path;
  }

  strcpy(temp, dest_path + offset);
  path_join(dest_path, home_path, ".dotfiles", temp, dest_path, NULL);

  printf("%s", dest_path);
  // path_create(dest_path, 0755);
  // copy
}
