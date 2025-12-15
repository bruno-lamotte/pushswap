/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 04:16:10 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/15 06:35:57 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int get_max_bits(t_stack **stack)
{
    t_stack *head;
    int     max;
    int     max_bits;

    head = *stack;
    max = head->index;
    max_bits = 0;
    while (1)
    {
        if (head->index > max)
            max = head->index;
        head = head->next;
        if (head == *stack)
            break;
    }
    while ((max >> max_bits) != 0)
        max_bits++;
    return (max_bits);
}
/*
void	radix_pass(t_stack **a, t_stack **b, int shift)
{
	int	size;
	int	i;
	int	val;
	int	count[4] = {};

	size = get_stack_size(*a);
	i = 0;
	while (i < size)
	{
		val = ((*a)->index >> shift) & 3;
		if (val == 0 && ++count[0])
			pb(a, b);
		else if (val == 1 && ++count[1])
		{
			pb(a, b);
			rb(b);
		}
		else
			ra(a);
		i++;
	}
	while (get_stack_size(*a) > 0)
	{
		val = ((*a)->index >> shift) & 3;
		if (val == 2 && ++count[2])
			pb(a, b);
		else if (val == 3 && ++count[3])
		{
			pb(a, b);
			rb(b);
		}
	}
	while (count[3]--)
	{
		rrb(b);
		pa(a, b);
	}
	while (count[2]--)
		pa(a, b);
	while (count[1]--)
	{
		rrb(b);
		pa(a, b);
	}
	while (count[0]--)
		pa(a, b);
}
*/
void	algo(t_stack **a, t_stack **b)
{
    int max_bits;
    int shift;

    max_bits = get_max_bits(a);
    shift = 0;
    while (shift < max_bits)
    {
        radix_pass(a, b, shift);
        shift += 2;
    }
}

