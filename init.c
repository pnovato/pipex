#include "pipex.h"

void    free_split(char **arr)
{
        int     i;

        i = 0;
        if (!arr)
                return;
        while (arr[i])
                free(arr[i++]);
        free(arr);
}

static void	open_infile(t_pipex *px)
{
	px->fd_in = open(px->infile, O_RDONLY);
	if (px->fd_in < 0)
	{
		perror(px->infile);
		free_pipex(px);
		exit(1);
	}
}

static void	open_outfile(t_pipex *px)
{
	px->fd_out = open(px->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (px->fd_out < 0)
	{
		perror(px->outfile);
		free_pipex(px);
		exit(1);
	}
}

t_pipex	init_pipex(char **argv, char **envp)
{
	t_pipex	px;
	char	**paths;
	
	px.infile = argv[1];
	px.outfile = argv[4];
	px.cmd1 = ft_split(argv[2], ' ');
	px.cmd2 = ft_split(argv[3], ' ');
	paths = split_path(envp);
	if (!px.cmd1 || !px.cmd1[0])
		px.cmd1path = NULL;
	else
		px.cmd1path = find_command(px.cmd1[0], paths);
	if (!px.cmd2 || !px.cmd2[0])
		px.cmd2path = NULL;
	else
		px.cmd2path = find_command(px.cmd2[0], paths);
	free_split(paths);
	open_infile(&px);
	open_outfile(&px);
	return (px);
}

void	free_pipex(t_pipex *px)
{
	int	i;
	
	if (px->cmd1)
	{
		i = 0;
		while (px->cmd1[i])
			free(px->cmd1[i++]);
		free(px->cmd1);
	}
	if (px->cmd1path)
		free(px->cmd1path);
	if (px->cmd2path)
		free(px->cmd2path);
}
