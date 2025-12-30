/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 04:16:10 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/30 00:57:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void k_sorting(t_stack **a, t_stack **b)
{
	int chunk_size;
    int threshold;
    int moved;

    threshold = 0;
    chunk_size = get_stack_size(*a) / 20 + 7;
    if (chunk_size < 1)
        chunk_size = 1;
    while (*a)
    {
        moved = 0;
        while (*a && moved < chunk_size)
        {
            if ((*a)->index <= threshold + chunk_size)
            {
                pb(a, b);
                if ((*b)->index <= threshold)
                    rb(b); 
                threshold++;
                moved++;
            }
            else
                ra(a);
        }
        // if (chunk_size >= 5)
        //     chunk_size -= 5;
        // else
        //     chunk_size /= 2;
        // if (chunk_size < 1)
        //     chunk_size = 1;
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

int cost_heuristic(t_stack *target, int threshold, int ideal_position)
{
//     int bonus;
    
//     bonus = 0;
//     if (target->index - threshold > 0)
//         bonus -= target->index - threshold;
//     else
//         bonus += 1;
//     if ((target->index - ideal_position) >= 0)
//         bonus -= (target->index - ideal_position) / 2;
//     else
//         bonus -= -(target->index - ideal_position) / 2;
//     if (target->index < threshold || target->index > ideal_position - 3)
//         bonus -= 5;
//     if (target->index % 3 == 0 || target->index % 7 == 0)
//         bonus += threshold % 3;
//     if (target->index % 5 == 0)
//         bonus += 2;
//     if (target->index % 7 == 0)
//         bonus -= 2;
//     if ((threshold + target->index) % 11 == 0)
//         bonus += 1; 
//     return bonus;
    (void)target;
    (void)threshold;
    (void)ideal_position;
    return 0;
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

void insert_sorted(t_stack **a, t_stack **b)
{
    int size;
    int pos;
    int moves;

    if (!*b)
        return ;
    if (!*a)
    {
        pa(a, b);
        return ;
    }
    size = get_stack_size(*a);
    pos = find_insert_pos(a, (*b)->value);
    if (pos <= size / 2)
    {
        moves = pos;
        while (moves > 0)
        {
            ra(a);
            moves--;
        }
    }
    else
    {
        moves = size - pos;
        while (moves > 0)
        {
            rra(a);
            moves--;
        }
    }
    pa(a, b);
}

void reintegrate(t_stack **a, t_stack **b, int threshold)
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
        total_cost = ft_abs(mouv_cost_b(b, current)) + ft_abs(mouv_cost_a(a, current) + cost_heuristic(current, threshold, get_stack_size(*a)));
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
            rb(b);
            steps--;
        }
        else
        {
            rrb(b);
            steps++;
        }
    }
    insert_sorted(a, b);
}

void algo(t_stack **a, t_stack **b)
{
    int min_pos;
    int size;
    int i;
    t_stack *current;
    t_stack *min_node;
    int threshold;

    k_sorting(a, b);
    while (*b)
        reintegrate(a, b, threshold++);
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
            ra(a);
            min_pos--;
        }
    }
    else
    {
        min_pos = size - min_pos;
        while (min_pos > 0)
        {
            rra(a);
            min_pos--;
        }
    }
}