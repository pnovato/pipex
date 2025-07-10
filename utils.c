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
	exit(EXIT_FAILURE);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**args;
	char	**paths;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		free(args);
		error_n_exit("Invalid command");
	}
	paths = split_path(envp);
	cmd_path = find_command(args[0], paths);
	if (!cmd_path)
	{
		free(args);
		error_n_exit("Command not found");
	}
	execve(cmd_path, args, envp);
	error_n_exit("execve failed");
} 
