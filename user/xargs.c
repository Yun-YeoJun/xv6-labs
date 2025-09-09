#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {

    if (argc > MAXARG) {
        fprintf(2, "Maximum argument number is 32");
        return 1;
    }

    char stdin[100];

    while (1) {
        gets(stdin, 100);
        if (stdin[0] == '\0')
            break;
        int n = strlen(stdin);
        if (n > 0 && (stdin[n - 1] == '\n' || stdin[n - 1] == '\r'))
            stdin[n - 1] = '\0';
        int pid = fork();
        if (pid == 0) {
            char *newArgv[MAXARG];
            int i;
            for (i = 0; i < argc; i++) {
                newArgv[i] = argv[i + 1];
            }
            newArgv[i - 1] = stdin;
            char *path = malloc(strlen(argv[1]) + 1);
            path[0] = '/';
            path++;
            strcpy(path, argv[1]);
            path--;
            exec(path, newArgv);
        } else {
            wait(0);
        }
    }

    return 0;
}