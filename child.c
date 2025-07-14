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

void	child1(t_pipex *px, char **envp)
{
	if (!px->cmd1 || !px->cmd1[0] || !px->cmd1path)
	{
		write(2, "command not found\n", 19);
		exit(127);
	}
	dup2(px->fd_in, STDIN_FILENO);
	dup2(px->pipefd[1], STDOUT_FILENO);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	execve(px->cmd1path, px->cmd1, envp);
	error_n_exit("execve failed (cmd1)");
}

void	child2(t_pipex *px, char **envp)
{
	if (!px->cmd2 || !px->cmd2[0] || !px->cmd2path)
	{
		write(2, "command not found\n", 19);
		exit(127);
	}
	dup2(px->pipefd[0], STDIN_FILENO);
        dup2(px->fd_out, STDOUT_FILENO);
        close(px->pipefd[1]);
        close(px->pipefd[0]);
	execve(px->cmd2path, px->cmd2, envp);
	error_n_exit("execve failed (cmd2)");
}
