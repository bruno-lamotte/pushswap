/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:15:02 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 03:27:35 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	isvalid(char *arg)
{
	if (!arg || !*arg)
		return (0);
	while (*arg)
	{
		if (!ft_isdigit(*arg) && !(*arg == '-'))
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
			if (ft_strncmp(arg, "-2147483648", 11) > 0)
				return (0);
		return (1);
	}
	if (ft_strlen(arg) > 10)
		return (0);
	if (ft_strlen(arg) == 10)
		if (ft_strncmp(arg, "2147483647", 10) > 0)
			return (0);
	return (1);
}

int	isdouble(t_stack *a, long nb)
{
	t_stack	*tmp;

	if (!a)
		return (0);
	tmp = a;
	while (1)
	{
		if (tmp->value == nb)
			return (1);
		tmp = tmp->next;
		if (tmp == a)
			break ;
	}
	return (0);
}

int	parsing(char **av, t_stack **a)
{
	int		i;
	t_stack	*new;
	long	nbr;

	i = 0;
	while (av[i])
	{
		if (!isvalid(av[i]) || !is_int_limits(av[i]))
			return (0);
		nbr = ft_atoi(av[i]);
		if (isdouble(*a, nbr))
			return (0);
		new = ft_new_node(nbr);
		add_back(a, new);
		i++;
	}
	set_index(*a);
	return (1);
}

char	**get_args(int ac, char **av)
{
	char	*tmp;
	char	*joined;

	if (ac == 2)
		return (ft_split(av[1], ' '));
	joined = ft_strdup("");
	while (*(++av) && joined)
	{
		if (!**av)
			return (free(joined), NULL);
		tmp = joined;
		joined = ft_strjoin(tmp, *av);
		free(tmp);
		if (!joined)
			return (NULL);
		tmp = joined;
		joined = ft_strjoin(tmp, " ");
		free(tmp);
	}
	if (!joined)
		return (NULL);
	tmp = joined;
	av = ft_split(tmp, ' ');
	free(tmp);
	return (av);
}
