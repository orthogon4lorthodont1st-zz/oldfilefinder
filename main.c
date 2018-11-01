#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int name_filter(const struct dirent *);

struct Output {
  size_t size;
  char name[256];
};

int main() {
  struct dirent **namelist;
  struct stat fileStat;
  struct Output *optr;
  int n;

  // Stores he files in namelist
  n = scandir(".", &namelist, &name_filter, NULL);
  optr = malloc(n * sizeof(*optr));

  if (optr == NULL) {
    perror("malloc\n");
    return -1;
  }

  if (n < 0) {
    perror("scandir\n");
    return -1;
  };

  while (n--) {
    stat(namelist[n]->d_name, &fileStat);
    optr[n].size = fileStat.st_size;
    strcpy(optr[n].name, namelist[n]->d_name);

    printf("File: %c\t Size: %lld bytes\n", namelist[n]->d_name,
           fileStat.st_size);
    free(namelist[n]);
  }
  free(optr);
  free(namelist);

  return 0;
}

int name_filter(const struct dirent *entry) {
  if (entry == NULL) {
    perror("name_filter\n");
    return -1;
  }

  return strncmp(entry->d_name, ".", 1) != 0;
}
