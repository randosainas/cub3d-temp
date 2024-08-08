/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:21:04 by lpetit            #+#    #+#             */
/*   Updated: 2024/08/08 13:22:58 by lpetit           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

char	*ft_strjoin_f(char *s1, char *s2)
{
	char	*jstr;
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	jstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!jstr)
		return (NULL);
	if (s1)
		while (s1[i])
		{
			jstr[i] = s1[i];
			i++;
		}
	if (s2)
		while (s2[w])
			jstr[i++] = s2[w++];
	jstr[i] = '\0';
	free(s1);
	free(s2);
	return (jstr);
}
