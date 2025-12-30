/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:00:21 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/30 03:02:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rev_rotate(t_stack **stack)
{
	if (!*stack)
		return ;
	*stack = (*stack)->prev;
}

void	rra(t_stack **a, t_list **instructions)
{
	rev_rotate(a);
	ft_lstadd_back(instructions, ft_lstnew(ft_strdup("rra")));
}

void	rrb(t_stack **b, t_list **instructions)
{
	rev_rotate(b);
	ft_lstadd_back(instructions, ft_lstnew(ft_strdup("rrb")));
}

void	rrr(t_stack **a, t_stack **b, t_list **instructions)
{
	rev_rotate(a);
	rev_rotate(b);
	ft_lstadd_back(instructions, ft_lstnew(ft_strdup("rrr")));
}
// void	rra(t_stack **a)
// {
// 	rev_rotate(a);
// 	write(1, "rra\n", 4);
// }

// void	rrb(t_stack **b)
// {
// 	rev_rotate(b);
// 	write(1, "rrb\n", 4);
// }

// void	rrr(t_stack **a, t_stack **b)
// {
// 	rev_rotate(a);
// 	rev_rotate(b);
// 	write(1, "rrr\n", 4);
// }