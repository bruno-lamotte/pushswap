/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 04:16:10 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 02:05:53 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#define DEPTH 0
#define CANDIDATES 1

t_stack	*copy_stack(t_stack *stack, int size)
{
	t_stack	*nstack;
	t_stack	*current;
	t_stack	*node;
	int		i;

	if (!stack)
		return (NULL);
	(1 && (nstack = NULL), (current = stack), (i = 0));
	while (i++ < size)
	{
		node = malloc(sizeof(t_stack));
		if (!node)
			return (free_stack(&nstack), NULL);
		(1 && (node->value = current->value), (node->index = current->index));
		if (!nstack)
			(1 && (nstack = node), (node->next = node), (node->prev = node));
		else
		{
			(1 && (node->next = nstack), (node->prev = nstack->prev));
			(1 && (nstack->prev->next = node), (nstack->prev = node));
		}
		current = current->next;
	}
	return (nstack);
}

int	evaluate_branch(t_stack *a, t_stack *b, int depth, int size)
{
	t_mouv	mouvs[CANDIDATES];
	t_eval	e;

	if (!b || depth <= 0)
		return (0);
	get_best_mouvs(a, b, mouvs, size);
	if (depth == 1)
		return (mouvs[0].total_cost);
	(1 && (e.best = 2147483647), (e.i = 0));
	while (e.i < CANDIDATES && mouvs[e.i].total_cost != 2147483647)
	{
		e.temp_a = copy_stack(a, get_stack_size(a));
		e.temp_b = copy_stack(b, size);
		mouv_up_in_b(mouvs[e.i].cost_b, &e.temp_a, &e.temp_b, NULL);
		e.total = mouvs[e.i].total_cost + evaluate_branch(e.temp_a, e.temp_b,
				depth - 1, size - 1);
		if (e.total < e.best)
			e.best = e.total;
		free_stack(&e.temp_a);
		free_stack(&e.temp_b);
		e.i++;
	}
	return (e.best);
}

void	reintegrate(t_stack **a, t_stack **b, t_list **instructions, int size)
{
	t_mouv	mouvs[CANDIDATES];
	t_eval	e;
	int		best_idx;

	if (!*b)
		return ;
	get_best_mouvs(*a, *b, mouvs, size);
	(1 && (best_idx = 0), (e.best = 2147483647), (e.i = 0));
	while (e.i < CANDIDATES && mouvs[e.i].total_cost != 2147483647)
	{
		e.temp_a = copy_stack(*a, get_stack_size(*a));
		e.temp_b = copy_stack(*b, size);
		mouv_up_in_b(mouvs[e.i].cost_b, &e.temp_a, &e.temp_b, NULL);
		e.total = mouvs[e.i].total_cost + evaluate_branch(e.temp_a, e.temp_b,
				DEPTH, size - 1);
		if (e.total < e.best)
			(1 && (e.best = e.total), (best_idx = e.i));
		free_stack(&e.temp_a);
		free_stack(&e.temp_b);
		e.i++;
	}
	mouv_up_in_b(mouvs[best_idx].cost_b, a, b, instructions);
}

void	final_rotate(t_stack **a, t_list **instructions, int size)
{
	int		min_pos;
	int		i;
	t_stack	*current;
	t_stack	*min_node;

	(1 && (current = *a), (min_node = *a), (min_pos = 0), (i = 0));
	while (i < size)
	{
		if (current->value < min_node->value)
			(1 && (min_node = current), (min_pos = i));
		current = current->next;
		i++;
	}
	if (min_pos <= size / 2)
	{
		while (min_pos-- > 0)
			ra(a, instructions, 1);
	}
	else
	{
		min_pos = size - min_pos;
		while (min_pos-- > 0)
			rra(a, instructions, 1);
	}
}

void	algo(t_stack **a, t_stack **b, t_list **instructions)
{
	int	size;

	size = get_stack_size(*a);
	k_sorting(a, b, instructions, size);
	while (*b)
	{
		reintegrate(a, b, instructions, get_stack_size(*b));
	}
	final_rotate(a, instructions, size);
}
