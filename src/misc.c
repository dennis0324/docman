#include "misc.h"
#include <linux/limits.h>

void path_join(char *dest, ...) {
  char buf[PATH_MAX];
  char *tmp = NULL;
  int argc = 0;

  char *file_stack[256];

  va_list ap;
  va_start(ap, dest);
  while ((tmp = va_arg(ap, char *)) != NULL) {
    if (tmp[0] == '/') {
      if (argc)
        tmp++;
      else {
        dest[0] = '/';
        dest++;
      }
    }

    // not strtok with first slash
    if (strchr(tmp + 1, '/') != NULL) {
      strcpy(buf, tmp);
      char *tmp_tok = strtok(buf + 1, "/");
      while (tmp_tok != NULL) {
        file_stack[argc] = calloc(256, sizeof(char));
        strcpy(file_stack[argc++], tmp_tok);
        tmp_tok = strtok(NULL, "/");
      }
      continue;
    }

    if (!strcmp(tmp, "."))
      continue;

    if (!strcmp(tmp, "..")) {
      if (argc > 0) {
        free(file_stack[argc--]);
      }
      continue;
    }

    file_stack[argc] = calloc(256, sizeof(char));
    strcpy(file_stack[argc++], tmp);
  }
  va_end(ap);

  memset(buf, 0, sizeof(buf)); // reseting buffer to empty
  // add slash('/') between elements in array
  for (int i = 0; i < argc; i++) {
    if (i)
      buf[strlen(buf)] = '/';
    memcpy(buf + strlen(buf), file_stack[i], sizeof(char) * strlen(file_stack[i]));
    free(file_stack[i]);
  }

  strcpy(dest, buf);
}

void path_name(char *a) {
  if (a[0] == '.') {
    strncpy(a, a + 1, strlen(a) - 1);
    a[strlen(a) - 1] = 0;
  }
}

int path_create(char *file_path, mode_t mode) {
  for (char *p = strchr(file_path + 1, '/'); p; p = strchr(p + 1, '/')) {
    *p = '\0';
    if (mkdir(file_path, mode) == -1) {
      if (errno != EEXIST) {
        *p = '/';
        return -1;
      }
    }
    *p = '/';
  }
  return 0;
}
