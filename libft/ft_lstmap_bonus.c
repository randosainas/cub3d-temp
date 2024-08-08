/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:50 by lpetit            #+#    #+#             */
/*   Updated: 2023/11/03 00:19:54 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	newlst = ft_lstnew(f(lst->content));
	if (!newlst)
		return (NULL);
	tmp = newlst;
	lst = lst->next;
	while (lst)
	{
		newlst->next = ft_lstnew(f(lst->content));
		if (!newlst->next)
		{
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		newlst = newlst->next;
		lst = lst->next;
	}
	return (tmp);
}
/*
void delete(void *content)
{
	char *str = (char *)content;
	if (str == NULL)
		return;
	if (str[0] != '_' || str[1] != '_')
		write(1, "error", 6);
	free(content);
}

void	*ft_plus_one(void *content)
{
	int	i = 0;
	if (content)
	{
		//printf("%d\n", *(int *)content);
		i = 1;
		//printf("%d\n", *(int *)content);
	}
	return (content);
}


int	main(void)
{
	t_list	**lst;
	t_list	*first;
	t_list	*second;
	t_list	*third;

	lst = (t_list **)malloc(sizeof(t_list **));
	first = ft_lstnew("one");
	*lst = first;
	second = ft_lstnew("two");
	ft_lstadd_back(lst, second);
	third = ft_lstnew("three");
	ft_lstadd_back(lst, third);
	ft_lstmap(*lst, ft_plus_one, delete);
	free(first);
	free(second);
	free(third);
	free(lst);
}*/
