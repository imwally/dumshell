#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 4096

void
sig_int(int signo) 
{
    printf("\nSIGNAL CAUGHT: SIGINT\n");
}

void
error_fatal(const char *msg, ...) {
    char        buf[MAXLINE];
    va_list     ap;
    va_start(ap, msg);

    vsnprintf(buf, MAXLINE, msg, ap);
    snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(errno));
    strcat(buf, "\n");
    fputs(buf, stderr);

    va_end(ap);
    exit(1);
}

int
main(void)
{
    char    buf[MAXLINE];
    char    cwd[MAXLINE];
    pid_t   pid;
    int     status;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        error_fatal("signal error");
    }

    printf("Hello %s,\n\n", getlogin());
    printf("Welcome to the dumshell -- a dumb shell that dumps UNIX process "
            "information to STDOUT.\n\n"
            "Use the command 'exit' to leave the shell at anytime.\n\n"
            "Here is some information about this current process:\n----\n");

    if ((getcwd(cwd, MAXLINE) != NULL)) {
        printf("Current working directory (CWD): %s\n", cwd);
    } else{
        error_fatal("couldn't get working directory: %s", cwd);
    }

    printf("User running this process (UID): %d\n", getuid());
    printf("Parent Process (PPID): %d\n", getppid());
    printf("Current Process (PID): %d\n", getpid());

    printf("----\n%% ");

    while (fgets(buf, MAXLINE, stdin) != NULL && (strncmp(buf, "exit", 4) != 0)) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0;
        }

        // Fork current process. 
        if ((pid = fork()) < 0) {
            error_fatal("fork error: %d", pid);
        } else if (pid == 0) {
            printf(">>>> Process %d forked from %d <<<<\n", getpid(), getppid());
            execlp(buf, buf, (char *)0);
            error_fatal("exec error: %s", buf);
            exit(127);
        }

        // Wait for child process.
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            error_fatal("waitpid error: %d", pid);
        } else {
            printf(">>>> Returning to parent process %d <<<<\n", getpid());
        }

        printf("%% ");
    }

    exit(0);
}
