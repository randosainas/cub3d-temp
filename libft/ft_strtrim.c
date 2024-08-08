/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:59:32 by lpetit            #+#    #+#             */
/*   Updated: 2023/10/19 17:41:36 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strdup(char const *s)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_isset(char c, char const *set)
{
	size_t	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	ft_trimcpy(char *cp, char const *s1, size_t start, size_t end)
{
	size_t	l;

	l = 0;
	while (start <= end)
		cp[l++] = s1[start++];
	cp[l] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*cp;

	start = 0;
	end = 0;
	if (!s1 || s1[0] == '\0')
		return (ft_strdup(""));
	while (s1[end])
		end++;
	end -= 1;
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	if (s1[start] == '\0')
		return (ft_strdup(""));
	while (s1[end] && ft_isset(s1[end], set))
		end--;
	cp = (char *)malloc(((end - start) + 2) * sizeof(char));
	if (!cp)
		return (NULL);
	ft_trimcpy(cp, s1, start, end);
	return (cp);
}
