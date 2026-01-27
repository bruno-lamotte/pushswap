/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:50:34 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 03:27:51 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_new_node(int value)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_back(t_stack **stack, t_stack *new_node)
{
	t_stack	*last;

	if (!new_node)
		return ;
	if (!*stack)
	{
		*stack = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last = (*stack)->prev;
		last->next = new_node;
		new_node->prev = last;
		new_node->next = *stack;
		(*stack)->prev = new_node;
	}
}

int	get_stack_size(t_stack *stack)
{
	t_stack	*tmp;
	int		count;

	if (!stack)
		return (0);
	count = 0;
	tmp = stack;
	while (1)
	{
		count++;
		tmp = tmp->next;
		if (tmp == stack)
			break ;
	}
	return (count);
}

void	set_index(t_stack *stack_a)
{
	t_stack	*current;
	t_stack	*compare;
	int		count;

	if (!stack_a)
		return ;
	current = stack_a;
	while (1)
	{
		count = 0;
		compare = stack_a;
		while (1)
		{
			if (compare->value < current->value)
				count++;
			compare = compare->next;
			if (compare == stack_a)
				break ;
		}
		current->index = count;
		current = current->next;
		if (current == stack_a)
			break ;
	}
}
