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

//utils.c
char	**split_path(char **envp);
char	*find_command(char *cmd, char **paths);
void	error_n_exit(const char *msg);
void    exec_cmd(char *cmd, char **envp);

//pipex.c
void	pipex(char **argv, char **envp);

//child.c
void    open_files(int *infile, int *outfile, char **argv);
void    child1(int infile, int *pipefd, char *cmd, char **envp);
void    child2(int outfile, int *pipefd, char *cmd, char **envp);


#endif
