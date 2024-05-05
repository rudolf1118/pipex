#ifndef PIPEX_H
# define PIPEX_H
#include <unistd.h>
#include <stdio.h>
#include<sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void child_process(char **argv, char **envp, int *fd);
void execute(char *argv, char **envp);
char *find_path(char *cmd, char **envp);
void	error(void);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *arg);
void	ft_putstr_fd(char *s, int fd);
#endif