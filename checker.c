/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 03:15:00 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 03:51:12 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *a)
{
	t_stack	*tmp;

	if (!a)
		return (1);
	tmp = a;
	while (tmp->next != a)
	{
		if (tmp->value > tmp->next->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	exec_instr(char *line, t_stack **a, t_stack **b)
{
	if (!ft_strncmp(line, "sa\n", 3))
		sa(a, NULL);
	else if (!ft_strncmp(line, "sb\n", 3))
		sb(b, NULL);
	else if (!ft_strncmp(line, "ss\n", 3))
		ss(a, b, NULL);
	else if (!ft_strncmp(line, "pa\n", 3))
		pa(a, b, NULL);
	else if (!ft_strncmp(line, "pb\n", 3))
		pb(a, b, NULL);
	else if (!ft_strncmp(line, "ra\n", 3))
		ra(a, NULL, 0);
	else if (!ft_strncmp(line, "rb\n", 3))
		rb(b, NULL);
	else if (!ft_strncmp(line, "rr\n", 3))
		rr(a, b, NULL);
	else if (!ft_strncmp(line, "rra\n", 4))
		rra(a, NULL, 0);
	else if (!ft_strncmp(line, "rrb\n", 4))
		rrb(b, NULL);
	else if (!ft_strncmp(line, "rrr\n", 4))
		rrr(a, b, NULL);
	else
		return (0);
	return (1);
}

int	read_and_exec(t_stack **a, t_stack **b)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (!exec_instr(line, a, b))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;

	(1 && (a = NULL), (b = NULL));
	if (ac < 2)
		return (0);
	av = get_args(ac, av);
	if (!av || !*av)
		return (free_split(av), write(2, "Error\n", 6));
	if (!parsing(av, &a))
		return (free_split(av), free_stack(&a), write(2, "Error\n", 6));
	free_split(av);
	if (!read_and_exec(&a, &b))
	{
		get_next_line(-1);
		return (free_stack(&a), free_stack(&b), write(2, "Error\n", 6));
	}
	if (is_sorted(a) && !b)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(&a);
	free_stack(&b);
	get_next_line(-1);
	return (0);
}
