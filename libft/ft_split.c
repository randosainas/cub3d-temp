/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:37:05 by lpetit            #+#    #+#             */
/*   Updated: 2023/10/21 19:33:03 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static	void	ft_free_all_tab(char **tab, int tabindex)
{
	while (tabindex >= 0)
		free(tab[tabindex--]);
	free(tab);
	return ;
}

static int	ft_word_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static size_t	ft_strlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

static char	*ft_create_str(char const *s, char c, char **tab, int tabindex)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s, c);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
	{
		ft_free_all_tab(tab, tabindex - 1);
		return (NULL);
	}
	while (len != 0)
	{
		str[i++] = *s++;
		len--;
	}
	str[i] = '\0';
	tab[tabindex] = str;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	tab = (char **)malloc((ft_word_count(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			if (ft_create_str(s, c, tab, i) == NULL)
				return (NULL);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	tab[i] = 0;
	return (tab);
}
