#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	char	**cmd1;
	char	*cmd1path;
	char	**cmd2;
	char	*cmd2path;
	char	*infile;
	char	*outfile;
	int		fd_in;
	int		fd_out;
	int		pipefd[2];
	int		status1;
	int		status2;
}	t_pipex;



//utils.c
char	**split_path(char **envp);
char	*find_command(char *cmd, char **paths);
void	error_n_exit(const char *msg);


//init.c
t_pipex	init_pipex(char **argv, char **envp);
void	free_pipex(t_pipex *px);
void	free_split(char **arr);

//pipex.c
void	pipex(char **argv, char **envp);

//child.c
void    open_files(int *infile, int *outfile, char **argv);
void    child1(t_pipex *px, char **envp);
void    child2(t_pipex *px, char **envp);


#endif
