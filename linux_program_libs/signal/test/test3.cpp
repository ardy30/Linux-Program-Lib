#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

void f(int n)
{
    cout << "in f" << endl;
}

int main()
{
    int fd[2];
    if(pipe(fd) == -1)
    {
	cout << "pipe error" << endl;
	return 0;
    }

    int size = fpathconf(fd[0], _PC_PIPE_BUF);

    if(fork() == 0)
    {
	close(fd[0]);

	signal(SIGPIPE, f);

	char *p = new char[15*size];

	cout << write(fd[1], p, 15*size) << endl;

	cout << "hello: " << write(fd[1], p, 2*size-100) << endl;

	close(fd[1]);
	
	exit(0);
    }

    close(fd[1]);

    sleep(5);

    close(fd[0]);

    wait(0);

    cout << "father close read fd" << endl;

    return 0;
}
