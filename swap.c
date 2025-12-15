/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:05:53 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/15 03:11:59 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	swap(t_stack *stack)
{
	int	tmp_val;
	int	tmp_index;

	if (!stack || stack->next == stack)
		return ;
	tmp_val = stack->value;
	tmp_index = stack->index;
	stack->value = stack->next->value;
	stack->index = stack->next->index;
	stack->next->value = tmp_val;
	stack->next->index = tmp_index;
}

void	sa(t_stack **a)
{
	swap(*a);
	write(1, "sa\n", 3);
}

void	sb(t_stack **b)
{
	swap(*b);
	write(1,"sa\n", 3);
}

void	ss(t_stack **a, t_stack **b)
{
	swap(*a);
	swap(*b);
	write(1,"ss\n", 3);
}
