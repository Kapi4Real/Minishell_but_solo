#include "libft.h"

int ft_isspace(int c)
{
    return (c == ' '  || c == '\t' || c == '\n' \
         || c == '\r' || c == '\v' || c == '\f');
}
