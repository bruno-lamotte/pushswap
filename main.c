/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:22:33 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/30 03:02:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

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

void	print_stack(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	if (!stack) return ;
	while (1)
	{
		printf("Value: %7d | Index: %7d\n", tmp->value, tmp->index);
		tmp = tmp->next;
		if (tmp == stack)
			break ;
	}
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

void	push_swap(t_stack **a)
{
	int		size;
	t_stack	*b;
	t_list	*instructions;

	instructions = NULL;
	size = get_stack_size(*a);
	b = NULL;
	if (size <= 1)
		return ;
	if (size == 2)
	{
		if ((*a)->index > (*a)->next->index)
			sa(a, &instructions);
	}
	else if (size == 3)
		sort_three(a, &instructions);
	else if (size <= 5)
		sort_five(a, &b, &instructions);
	else
		algo(a, &b, &instructions);
	free_stack(&b);
	print_list(instructions);
	free_list(instructions);
}

// void	push_swap(t_stack **a)
// {
// 	int		size;
// 	t_stack	*b;

// 	size = get_stack_size(*a);
// 	b = NULL;
// 	if (size <= 1)
// 		return ;
// 	if (size == 2)
// 	{
// 		if ((*a)->index > (*a)->next->index)
// 			sa(a);
// 	}
// 	else if (size == 3)
// 		sort_three(a);
// 	else if (size <= 5)
// 		sort_five(a, &b);
// 	else
// 		algo(a, &b);
// 	free_stack(&b);
// }

int	main(int ac, char **av)
{
	t_stack	*a;

	a = NULL;
	if (ac < 2)
		return (0);
	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
		if (!av)
			return (0);
	}
	else
		av++;
	if (!parsing(av, &a))
	{
		if (ac == 2)
			free(av);
		return (free_stack(&a), write(2, "Error\n", 6));
	}
	push_swap(&a);
	print_stack(a);
	free_stack(&a);
	return (0);
}
