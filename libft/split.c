#include "../include/pipex.h"

static int	mallocer(char **result, size_t i, size_t len)
{
    result[i] = (char *)malloc(sizeof(char) * (len + 1));
    if (!result[i])
    {
        while (i >= 0)
        {
            free(result[i--]);
        }
        free(result);
        return (1);
    }
    return (0);
}

static int	fill(char **result, char const *s, char c)
{
    int		i;
    size_t	len;

    i = 0;
    while (*s)
    {
        len = 0;
        while (*s == c && *s)
            ++s;
        while (*s != c && *s)
        {
            ++len;
            ++s;
        }
        if (len)
        {
            if (mallocer(result, i, len + 1))
                return (1);
            ft_strlcpy(result[i], (s - len), len + 1);
        }
        i++;
    }
    return (0);
}

static size_t	count_tokens(char const *s, char c)
{
    int	in_str;
    int	count;

    count = 0;
    while (*s)
    {
        in_str = 0;
        while (*s == c && *s)
            ++s;
        while (*s != c && *s)
        {
            if (!in_str)
            {
                ++count;
                in_str = 1;
            }
            ++s;
        }
    }
    return (count);
}

char	**ft_split(char const *s, char c)
{
    size_t	tokens;
    char	**result;

    if (!s)
        return (NULL);
    tokens = count_tokens(s, c);
    result = (char **)malloc(sizeof(char *) * (tokens + 1));
    if (!result)
        return (NULL);
    result[tokens] = NULL;
    if (fill(result, s, c))
        return (NULL);
    return (result);
}