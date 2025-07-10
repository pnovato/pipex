#include "pipex.h"


void	open_files(int *infile, int *outfile, char **argv)
{
	*infile = open(argv[1], O_RDONLY);
	if (*infile < 0)
		error_n_exit("Error opening input file");
	*outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile < 0)
		error_n_exit("Error opening output file");
}

void	child1(int infile, int *pipefd, char *cmd, char **envp)
{
	dup2(infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exec_cmd(cmd, envp);
}

void	child2(int outfile, int *pipefd, char *cmd, char **envp)
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	exec_cmd(cmd, envp);
}
