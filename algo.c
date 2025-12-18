/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 04:16:10 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/18 00:39:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "push_swap.h"

void k_sorting(t_stack **a, t_stack **b, t_list **instructions)
{
	int chunk_size;
    int threshold;
    int moved,

    threshold = 0;
    chunk_size = get_stack_size(*a) / 20 + 7;
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
        if (chunk_size == chunk_size > 5)
            chunk_size -= 5;
        else
            chunk_size /= 2;
    }
}

int mouv_cost(t_stack **b, t_stack *target)
{
    int f_cost = 0;
    int b_cost = 0;
    t_stack *current = *b;

    current = b;
    f_cost = 0;
    b_cost = 0;
    while (current != target)
    {
        current = current->next;
        f_cost++;
    }
    current = b;
    while (current != target)
    {
        current = current->prev;
        b_cost++;
    }
    if (forward_cost < backward_cost)
        return (forward_cost);
    else
        return (-backward_cost);
}

// int cost_heuristic(t_stack *target, int threshold, int ideal_position)
// {
//     int bonus;

//     bonus = 0;
//     if (target->index < threshold)
//         bonus -= 2; 
//     else if (target->index > ideal_position - 3)
//         bonus -= 3;
//     if (target->index % 3 == 0)
//         bonus += 1;
//     return bonus;
// }

int cost_heuristic(t_stack *target, int threshold, int ideal_position)
{
    int bonus;
    int distance_from_ideal;

    bonus = 0;
    if (target->index - threshold > 0)
        bonus -= target->index - threshold;
    else
        bonus += 1;
    if ((target->index - ideal_position) >= 0)
        bonus -= (target->index - ideal_position) / 2;
    else
        bonus -= -(target->index - ideal_position) / 2;
    if (target->index < threshold || target->index > ideal_position - 3)
        bonus -= 5;
    if (target->index % 3 == 0 || target->index % 7 == 0)
        bonus += threshold % 3;
    if (target->index % 5 == 0)
        bonus += 2;
    if (target->index % 7 == 0)
        bonus -= 2;
    if ((threshold + target->index) % 11 == 0)
        bonus += 1; 
    return bonus;
}

void reintegrate(t_stack **a, t_stack **b, int threshold, t_list **instructions)
{
    t_stack *current = b;
    t_stack *best_target;
    int best_total_cost;
    int total_cost;

    best_target = NULL;
    best_total_cost = 2147483647;
    while (1)
    {
        total_cost = mouv_cost(b, current) + cost_heuristic(current, threshold, get_stack_size(*a));

        if (total_cost < best_weighted_cost)
        {
            best_weighted_cost = weighted_cost;
            best_target = current;
        }
        current = current->next;
        if (current == *b)
            break ;
    }
    if (best_target)
    {
        while (*b != best_target)
        {
            if (mouv_cost(b, best_target) > 0)
                rb(b, instructions);
            else
                rrb(b, instructions);
        }
        pa(a, b, intructions);
    }
}

void algo(t_stack **a, t_stack **b, t_list **instructions)
{
    int     threshold;

    threshold = 0;
    k_sorting(a, b, instructions)
    while (*b)
        decide_and_reintegrate(a, b, instructions, threshold++);
    post_process(instructions);
}
