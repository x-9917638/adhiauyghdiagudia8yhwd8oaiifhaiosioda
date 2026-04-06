#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int eprintf(const char *fmt, ...);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    eprintf("Expected 1 argument, got %d\n", argc - 1);
    eprintf("pass -h for help\n");
    return 1;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    printf("Usage: counter [options] FILE\n"
           "Count the number of words and lines in a given FILE.\n\n"

           "Options:\n"
           "  -h, --help  Print this help\n");
    return 0;
  }

  char *path = argv[1];

  FILE *fp = fopen(path, "r");

  if (fp == NULL) {
    goto fopen_err;
  }

  char buf[MAX_LINE_LENGTH];
  unsigned long long lines = 0;
  unsigned long words = 0;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    lines++;

    int len = strlen(buf);
    for (int i = 0; i < len - 1; i++) {
      if (!isspace(buf[i])) {
        words++;
        while (!isspace(buf[i + 1])) {
          i++;
        }
      }
    }
  }

  fclose(fp);

  printf("Summary:\n\t- %lu words\n\t- %llu lines\n", words, lines);

  return 0;

fopen_err:
  switch (errno) {
  case EACCES | EPERM:
    eprintf("permission denied (os error %d)\n", errno);
    break;
  case EINVAL | ENAMETOOLONG:
    eprintf("%s is invalid (os error %d)\n", path, errno);
    break;

  case ENOENT:
    eprintf("no such file or directory (os error 2)\n");
    break;

  case ENOMEM:
    eprintf("not enough memory (os error 12)\n");
    break;

  case ELOOP:
    eprintf("too many symbolic links (os error 40)\n", path);
    break;

  case EOVERFLOW:
    eprintf("file too big (os error 75)\n");
    break;

  default:
    eprintf("an unknown error occured (os error %d)\n", errno);
    break;
  }
  return errno;
}

int eprintf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int status = vfprintf(stderr, fmt, args);
  va_end(args);
  return status;
}
