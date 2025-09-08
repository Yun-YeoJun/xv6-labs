#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	
	// 0: read , 1: write
	int fd1[2]; // child -> parent
	if (pipe(fd1) == -1) {
		fprintf(2, "pipe error\n");
		return 1;
	}

	int fd2[2]; // parent -> child
	if (pipe(fd2) == -1) {
		fprintf(2, "pipe error\n");
		return 1;
	}

	int pid = fork();
	if (pid == -1) {
		fprintf(2, "fork error\n");
		return 1;
	}

	char buf[4];

	if (pid == 0) {
		read(fd2[0], buf, 4);
		printf("%d: received ping\n", getpid());
		write(fd1[1], "pong", 4);
	} else {
		write(fd2[1], "ping", 4);
		read(fd1[0], buf, 4);
		printf("%d: received pong\n", getpid());
	}

	return 0;
}
