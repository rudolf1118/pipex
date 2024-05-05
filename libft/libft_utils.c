#include "../include/pipex.h"

size_t	ft_strlen(const char *arg)
{
    size_t	i;

    i = 0;
    while (arg[i])
        i++;
    return (i);
}

static size_t	ft_strlen_safe(char const *s)
{
    if (s == NULL)
        return (0);
    return (ft_strlen(s));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
    size_t	len1;
    size_t	len2;
    char	*result;
    size_t	i;
    size_t	j;

    i = 0;
    len1 = ft_strlen_safe(s1);
    len2 = ft_strlen_safe(s2);
    result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!result)
        return (NULL);
    while (i < len1 && s1 != NULL)
    {
        result[i] = s1[i];
        i++;
    }
    j = 0;
    while (j < len2 && s2 != NULL)
    {
        result[i++] = s2[j++];
    }
    result[i] = '\0';
    return (result);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t	i;

    i = 0;
    if (dstsize > 0)
    {
        while (src[i] != '\0' && i < (dstsize - 1))
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    i = 0;
    while (src[i] != '\0')
        i++;
    return (i);
}


char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t	i;
    size_t	j;

    i = 0;
    if (ft_strlen(needle) == 0)
        return ((char *)haystack);
    while (i < len && haystack[i] != '\0')
    {
        j = 0;
        while (i + j < len && haystack[i + j] == needle[j] && needle[j] != '\0')
        {
            j++;
        }
        if (needle[j] == '\0')
            return ((char *)haystack + i);
        i++;
    }
    return (NULL);
}