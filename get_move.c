/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:59:55 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 01:59:56 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#define CANDIDATES 1

void	keep_bests_mouvs(t_mouv new_mouv, t_mouv *mouvs)
{
	int	i;
	int	j;

	i = 0;
	while (i < CANDIDATES)
	{
		if (new_mouv.total_cost < mouvs[i].total_cost)
		{
			j = CANDIDATES - 1;
			while (j > i)
			{
				mouvs[j] = mouvs[j - 1];
				j--;
			}
			mouvs[i] = new_mouv;
			break ;
		}
		i++;
	}
}

void	inititalize_mouvs(t_mouv *mouvs)
{
	int	i;

	i = CANDIDATES;
	while (i--)
	{
		mouvs[i].total_cost = 2147483647;
		mouvs[i].cost_b = 0;
		mouvs[i].cost_a = 0;
	}
}

void	get_best_combi(int totals[4], t_mouv *best_for_item, int costs[4][2])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (totals[i] < best_for_item->total_cost)
		{
			best_for_item->total_cost = totals[i];
			best_for_item->cost_a = costs[i][0];
			best_for_item->cost_b = costs[i][1];
		}
		i++;
	}
}

void	try_combi(t_stack *a, t_stack *b, t_stack *current,
		t_mouv *best_for_item)
{
	int	costs[4][2];
	int	totals[4];
	int	size_a;

	size_a = get_stack_size(a);
	costs[0][0] = mouv_cost_a(&a, current, size_a, 1);
	costs[0][1] = mouv_cost_b(&b, current, 1);
	totals[0] = ft_max(costs[0][0], costs[0][1]);
	costs[1][0] = mouv_cost_a(&a, current, size_a, 0);
	costs[1][1] = mouv_cost_b(&b, current, 0);
	totals[1] = ft_max(ft_abs(costs[1][0]), ft_abs(costs[1][1]));
	costs[2][0] = mouv_cost_a(&a, current, size_a, 1);
	costs[2][1] = mouv_cost_b(&b, current, 0);
	totals[2] = costs[2][0] + ft_abs(costs[2][1]);
	costs[3][0] = mouv_cost_a(&a, current, size_a, 0);
	costs[3][1] = mouv_cost_b(&b, current, 1);
	totals[3] = ft_abs(costs[3][0]) + costs[3][1];
	best_for_item->total_cost = 2147483647;
	get_best_combi(totals, best_for_item, costs);
}

void	get_best_mouvs(t_stack *a, t_stack *b, t_mouv *mouvs, int size)
{
	t_stack	*current;
	t_mouv	tmp_mouv;

	inititalize_mouvs(mouvs);
	if (!b)
		return ;
	current = b;
	while (size--)
	{
		try_combi(a, b, current, &tmp_mouv);
		keep_bests_mouvs(tmp_mouv, mouvs);
		current = current->next;
	}
}
