/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ksorting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:57:15 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 02:35:39 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	adapt_chunk_size(int chunk_size, t_stack **a)
{
	if (chunk_size > get_stack_size(*a) / 5)
		chunk_size = chunk_size * 6 / 7;
	if (chunk_size < 1)
		return (1);
	return (chunk_size);
}

void	k_sorting(t_stack **a, t_stack **b, t_list **instructions, int size)
{
	int	chunk_size;
	int	threshold;
	int	moved;

	threshold = 0;
	chunk_size = size / 6;
	while (*a)
	{
		moved = 0;
		while (*a && moved < chunk_size)
		{
			if ((*a)->index <= threshold + chunk_size)
			{
				pb(a, b, instructions);
				if ((*b)->index <= threshold)
					rb(b, instructions);
				threshold++;
				moved++;
			}
			else
				ra(a, instructions, 1);
		}
		chunk_size = adapt_chunk_size(chunk_size, a);
	}
}
