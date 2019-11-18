#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  printf("Directory Statistics:\n");
  DIR * folder = opendir("./");
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
