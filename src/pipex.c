/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rharutyu <rharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:46:38 by rharutyu          #+#    #+#             */
/*   Updated: 2024/05/06 18:26:48 by rharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	len1;
	int	len2;
	int	i;
	int	j;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	i = 0;
	while (i <= len1 - len2)
	{
		j = 0;
		while (j < len2 && str1[i + j] == str2[j])
		{
			j++;
		}
		if (j == len2)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	validation(char **argv)
{
	if (ft_strcmp(argv[1], "/dev/urandom") || ft_strcmp(argv[1], "/dev/random")
		|| ft_strcmp(argv[4], "/dev/urandom") || ft_strcmp(argv[4],
			"/dev/random"))
	{
		ft_putstr_fd("No such a file or directory\n", 2);
		return (1);
	}
	else if (!(argv[2][0] >= 'a' && argv[2][0] <= 'z') && !(argv[2][0] >= 'A'
			&& argv[2][0] <= 'Z') && !(argv[3][0] >= 'a' && argv[3][0] <= 'z')
		&& !(argv[3][0] >= 'A' && argv[3][0] <= 'Z'))
	{
		msg(ERR_CMD);
		return (1);
	}
	return (0);
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fileout;

	fileout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fileout == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5 && envp)
	{
		if (validation(argv))
			return (0);
		if (pipe(fd) == -1)
			msg(ERR_PIPE);
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			child_process(argv, envp, fd);
		waitpid(pid, NULL, 0);
		parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("\033[31mInvalid number of arguments\n\n\e[0m", 2);
		ft_putstr_fd("Example of correct version:", 1);
		ft_putstr_fd("./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit(1);
	}
}
