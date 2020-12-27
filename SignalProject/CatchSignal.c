#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <error.h>

void catchSignal(int sign)
{
    switch (sign)
    {
	case SIGINT:
	    fprintf(stderr, "ctrl+C signal was catched\n");
	    exit(11);
        case SIGTSTP:
            fprintf(stderr, "ctrl+Z signal was catched\n");
	    exit(10);
    }
}

int main()
{
    signal(SIGINT, catchSignal);
    signal(SIGTSTP, catchSignal);

    sleep(10);

    return 0;
}
