/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:00:21 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/06 07:59:09 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rev_rotate(t_stack **stack)
{
	if (!*stack)
		return ;
	*stack = (*stack)->prev;
}

void	rra(t_stack **a, t_list **instructions, int print)
{
	rev_rotate(a);
	if (print && instructions)
		ft_lstadd_back(instructions, ft_lstnew(ft_strdup("rra")));
}

void	rrb(t_stack **b, t_list **instructions)
{
	rev_rotate(b);
	if (instructions)
		ft_lstadd_back(instructions, ft_lstnew(ft_strdup("rrb")));
}

void	rrr(t_stack **a, t_stack **b, t_list **instructions)
{
	rev_rotate(a);
	rev_rotate(b);
	if (instructions)
		ft_lstadd_back(instructions, ft_lstnew(ft_strdup("rrr")));
}
