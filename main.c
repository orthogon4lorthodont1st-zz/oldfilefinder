#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  struct dirent **namelist;
  struct stat fileStat;
  int n;

  n = scandir(".", &namelist, NULL, alphasort);

  if (n < 0) {
    perror("scandir");
    return 1;
  };

  while (n--) {
    stat(namelist[n]->d_name, &fileStat);
    printf("File: %s\t Size: %lld bytes\n", namelist[n]->d_name,
           fileStat.st_size);
    free(namelist[n]);
  }
  free(namelist);
}
