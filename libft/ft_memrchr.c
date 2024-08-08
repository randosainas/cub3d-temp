/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:33:31 by lpetit            #+#    #+#             */
/*   Updated: 2023/09/15 17:31:44 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memrchr(const void *s, int c, size_t n)
{
	unsigned char	*s_byte;
	unsigned char	c_val;
	int				i;

	i = n - 1;
	s_byte = (unsigned char *)s;
	c_val = (unsigned char)c;
	while (i >= 0)
	{
		if (s_byte[i] == c_val)
		{
			return (s_byte + i);
		}
		i--;
	}
	return (NULL);
}
