/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:59:29 by lpetit            #+#    #+#             */
/*   Updated: 2023/09/12 15:03:59 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_byte;
	unsigned char	c_value;

	s_byte = (unsigned char *)s;
	c_value = (unsigned char)c;
	while (n > 0)
	{
		*s_byte++ = c_value;
		n--;
	}
	return (s);
}
