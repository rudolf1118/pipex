#include "../include/pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
    int	i;

    i = 0;
    if (!s)
        return ;
    while (s[i])
    {
        write(fd, &s[i], 1);
        ++i;
    }
}

char *find_path(char *cmd, char **envp)
{
    int i;
    char **paths;
    char *part_path;
    char *path;
    i = 0;
    while (ft_strnstr(envp[i], "PATH", 4) == 0)
        i++;
    paths = ft_split(envp[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    i = -1;
    while (paths[++i])
        free(paths[i]);
    free(paths);
    return (0);
}

void	error(void)
{
    perror("\033[31mError");
    exit(EXIT_FAILURE);
}

void execute(char *argv, char **envp)
{
    char **cmd;
    char *path;
    int i;

    cmd = ft_split(argv, 32);
    path = find_path(cmd[0],envp);
    i = 0;
    if (!path)
    {
        while (cmd[i])
            free(cmd[i++]);
        free(cmd);
        error();
    }
    if (execve(path,cmd, envp) == -1)
        error();
}