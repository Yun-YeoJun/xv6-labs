#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int check(char secret[]) {
  int i;
  for (i = 0; i < 7; i++) {
    if (secret[i] == '.' || secret[i] == '/' || ('a' <= secret[i] && secret[i] <= 'f'))
      continue;
    return 0;
  }

  if (secret[7] == '\0')
    return 1;
  else
    return 0;
}

int
main(int argc, char *argv[])
{
  // your code here.  you should write the secret to fd 2 using write
  // (e.g., write(2, secret, 8)

  char *end = sbrk(PGSIZE*32);

  char secret[8];

  int i;
  for (i = 0; i < 32; i++) {
    char* base = end + PGSIZE * i;
    strcpy(secret, base + 32);
    if (check(secret) == 1) {
      printf("secret: %s\n", secret);
      break;
    }
  }

  write(2, secret, 8);
  exit(1);
}
