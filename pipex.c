#include "pipex.h"

static void	run_child(pid_t *pid, void (*child_fn)(t_pipex *, char **),
						t_pipex *px, char **envp)
{
	*pid = fork();
	if (*pid < 0)
		error_n_exit("fork");
	if (*pid == 0)
		child_fn(px, envp);
}

static void	create_and_fork(t_pipex *px, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	run_child(&pid1, child1, px, envp);
	run_child(&pid2, child2, px, envp);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	waitpid(pid1, &px->status1, 0);
	waitpid(pid2, &px->status2, 0);
	free_pipex(px);
	if (WIFEXITED(px->status2))
		exit(WEXITSTATUS(px->status2));
	else
		exit(1);
}

void	pipex(char **argv, char **envp)
{
	t_pipex px;
	
	px = init_pipex(argv, envp);
	open_files(&px.fd_in, &px.fd_out, argv);
	if (pipe(px.pipefd) < 0)
		error_n_exit("pipe");
	create_and_fork(&px, envp);
}

