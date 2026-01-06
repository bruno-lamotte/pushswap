/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:05:53 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/06 07:57:02 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack *stack)
{
	int	tmp_val;
	int	tmp_index;

	if (!stack || stack->next == stack)
		return ;
	tmp_val = stack->value;
	tmp_index = stack->index;
	stack->value = stack->next->value;
	stack->index = stack->next->index;
	stack->next->value = tmp_val;
	stack->next->index = tmp_index;
}

void	sa(t_stack **a, t_list **instructions)
{
	swap(*a);
	ft_lstadd_back(instructions, ft_lstnew(ft_strdup("sa")));
}

void	sb(t_stack **b, t_list **instructions)
{
	swap(*b);
	ft_lstadd_back(instructions, ft_lstnew(ft_strdup("sb")));
}

void	ss(t_stack **a, t_stack **b, t_list **instructions)
{
	swap(*a);
	swap(*b);
	ft_lstadd_back(instructions, ft_lstnew(ft_strdup("ss")));
}
