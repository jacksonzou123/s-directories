#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
  DIR * folder;
  if (argc > 1) {
    folder = opendir(argv[1]);
    if (errno != 0) {
      printf("Error: %s\n",strerror(errno));
      return 0;
    }
  }
  else {
    //printf("%d\n", errno);
    folder = opendir("./");
  }
  printf("Directory Statistics:\n");
  int size = 0;
  struct dirent *file = readdir(folder);
  printf("Folders:\n");
  while (file && file->d_type == DT_DIR) {
    printf("  %s\n", file->d_name);
    size += 4096;
    file = readdir(folder); //get file from folder
  }
  printf("Files:\n");
  while (file) {
    struct stat stats;
    struct stat *p = &stats;
    int index = stat(file->d_name, p);
    size += p->st_size;
    printf("  %s\n", file->d_name);
    file = readdir(folder);
  }
  printf("Total Size: %d bytes\n", size);
  return 0;
}
