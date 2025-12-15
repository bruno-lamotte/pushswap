/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:13:58 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/15 04:42:07 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*cut_node(t_stack **stack)
{
	t_stack	*node;

	if (!*stack)
		return (NULL);
	node = *stack;
	if ((*stack)->next == *stack)
		*stack = NULL;
	else
	{
		*stack = node->next;
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	node->next = node;
	node->prev = node;
	return (node);
}

void	push_node(t_stack **stack, t_stack *new_node)
{
	t_stack	*tail;

	if (!*stack)
	{
		*stack = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
	}
	else
	{
		tail = (*stack)->prev;
		tail->next = new_node;
		new_node->prev = tail;
		new_node->next = *stack;
		(*stack)->prev = new_node;
		*stack = new_node;
	}
}

void	pa(t_stack **a, t_stack **b)
{
	t_stack	*node;

	if (!*b)
		return ;
	node = cut_node(b);
	push_node(a, node);
	write(1, "pa\n", 3);
}

void	pb(t_stack **a, t_stack **b)
{
	t_stack	*node;

	if (!*a)
		return ;
	node = cut_node(a);
	push_node(b, node);
	write(1, "pb\n", 3);
}
