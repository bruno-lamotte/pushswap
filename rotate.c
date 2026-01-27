/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:58:16 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 02:42:28 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack **stack)
{
	if (!*stack)
		return ;
	*stack = (*stack)->next;
}

void	ra(t_stack **a, t_list **instructions, int print)
{
	rotate(a);
	if (print)
		add_instruction(instructions, "ra");
}

void	rb(t_stack **b, t_list **instructions)
{
	rotate(b);
	if (instructions)
		add_instruction(instructions, "rb");
}

void	rr(t_stack **a, t_stack **b, t_list **instructions)
{
	rotate(a);
	rotate(b);
	add_instruction(instructions, "rr");
}
