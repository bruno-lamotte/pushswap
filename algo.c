/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 04:16:10 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/06 11:58:04 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int mouv_cost_a(t_stack **a, t_stack *target, int size)
{
    int f_cost;
    int b_cost;
    t_stack *current;
    t_stack *start;

    if (!a || !*a || !target)
        return (0);
    (1 && (start = *a), (current = *a), (f_cost = 0));
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

void insert_sorted(t_stack **a, t_stack **b, t_list **instructions, int print)
{
    int     pos;
    int     moves;
    int     size;
    
    size = get_stack_size(*a);
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

void    mouv_up_in_b(int steps, t_stack **a, t_stack **b, t_list **instructions)
{
    int print;
    
    print = instructions != 0;
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
    insert_sorted(a, b, instructions, print);
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

void    keep_bests_mouvs(int total_cost, int cost_b, t_mouv *mouvs)
{
    int i;
    int j;
    
    i = 1;
    while (i--)
    {
        
        if (total_cost < mouvs[i].total_cost)
        {
            j = 0;
            while (j > i)
            {
                mouvs[j] = mouvs[j - 1];
                j--;
            }
            mouvs[i].cost_b = cost_b;
            mouvs[i].total_cost = total_cost;
            return ;
        }
    }
}

void    inititalize_mouvs(t_mouv *mouvs)
{
    int i;

    i = 1;
    while (i--)
    {
        mouvs[i].total_cost = 2147483647;
        mouvs[i].cost_b = 0;
    }
}

void    get_best_mouvs(t_stack *a, t_stack *b, t_mouv *mouvs, int size)
{
    t_stack *current;
    int i;
    int cost_a;
    int cost_b;
    int total_cost;

    inititalize_mouvs(mouvs);
    if (!b)
        return;
    current = b;
    i = 0;
    while (i < size)
    {
        (1 && (cost_b = mouv_cost_b(&b, current)), (cost_a = mouv_cost_a(&a, current, get_stack_size(a))));
        if (cost_a * cost_b >= 0)
            total_cost = ft_max(ft_abs(cost_b), ft_abs(cost_a));
        else
            total_cost = ft_abs(cost_b) + ft_abs(cost_a);
        if (current->next && current->index == current->next->index + 1)
            total_cost--;
        keep_bests_mouvs(total_cost, cost_b, mouvs);
        current = current->next;
        i++;
    }
}

int evaluate_branch(t_stack *a, t_stack *b, int depth, int size)
{
    t_mouv mouvs[1];
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
    while (i < 1 && mouvs[i].total_cost != 2147483647)
    {
        temp_a = copy_stack(a, get_stack_size(a));
        temp_b = copy_stack(b, size);
        mouv_up_in_b(mouvs[i].cost_b, &temp_a, &temp_b, NULL);
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
    t_mouv mouvs[1];
    int best_index;
    int best_cost;
    int i;
    int total;
    t_stack *temp_a;
    t_stack *temp_b;
    
    if (!*b)
        return ;
    get_best_mouvs(*a, *b, mouvs, size);
    best_index = 0;
    best_cost = 2147483647;
    i = 0;
    while (i < 1 && mouvs[i].total_cost != 2147483647)
    {
        temp_a = copy_stack(*a, get_stack_size(*a));
        temp_b = copy_stack(*b, size);
        mouv_up_in_b(mouvs[i].cost_b, &temp_a, &temp_b, NULL);
        total = mouvs[i].total_cost + evaluate_branch(temp_a, temp_b, 0, size - 1);
        if (total < best_cost)
            (1 && (best_cost = total), (best_index = i));   
        free_stack(&temp_a);
        free_stack(&temp_b);
        i++;
    }
    mouv_up_in_b(mouvs[best_index].cost_b, a, b, instructions);
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
