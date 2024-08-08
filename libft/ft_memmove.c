/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:46:10 by lpetit            #+#    #+#             */
/*   Updated: 2023/10/19 05:48:16 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

static void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	while (n--)
		*((unsigned char *)dest + n) = *((unsigned char *)src + n);
	return (dest);
}

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	unsigned char	*dest_byte;
	unsigned char	*src_byte;

	dest_byte = (unsigned char *)dest;
	src_byte = (unsigned char *) src;
	if (!dest && !src)
		return (NULL);
	if (dest_byte < src_byte)
	{
		while (n > 0)
		{
			*dest_byte++ = *src_byte++;
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
