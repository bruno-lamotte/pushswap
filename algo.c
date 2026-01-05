/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 04:16:10 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/05 04:51:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void k_sorting(t_stack **a, t_stack **b, t_list **instructions)
{
	int chunk_size;
	int initial_chunk;
    int threshold;
    int moved;

    threshold = 0;
    chunk_size = get_stack_size(*a) / 6;
    //chunk_size = 32;
    if (chunk_size < 6)
        chunk_size = 6;
    initial_chunk = chunk_size;
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
                ra(a, instructions);
        }
        if (chunk_size > initial_chunk / 2 && chunk_size > get_stack_size(*a) / 5)
            chunk_size = chunk_size * 6 / 7;
        else if (chunk_size > 2)
            chunk_size--;
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
    start = *b;
    current = *b;
    f_cost = 0;
    while (current != target)
    {
        current = current->next;
        f_cost++;
        if (current == start)
            break ;
    }
    current = *b;
    b_cost = 0;
    while (current != target)
    {
        current = current->prev;
        b_cost++;
        if (current == start)
            break ;
    }
    if (f_cost <= b_cost)
        return (f_cost);
    return (-b_cost);
}

int mouv_cost_a(t_stack **a, t_stack *target)
{
    int f_cost;
    int b_cost;
    t_stack *current;
    t_stack *start;
    int size;

    if (!a || !*a || !target)
        return (0);
    size = get_stack_size(*a);
    start = *a;
    current = *a;
    f_cost = 0;
    while (f_cost < size && current->value < target->value)
    {
        current = current->next;
        f_cost++;
        if (current == start)
            break ;
    }
    b_cost = size - f_cost;
    if (f_cost < b_cost)
        return (f_cost);
    else
        return (-b_cost);
}

int find_insert_pos(t_stack **a, int value)
{
    t_stack *current;
    t_stack *min_node;
    t_stack *max_node;
    int min_pos;
    int size;
    int i;

    current = *a;
    min_node = *a;
    max_node = *a;
    min_pos = 0;
    size = get_stack_size(*a);
    i = 0;
    while (i < size)
    {
        if (current->value < min_node->value)
        {
            min_node = current;
            min_pos = i;
        }
        if (current->value > max_node->value)
            max_node = current;
        current = current->next;
        i++;
    }
    if (value < min_node->value || value > max_node->value)
        return (min_pos);
    current = *a;
    i = 0;
    while (i < size)
    {
        if (current->value < value && current->next->value > value)
            return (i + 1);
        current = current->next;
        i++;
    }
    return (min_pos);
}

void insert_sorted(t_stack **a, t_stack **b, t_list **instructions)
{
    int size;
    int pos;
    int moves;

    if (!*b)
        return ;
    if (!*a)
    {
        pa(a, b, instructions);
        return ;
    }
    size = get_stack_size(*a);
    pos = find_insert_pos(a, (*b)->value);
    if (pos <= size / 2)
    {
        moves = pos;
        while (moves > 0)
        {
            ra(a, instructions);
            moves--;
        }
    }
    else
    {
        moves = size - pos;
        while (moves > 0)
        {
            rra(a, instructions);
            moves--;
        }
    }
    pa(a, b, instructions);
}

void reintegrate(t_stack **a, t_stack **b, int threshold, t_list **instructions)
{
    t_stack *current;
    t_stack *best_target;
    int best_total_cost;
    int total_cost;
    int steps;
    int size;
    int i;

    if (!*b)
        return ;
    current = *b;
    best_target = *b;
    best_total_cost = 2147483647;
    size = get_stack_size(*b);
    i = 0;
    while (i < size)
    {
        if (mouv_cost_a(a, current) * mouv_cost_b(b, current) >= 0)
            total_cost = ft_max(ft_abs(mouv_cost_b(b, current)), ft_abs(mouv_cost_a(a, current)));
        else
            total_cost = ft_abs(mouv_cost_b(b, current)) + ft_abs(mouv_cost_a(a, current));
        if (current->next && current->index == current->next->index + 1)
            total_cost--;
            //total_cost -= cost_heuristic(current, threshold, get_stack_size(*a));
        if (total_cost < best_total_cost)
        {
            best_total_cost = total_cost;
            best_target = current;
        }
        current = current->next;
        i++;
    }
    steps = mouv_cost_b(b, best_target);
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
    (void)threshold;
    insert_sorted(a, b, instructions);
}

void algo(t_stack **a, t_stack **b, t_list **instructions)
{
    int min_pos;
    int size;
    int i;
    t_stack *current;
    t_stack *min_node;
    int threshold;

    threshold = 0;
    k_sorting(a, b, instructions);
    while (*b)
    {
        reintegrate(a, b, threshold, instructions);
        threshold++;
    }
    size = get_stack_size(*a);
    current = *a;
    min_node = *a;
    min_pos = 0;
    i = 0;
    while (i < size)
    {
        if (current->value < min_node->value)
        {
            min_node = current;
            min_pos = i;
        }
        current = current->next;
        i++;
    }
    if (min_pos <= size / 2)
    {
        while (min_pos > 0)
        {
            ra(a, instructions);
            min_pos--;
        }
    }
    else
    {
        min_pos = size - min_pos;
        while (min_pos > 0)
        {
            rra(a, instructions);
            min_pos--;
        }
    }
}
