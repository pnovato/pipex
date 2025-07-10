#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "pipex.h"

int main(int ac, char **av, char **envp)
{	
	if (ac != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
		return (1);
	}
	pipex(av, envp);
	return (0);
}
