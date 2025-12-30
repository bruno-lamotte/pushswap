/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:58:16 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/29 21:09:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack **stack)
{
	if (!*stack)
		return ;
	*stack = (*stack)->next;
}

// void	ra(t_stack **a, t_list **instructions)
// {
// 	rotate(a);
// 	ft_lstadd_back(&instructions, ft_lstnew("ra"));
// }

// void	rb(t_stack **b, t_list **instructions)
// {
// 	rotate(b);
// 	ft_lstadd_back(&instructions, ft_lstnew("rb"));
// }

// void	rr(t_stack **a, t_stack **b, t_list **instructions)
// {
// 	rotate(a);
// 	rotate(b);
// 	ft_lstadd_back(&instructions, ft_lstnew("rr"));
// }
void	ra(t_stack **a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

void	rb(t_stack **b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

void	rr(t_stack **a, t_stack **b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}