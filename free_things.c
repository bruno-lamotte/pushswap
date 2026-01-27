/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 02:49:14 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 02:49:16 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_stack **stack)
{
	t_stack	*tmp;
	t_stack	*current;

	if (!stack || !*stack)
		return ;
	current = *stack;
	if (current->next == current)
	{
		free(current);
		*stack = NULL;
		return ;
	}
	current->prev->next = NULL;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_list(t_list *instructions)
{
	t_list	*tmp;

	while (instructions)
	{
		tmp = instructions->next;
		if (instructions->content)
			free(instructions->content);
		free(instructions);
		instructions = tmp;
	}
}
