/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:25:24 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/30 02:46:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <libft.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

int					parsing(char **av, t_stack **a);
t_stack				*ft_new_node(int value);
void				add_back(t_stack **stack, t_stack *new_node);
void				free_stack(t_stack **stack);
void				sa(t_stack **a, t_list **instructions);
void				sb(t_stack **b, t_list **instructions);
void				ss(t_stack **a, t_stack **b, t_list **instructions);
void				pa(t_stack **a, t_stack **b, t_list **instructions);
void				pb(t_stack **a, t_stack **b, t_list **instructions);
void				ra(t_stack **a, t_list **instructions);
void				rb(t_stack **b, t_list **instructions);
void				rr(t_stack **a, t_stack **b, t_list **instructions);
void				rra(t_stack **a, t_list **instructions);
void				rrb(t_stack **b, t_list **instructions);
void				rrr(t_stack **a, t_stack **b, t_list **instructions);
void				push_swap(t_stack **a);
void				sort_three(t_stack **a, t_list **instructions);
void				sort_five(t_stack **a, t_stack **b, t_list **instructions);
int					get_stack_size(t_stack *stack);
void				algo(t_stack **a, t_stack **b, t_list **instructions);
void				print_list(t_list *instructions);
void				add_instruction(t_list **instructions, char *instr);
int					is_cancelable(t_list *current);

#endif
