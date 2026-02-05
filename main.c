/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:22:33 by blamotte          #+#    #+#             */
/*   Updated: 2026/02/05 16:34:01 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		if (!is_sorted(*a))
			algo(a, &b, &instructions);
	free_stack(&b);
	print_list(instructions);
	free_list(instructions);
}

int	main(int ac, char **av)
{
	t_stack	*a;

	a = NULL;
	if (ac < 2)
		return (0);
	av = get_args(ac, av);
	if (!av || !*av)
		return (free_split(av), write(2, "Error\n", 6));
	if (!parsing(av, &a))
	{
		free_split(av);
		return (free_stack(&a), write(2, "Error\n", 6));
	}
	push_swap(&a);
	free_stack(&a);
	free_split(av);
	return (0);
}
/*void	print_stack(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	if (!stack)
		return ;
	while (1)
	{
		printf("Value: %7d | Index: %7d\n", tmp->value, tmp->index);
		tmp = tmp->next;
		if (tmp == stack)
			break ;
	}
}*/
