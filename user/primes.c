#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int pipe_component(int fd[]);

int main(int argv, char *argc[]) {

	int fd[2];
	if (pipe(fd) == -1) {
		fprintf(2, "pipe error at main\n");
		return 1;
	}

	int pid = fork();
	if (pid == 0) { // child
		close(fd[1]);
		if (pipe_component(fd) == 1) {
			return 1;
		}
	} else { // parent
		close(fd[0]);
		for (int i = 2; i < 281; i++) {
			write(fd[1], &i, sizeof(int));
		}
		close(fd[1]);
		wait(0);
	}

	return 0;
}

int pipe_component(int fd[]) {

		int n;
		int step = -1;

		if (read(fd[0], &n, sizeof(int)) != 0) {
			step = n;
			printf("prime %d\n", step);
			int fd2[2];
			if (pipe(fd2) == -1) {
				fprintf(2, "pipe error at pipe_component\n");
				close(fd[0]);
				return 1;
			}

			int pid = fork();
			if (pid == 0) {
				close(fd[0]);
				close(fd2[1]);
				pipe_component(fd2);

			} else {
				close(fd2[0]);
				while(read(fd[0], &n, sizeof(int)) != 0) {
					if (n % step == 0) {
						continue;
					} else {
						write(fd2[1], &n, sizeof(int));
					}
				}
			}
			close(fd2[1]);
		}

		close(fd[0]);
		wait(0);
		return 0;
}
