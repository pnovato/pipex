#include "pipex.h"


char	**split_path(char **envp)
{
	int	i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_command(char *cmd, char **paths)
{
	char	*full_path;
	char	*temp;
	int	i;
	
	if (!cmd)
		return (NULL);
	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (paths && paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	error_n_exit(const char *msg)
{
	perror(msg);
	exit(127);
}

void	default_error_exit(char **args)
{
	write(2, "command not found\n", 19);
	free(args);
	exit(127);
}

