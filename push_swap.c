/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:07:12 by daejlee           #+#    #+#             */
/*   Updated: 2022/09/09 15:07:13 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "./libft_garage/libft/libft.h"
#include "./libft_garage/ft_printf/ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

//./push_swap 1 2 7 11 22 927 731 33

void	print_stack(t_decue_addr *p)
{
	t_decue	*head;

	ft_printf("-------------------------------\n");
	ft_printf("signed val is following.....\n");
	ft_printf("-------------------------------\n");
	head = p->a_top;
	while (head)
	{
		ft_printf("%d\n", head->val);
		head = head->next;
	}
	ft_printf("-\na\n");
	head = p->b_top;
	while (head)
	{
		ft_printf("%d\n", head->val);
		head = head->next;
	}
	ft_printf("-\nb\n");
	ft_printf("-------------------------------\n");
	ft_printf("unsigned val is following.....\n");
	ft_printf("-------------------------------\n");
	head = p->a_top;
	while (head)
	{
		ft_printf("%u\n", head->u_val);
		head = head->next;
	}
	ft_printf("-\na\n");
	head = p->b_top;
	while (head)
	{
		ft_printf("%u\n", head->u_val);
		head = head->next;
	}
	ft_printf("-\nb\n");
}

unsigned int	get_dig(unsigned int val, unsigned int div)
{
	if (div == 1)
		return (val % 10);
	else
	{
		div *= 10;
		val %= div;
		div /= 10;
		return (val /= div);
	}
}

unsigned int	get_count(t_decue *target, unsigned int div,
		unsigned int pushing_int)
{
	unsigned int	count;
	unsigned int	target_dig;

	count = 0;
	while (target)
	{
		target_dig = get_dig(target->u_val, div);
		if (target_dig == pushing_int)
			count++;
		target = target->previous;
	}
	return (count);
}

static void	mv_b_to_a(t_decue_addr *p)
{
	while (p->b_top)
	{
		pa(p);
		if (p->a_top->next)
			ra(p);
		else
			p->a_bottom = p->a_top;
	}
}

void	radix_sort(t_decue_addr *p)
{
	unsigned int	div;
	t_decue			*target;

	div = 1;
	target = p->a_top;
	p->idx_chamber = (int *)malloc(sizeof(int) * p->size);
	if (!p->idx_chamber)
		return ;
	while (p->u_max / div)
	{
		if (target == p->a_top)
		{
			sort_loop_to_b(p, div);
			target = p->b_top;
		}
		else
		{
			sort_loop_to_a(p, div);
			target = p->a_top;
		}
		div *= 10;
	}
	if (p->b_top)
		mv_b_to_a(p);
}

int	main(int argc, char **argv)
{
	t_decue_addr	*p;

	if (argc == 1)
		return (1);
	else if (is_int(argv) || is_there_dup(argv))
		return (print_err());
	p = init_p();
	p->size = push_args_to_a(argv, p);
	if (!p->size)
		return (1);
	else if (check_already_sorted(p->a_top))
		return (purge_lst(p));
	if (argc < 5)
		manual_sort(argc, p);
	else
		radix_sort(p);
	print_stack(p);
	return (purge_lst(p));
}
