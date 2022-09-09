/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:06:36 by daejlee           #+#    #+#             */
/*   Updated: 2022/09/09 15:06:37 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft_garage/libft/libft.h"
#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

int	print_err(void)
{
	write(2, "Error\n", ft_strlen("Error\n"));
	return (1);
}

int	purge_lst(t_decue_addr *p)
{
	t_decue	*temp1;
	t_decue	*temp2;

	temp1 = p->a_top;
	while (temp1)
	{
		temp2 = temp1->next;
		temp1->previous = NULL;
		temp1->next = NULL;
		free(temp1);
		temp1 = temp2;
	}
	temp1 = p->b_top;
	while (temp1)
	{
		temp2 = temp1->next;
		temp1->previous = NULL;
		temp1->next = NULL;
		free(temp1);
		temp1 = temp2;
	}
	free (p);
	return (0);
}

t_decue_addr	*init_p(void)
{
	t_decue_addr	*ret;

	ret = (t_decue_addr *)malloc(sizeof(t_decue_addr));
	if (!ret)
		return (NULL);
	ret->a_top = NULL;
	ret->a_bottom = NULL;
	ret->b_top = NULL;
	ret->b_bottom = NULL;
	ret->u_max = 0;
	ret->min = 0;
	ret->size = 0;
	return (ret);
}
