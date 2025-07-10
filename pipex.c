#include "pipex.h"

void	pipex(char **argv, char **envp)
{
	int	pipefd[2];
	int	infile;
	int	outfile;
	pid_t	pid1;
	pid_t	pid2;

	open_files(&infile, &outfile, argv);
	if (pipe(pipefd) < 0)
		error_n_exit("pipe");
	pid1 = fork();
	if (pid1 < 0)
		error_n_exit("fork");
	if (pid1 == 0)
		child1(infile, pipefd, argv[2], envp);
	pid2 = fork();
	if (pid2 < 0)
		error_n_exit("fork");
	if (pid2 == 0)
		child2(outfile, pipefd, argv[3], envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

