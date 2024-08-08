/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:51:41 by lpetit            #+#    #+#             */
/*   Updated: 2023/10/06 17:19:29 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static int	ft_count_digit(int n)
{
	int			digit;
	long int	nbr;

	nbr = (long int) n;
	digit = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		digit++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		digit++;
	}
	return (digit);
}

static void	ft_assign_str(int n, int digit, char *str)
{
	int			i;
	long int	nbr;

	i = 0;
	nbr = (long int) n;
	str[digit--] = '\0';
	if (nbr == 0)
	{
		str[i] = '0';
		return ;
	}
	if (nbr < 0)
	{
		str[i] = '-';
		i++;
		nbr = -nbr;
	}
	while (digit >= i)
	{
		str[digit--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return ;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digit;

	digit = ft_count_digit(n);
	str = (char *)malloc((digit + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_assign_str(n, digit, str);
	return (str);
}
