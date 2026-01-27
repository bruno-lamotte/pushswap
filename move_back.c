/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:58:23 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 01:58:26 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	mouv_cost_b(t_stack **b, t_stack *target, int direction)
{
	int		f_cost;
	int		b_cost;
	t_stack	*current;
	t_stack	*start;

	if (!b || !*b || !target)
		return (0);
	(1 && (start = *b), (current = *b), (f_cost = 0), (b_cost = 0));
	while (current != target)
	{
		current = current->next;
		f_cost++;
		if (current == start)
			break ;
	}
	current = *b;
	while (current != target)
	{
		(1 && (current = current->prev), (b_cost = b_cost + 1));
		if (current == start)
			break ;
	}
	if (direction)
		return (f_cost);
	return (-b_cost);
}

int	mouv_cost_a(t_stack **a, t_stack *target, int size, int direction)
{
	int		f_cost;
	int		b_cost;
	t_stack	*current;
	t_stack	*start;

	if (!a || !*a || !target)
		return (0);
	(1 && (start = *a), (current = *a), (f_cost = 0));
	while (f_cost < size && current->value < target->value)
	{
		current = current->next;
		f_cost++;
		if (current == start)
			break ;
	}
	b_cost = size - f_cost;
	if (direction)
		return (f_cost);
	else
		return (-b_cost);
}

int	find_insert_pos(t_stack **a, int value, int size)
{
	t_stack	*cur;
	t_stack	*min_node;
	t_stack	*max_node;
	int		min_pos;
	int		i;

	(1 && (cur = *a), (min_node = *a), (max_node = *a), (min_pos = 0), (i = 0));
	while (i < size)
	{
		if (cur->value < min_node->value)
			(1 && (min_node = cur), (min_pos = i));
		if (cur->value > max_node->value)
			max_node = cur;
		(1 && (cur = cur->next), (i = i + 1));
	}
	if (value < min_node->value || value > max_node->value)
		return (min_pos);
	(1 && (cur = *a), (i = 0));
	while (i < size)
	{
		if (cur->value < value && cur->next->value > value)
			return (i + 1);
		(1 && (cur = cur->next), (i = i + 1));
	}
	return (min_pos);
}

void	insert_sorted(t_stack **a, t_stack **b, t_list **instructions, int size)
{
	int	pos;
	int	moves;
	int	print;

	print = instructions != 0;
	if (!*a)
		return (pa(a, b, instructions));
	pos = find_insert_pos(a, (*b)->value, size);
	if (pos <= size / 2)
	{
		moves = pos;
		while (moves-- > 0)
			ra(a, instructions, print);
	}
	else
	{
		moves = size - pos;
		while (moves-- > 0)
			rra(a, instructions, print);
	}
	pa(a, b, instructions);
}

void	mouv_up_in_b(int steps, t_stack **a, t_stack **b, t_list **instructions)
{
	while (steps != 0)
	{
		if (steps > 0)
		{
			rb(b, instructions);
			steps--;
		}
		else
		{
			rrb(b, instructions);
			steps++;
		}
	}
	insert_sorted(a, b, instructions, get_stack_size(*a));
}
