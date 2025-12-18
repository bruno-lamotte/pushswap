/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:58:16 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/18 00:15:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack **stack)
{
	if (!*stack)
		return ;
	*stack = (*stack)->next;
}

void	ra(t_stack **a, t_list **instructions)
{
	rotate(a);
	ft_lstadd_back(&instructions, ft_lstnew("ra"));
}

void	rb(t_stack **b, t_list **instructions)
{
	rotate(b);
	ft_lstadd_back(&instructions, ft_lstnew("rb"));
}

void	rr(t_stack **a, t_stack **b, t_list **instructions)
{
	rotate(a);
	rotate(b);
	ft_lstadd_back(&instructions, ft_lstnew("rr"));
}
