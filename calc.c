#include <stdio.h>
#include <string.h>

// Null byte :c
#define MAX_NUMBER_LENGTH 34
#define MAX_OPERATOR_LENGTH 4 // op + Some(\r) + \n + \0

int main(int argc, char *argv[]) {
  printf("Enter number: ");
  char buf[MAX_NUMBER_LENGTH];

  if (fgets(buf, sizeof(buf), stdin) == NULL) {
    fprintf(stderr, "An error occured reading from standard input!\n");
    return 1;
  }
  // SAFETY: Even if there is no newline, we just set \0 to \0
  buf[strcspn(buf, "\r\n")] = 0;

  double first;
  if (sscanf(buf, "%lf", &first) != 1) {
    fprintf(stderr, "Failed to convert %s to a double!\n", buf);
    return 1;
  }

  printf("Enter operator: ");
  char op[MAX_OPERATOR_LENGTH];

  if (fgets(op, sizeof(op), stdin) == NULL) {
    fprintf(stderr, "An error occured reading from standard input!\n");
    return 1;
  }
  op[strcspn(op, "\r\n")] = 0;

  printf("Enter number: ");
  if (fgets(buf, sizeof(buf), stdin) == NULL) {
    fprintf(stderr, "An error occured reading from standard input!\n");
    return 1;
  }
  buf[strcspn(buf, "\r\n")] = 0;

  double second;
  if (sscanf(buf, "%lf", &second) != 1) {
    fprintf(stderr, "Failed to convert %s to a double!\n", buf);
    return 1;
  }

  if (strcmp(op, "+") == 0) {
    printf("%lf + %lf = %lf\n", first, second, first + second);
  } else if (strcmp(op, "-") == 0) {
    printf("%lf - %lf = %lf\n", first, second, first - second);
  } else if (strcmp(op, "/") == 0) {
    printf("%lf / %lf = %lf\n", first, second, first / second);
  } else if (strcmp(op, "*") == 0 || strcmp(op, "x") == 0) {
    printf("%lf x %lf = %lf\n", first, second, first * second);
  } else {
    fprintf(stderr, "Unknown operator %s.\n", op);
  }

  return 0;
}
