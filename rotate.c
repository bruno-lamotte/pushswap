/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:58:16 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/06 07:58:40 by blamotte         ###   ########.fr       */
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
	if (print && instructions)
		ft_lstadd_back(instructions, ft_lstnew(ft_strdup("ra")));
}

void	rb(t_stack **b, t_list **instructions)
{
	rotate(b);
	if (instructions)
		ft_lstadd_back(instructions, ft_lstnew(ft_strdup("rb")));
}

void	rr(t_stack **a, t_stack **b, t_list **instructions)
{
	rotate(a);
	rotate(b);
	if (instructions)
		ft_lstadd_back(instructions, ft_lstnew(ft_strdup("rr")));
}
