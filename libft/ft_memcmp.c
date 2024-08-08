/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:19:29 by lpetit            #+#    #+#             */
/*   Updated: 2023/10/19 12:39:19 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

int	ft_memcmp(void const *s1, void const *s2, size_t n)
{
	unsigned char	*s1_byte;
	unsigned char	*s2_byte;
	size_t			i;

	i = 0;
	s1_byte = (unsigned char *)s1;
	s2_byte = (unsigned char *)s2;
	while (i < n)
	{
		if (s1_byte[i] != s2_byte[i])
			return (s1_byte[i] - s2_byte[i]);
		i++;
	}
	return (0);
}
