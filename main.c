/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:22:33 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/12 17:22:37 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_stack(t_stack **stack)
{
	t_stack	*tmp;
	t_stack	*current;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}
/*
void print_stack(t_stack *stack)
{
    t_stack *tmp = stack;

    if (!stack) return;
    while (1)
    {
        ft_printf("Value: %10d | Index: %10d\n", tmp->value, tmp->index);
        tmp = tmp->next;
        if (tmp == stack)
            break;
    }
}
*/
int	main(int ac, char **av)
{
	t_stack	*a;

	a = NULL;
	if (ac < 2)
		return (0);
	if (ac == 2)
	{
		av = ft_split(av[1]);
		if (!av)
			return (NULL);
	}
	if (!parsing(av, &a))
		return (free_stack(&a), write(2, "Error\n", 6));
	pushswap(ac, &a);
	free_stack(&a);
	return (0);
}
