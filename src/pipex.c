#include "../include/pipex

int validation(const char *str1, const char *str2) {
    int len1;
    int len2;
    int i;
    int j;

    len1 = ft_strlen(str1);
    len2 = ft_strlen(str2);
    i = 0;
    while (i <= len1 - len2) {
       j = 0;
        while (j < len2 && str1[i + j] == str2[j]) {
            j++;
        }
        if (j == len2) {
            return 1;
        }
        i++;
    }
    return 0;
}

void child_process(char **argv, char **envp, int *fd)
{
    int filein;

    filein = open(argv[1], O_RDONLY);
    if (filein == -1)
        error();
    dup2(fd[1],STDOUT_FILENO);
    dup2(filein,STDIN_FILENO);
    close(fd[0]);
    execute(argv[2], envp);
}
void parent_process(char **argv, char **envp, int *fd)
{
    int fileout;

    fileout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (fileout == -1)
        error();
    dup2(fd[0],STDIN_FILENO);
    dup2(fileout,STDOUT_FILENO);
    close(fd[1]);
    execute(argv[3],envp);
}

int main__ (int argc, char **argv, char **envp)
{
    int fd[2];
    pid_t pid;

    if (argc == 5)
    {
       if (validation(argv[1],"/dev/urandom") || validation(argv[1],"/dev/random") || validation(argv[4],"/dev/urandom") || validation(argv[4],"/dev/random"))
       {
           ft_putstr_fd("No such a file or directory\n", 2);
           return 0;
       }
        if (pipe(fd) == -1)
            error();
        pid = fork();
        if (pid == -1)
            error();
        if (pid == 0)
            child_process(argv,envp,fd);
        waitpid(pid, NULL, 0);
        parent_process(argv,envp,fd);
    }
    else {
        ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
        ft_putstr_fd("Example of correct version: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
    }
}
int main ()
{
    main__
}