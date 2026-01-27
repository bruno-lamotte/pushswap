/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_up_to_five.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:57:27 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 01:55:05 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*get_max(t_stack *stack)
{
	t_stack	*max;
	t_stack	*tmp;

	if (!stack)
		return (NULL);
	max = stack;
	tmp = stack->next;
	while (tmp != stack)
	{
		if (tmp->index > max->index)
			max = tmp;
		tmp = tmp->next;
	}
	return (max);
}

t_stack	*get_min(t_stack *stack)
{
	t_stack	*min;
	t_stack	*tmp;

	if (!stack)
		return (NULL);
	min = stack;
	tmp = stack->next;
	while (tmp != stack)
	{
		if (tmp->index < min->index)
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

void	sort_three(t_stack **a, t_list **instructions)
{
	t_stack	*max;

	max = get_max(*a);
	if (*a == max)
		ra(a, instructions, 1);
	else if ((*a)->next == max)
		rra(a, instructions, 1);
	if ((*a)->index > (*a)->next->index)
		sa(a, instructions);
}

void	put_on_to_top(t_stack **a, t_stack *node, t_list **instructions)
{
	int		size;
	int		i;
	t_stack	*tmp;

	size = get_stack_size(*a);
	i = 0;
	tmp = *a;
	while (tmp != node && i++)
		tmp = tmp->next;
	if (i <= size / 2)
		while (*a != node)
			ra(a, instructions, 1);
	else
		while (*a != node)
			rra(a, instructions, 1);
}

void	sort_five(t_stack **a, t_stack **b, t_list **instructions)
{
	t_stack	*min;

	while (get_stack_size(*a) > 3)
	{
		min = get_min(*a);
		put_on_to_top(a, min, instructions);
		pb(a, b, instructions);
	}
	sort_three(a, instructions);
	while (*b)
		pa(a, b, instructions);
}
