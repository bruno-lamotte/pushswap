/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:15:02 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/15 01:12:41 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	isvalid(char *arg)
{
	if (!arg)
		return (0);
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	is_int_limits(char *arg)
{
	if (!arg)
		return (0);
	if (*arg == '-')
	{	
		if (ft_strlen(arg) > 11)
			return (0);
		if (ft_strlen(arg) == 11)
			if (ft_strncmp("-2147483648", arg) > 0)
				return (0);
		return (1);
	}
	if (ft_strlen(arg) > 10)
		return (0);                                                          
	if (ft_strlen(arg) == 10)                                                
		if (ft_strncmp("2147483647", arg) > 0)
			return (0);
	return (1);
}

void	set_index(t_stack *stack_a)
{
	t_stack	*current;
	t_stack	*compare;
	int		count;

	if (!stack_a)
		return ;
	current = stack_a;
	while (1)
	{
		count = 0;
		compare = stack_a;
		while (1) 
		{
			if (compare->value < current->value)
				count++;
			compare = compare->next;
			if (compare == stack_a)
				break ;
		}
		current->index = count;
		current = current->next;
		if (current == stack_a)
			break ;
	}
}

int	check_duplicate(t_stack *a, int nb)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->value == nb)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	parsing(char **av, t_stack *a)
{
	int		i;
	t_stack	*new;

	i = 0;
	while (av[i])
	{
		if (!isvalid(av[i]) || !is_int_limits(av[i])) 
			return (0);
		nbr = ft_atoi(av[i]);
		if (isdouble(*a, nbr))
			return (0);
		new = new_node(nbr);
		add_back(a, new);
		i++;
	}
	set_index(a);
	return (1);
}
