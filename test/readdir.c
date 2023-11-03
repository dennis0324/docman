#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct dirent *pDirent;
  DIR *pDir = opendir("/home/dennis/.dotfiles/test/");
  if (pDir == NULL)
    return 1;

  while ((pDirent = readdir(pDir)) != NULL) {
    printf("%s \n", pDirent->d_name);
  }

  return 0;
}
