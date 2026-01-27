/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:00:21 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 02:42:28 by blamotte         ###   ########.fr       */
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
	if (print)
		add_instruction(instructions, "rra");
}

void	rrb(t_stack **b, t_list **instructions)
{
	rev_rotate(b);
	if (instructions)
		add_instruction(instructions, "rrb");
}

void	rrr(t_stack **a, t_stack **b, t_list **instructions)
{
	rev_rotate(a);
	rev_rotate(b);
	add_instruction(instructions, "rrr");
}
