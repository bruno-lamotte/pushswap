/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 04:16:10 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/06 17:25:43 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#define DEPTH 1
#define CANDIDATES 1

int adapt_chunk_size(int chunk_size, int initial_chunk, t_stack **a)
{
    if (chunk_size > initial_chunk / 2 && chunk_size > get_stack_size(*a) / 5)
        return (chunk_size * 6 / 7);
    else if (chunk_size > 2)
        return (--chunk_size);
    return (chunk_size);
}

void k_sorting(t_stack **a, t_stack **b, t_list **instructions, int size)
{
	int chunk_size;
	int initial_chunk;
    int threshold;
    int moved;

    threshold = 0;
    (1 && (chunk_size = size / 6), (initial_chunk = chunk_size));
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
        chunk_size = adapt_chunk_size(chunk_size, initial_chunk, a);
    }
}

int mouv_cost_b(t_stack **b, t_stack *target)
{
    int f_cost;
    int b_cost;
    t_stack *current;
    t_stack *start;

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
    if (f_cost <= b_cost)
        return (f_cost);
    return (-b_cost);
}

int find_insert_pos(t_stack **a, int value, int size)
{
    t_stack *current;
    t_stack *min_node;
    t_stack *max_node;
    int min_pos;
    int i;

    (1 && (current = *a), (min_node = *a), (max_node = *a), (min_pos = 0), (i = 0));
    while (i < size)
    {
        if (current->value < min_node->value)
            (1 && (min_node = current), (min_pos = i));
        if (current->value > max_node->value)
            max_node = current;
        (1 && (current = current->next), (i = i + 1));
    }
    if (value < min_node->value || value > max_node->value)
        return (min_pos);
    (1 && (current = *a), (i = 0));
    while (i < size)
    {
        if (current->value < value && current->next->value > value)
            return (i + 1);
        (1 && (current = current->next), (i = i + 1));
    }
    return (min_pos);
}
int mouv_cost_a(t_stack **a, t_stack *target, int size)
{
    int pos;

    if (!a || !*a || !target)
        return (0);
    pos = find_insert_pos(a, target->value, size);
    if (pos <= size / 2)
        return (pos);
    return (pos - size);
}

void insert_sorted(t_stack **a, t_stack **b, t_list **instructions, int size)
{
    int     pos;
    int     moves;
    int     print;

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

void	finish_b_and_push(int cost_b, t_stack **a, t_stack **b, t_list **inst)
{
	while (cost_b > 0)
	{
		rb(b, inst);
		cost_b--;
	}
	while (cost_b < 0)
	{
		rrb(b, inst);
		cost_b++;
	}
	pa(a, b, inst);
}
void	apply_move(t_stack **a, t_stack **b, int cost_a, int cost_b, t_list **inst)
{
	while (cost_a > 0 && cost_b > 0)
	{
		rr(a, b, inst);
		cost_a--;
		cost_b--;
	}
	while (cost_a < 0 && cost_b < 0)
	{
		rrr(a, b, inst);
		cost_a++;
		cost_b++;
	}
	while (cost_a > 0)
    {
		ra(a, inst, 1);
        cost_a--;
    }
	while (cost_a < 0)
    {
		rra(a, inst, 1);
        cost_a++;
    }
    finish_b_and_push(cost_b, a, b, inst);
}

t_stack *copy_stack(t_stack *stack, int size)
{
    t_stack *new_stack;
    t_stack *current;
    t_stack *new_node;
    int i;
    
    if (!stack)
        return (NULL);
    (1 && (new_stack = NULL), (current = stack), (i = 0));
    while (i < size)
    {
        new_node = malloc(sizeof(t_stack));
        if (!new_node)
            return (NULL);
        (1 && (new_node->value = current->value), (new_node->index = current->index));
        if (!new_stack)
            (1 && (new_stack = new_node), (new_node->next = new_node), (new_node->prev = new_node));
        else
        {
            (1 && (new_node->next = new_stack), (new_node->prev = new_stack->prev));
            (1 && (new_stack->prev->next = new_node), (new_stack->prev = new_node));
        }
        current = current->next;
        i++;
    }
    return (new_stack);
}

void	keep_bests_mouvs(int t_cost, int cost_a, int cost_b, t_mouv *mouvs)
{
	int	i;
	int	j;

	i = 0;
	while (i < CANDIDATES)
	{
		if (t_cost < mouvs[i].total_cost)
		{
			j = CANDIDATES - 1;
			while (j > i)
			{
				mouvs[j] = mouvs[j - 1];
				j--;
			}
			mouvs[i].total_cost = t_cost;
			mouvs[i].cost_a = cost_a;
			mouvs[i].cost_b = cost_b;
			return ;
		}
		i++;
	}
}

void    inititalize_mouvs(t_mouv *mouvs)
{
    int i;

    i = CANDIDATES;
    while (i--)
    {
        mouvs[i].total_cost = 2147483647;
        mouvs[i].cost_b = 0;
    }
}

static void	try_combinations(int *c_a, int *c_b, t_mouv *mouvs)
{
	int	tot;

	if (c_a[0] > c_b[0])
		tot = c_a[0];
	else
		tot = c_b[0];
	keep_bests_mouvs(tot, c_a[0], c_b[0], mouvs);
	if (ft_abs(c_a[1]) > ft_abs(c_b[1]))
		tot = ft_abs(c_a[1]);
	else
		tot = ft_abs(c_b[1]);
	keep_bests_mouvs(tot, c_a[1], c_b[1], mouvs);
	tot = c_a[0] + ft_abs(c_b[1]);
	keep_bests_mouvs(tot, c_a[0], c_b[1], mouvs);
	tot = ft_abs(c_a[1]) + c_b[0];
	keep_bests_mouvs(tot, c_a[1], c_b[0], mouvs);
}

void	get_best_mouvs(t_stack *a, t_stack *b, t_mouv *mouvs, int size_b)
{
	t_stack	*cur;
	int		c_a[2];
	int		c_b[2];
	int		i;
	int		size_a;

	inititalize_mouvs(mouvs);
	cur = b;
	i = 0;
	size_a = get_stack_size(a);
	while (i < size_b)
	{
		c_b[0] = i;
		c_b[1] = i - size_b;
		c_a[0] = find_insert_pos(&a, cur->value, size_a);
		c_a[1] = c_a[0] - size_a;
		try_combinations(c_a, c_b, mouvs);
		cur = cur->next;
		i++;
	}
}

int evaluate_branch(t_stack *a, t_stack *b, int depth, int size)
{
    t_mouv mouvs[CANDIDATES];
    int min_cost;
    int i;
    t_stack *temp_a;
    t_stack *temp_b;
    int total;
    
    if (!b || depth <= 0)
        return (0);
    get_best_mouvs(a, b, mouvs, size);
    if (depth == 1)
        return (mouvs[0].total_cost);
    min_cost = 2147483647;
    i = 0;
    while (i < CANDIDATES && mouvs[i].total_cost != 2147483647)
    {
        if (mouvs[i].total_cost >= min_cost)
        {
            i++;
            continue;
        }
        temp_a = copy_stack(a, get_stack_size(a));
        temp_b = copy_stack(b, size);
        apply_move(&temp_a, &temp_b, mouvs[i].cost_a, mouvs[i].cost_b, NULL);
        total = mouvs[i].total_cost + evaluate_branch(temp_a, temp_b, depth - 1, size - 1);       
        if (total < min_cost)
            min_cost = total;
        free_stack(&temp_a);
        free_stack(&temp_b);
        i++;
    }   
    return (min_cost);
}

void reintegrate(t_stack **a, t_stack **b, t_list **instructions, int size)
{
    t_mouv mouvs[CANDIDATES];
    int best_index;
    int best_cost;
    int i;
    int total;
    t_stack *temp_a;
    t_stack *temp_b;
    
    if (!*b)
        return ;
    if (!*a)
        return (pa(a, b, instructions));
    get_best_mouvs(*a, *b, mouvs, size);
    best_index = 0;
    best_cost = 2147483647;
    i = 0;
    while (i < CANDIDATES && mouvs[i].total_cost != 2147483647)
    {
        if (mouvs[i].total_cost >= best_cost)
        {
            i++;
            continue;
        }
        temp_a = copy_stack(*a, get_stack_size(*a));
        temp_b = copy_stack(*b, size);
        apply_move(&temp_a, &temp_b, mouvs[i].cost_a, mouvs[i].cost_b, NULL);
        total = mouvs[i].total_cost + evaluate_branch(temp_a, temp_b, DEPTH - 1, size - 1);
        if (total < best_cost)
            (1 && (best_cost = total), (best_index = i));   
        free_stack(&temp_a);
        free_stack(&temp_b);
        i++;
    }
    apply_move(a, b, mouvs[best_index].cost_a, mouvs[best_index].cost_b, instructions);
}

void    final_rotate(t_stack **a, t_list **instructions, int size)
{
    int min_pos;
    int i;
    t_stack *current;
    t_stack *min_node;
    
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

void algo(t_stack **a, t_stack **b, t_list **instructions)
{
    int size;

    size = get_stack_size(*a);
    k_sorting(a, b, instructions, size);
    while (*b)
    {
        reintegrate(a, b, instructions, get_stack_size(*b));
    }
    final_rotate(a, instructions, size);

}
