/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:48:21 by lpetit            #+#    #+#             */
/*   Updated: 2023/10/29 17:28:58 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_byte;

	s_byte = (unsigned char *)s;
	while (n > 0)
	{
		*s_byte++ = 0;
		n--;
	}
	return ;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;
	size_t	limit;

	dest = NULL;
	limit = nmemb * size;
	if (limit != 0 && size != 0)
	{
		if (limit / size != nmemb)
		{
			return (NULL);
		}
	}
	if (nmemb == 0 || size == 0)
		limit = 0;
	dest = (void *)malloc(limit);
	if (!dest)
		return (NULL);
	ft_bzero(dest, nmemb * size);
	return (dest);
}
