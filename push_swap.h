/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:25:24 by blamotte          #+#    #+#             */
/*   Updated: 2026/02/05 16:27:57 by blamotte         ###   ########.fr       */
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

typedef struct s_mouv
{
	int				cost_b;
	int				cost_a;
	int				total_cost;
}					t_mouv;

typedef struct s_eval
{
	t_stack			*temp_a;
	t_stack			*temp_b;
	int				i;
	int				total;
	int				best;
}					t_eval;

int					is_sorted(t_stack *a);
void				set_index(t_stack *stack_a);
int					parsing(char **av, t_stack **a);
t_stack				*ft_new_node(int value);
void				add_back(t_stack **stack, t_stack *new_node);
void				free_stack(t_stack **stack);
void				free_split(char **split);
void				free_list(t_list *instructions);
void				sa(t_stack **a, t_list **instructions);
void				sb(t_stack **b, t_list **instructions);
void				ss(t_stack **a, t_stack **b, t_list **instructions);
void				pa(t_stack **a, t_stack **b, t_list **instructions);
void				pb(t_stack **a, t_stack **b, t_list **instructions);
void				ra(t_stack **a, t_list **instructions, int print);
void				rb(t_stack **b, t_list **instructions);
void				rr(t_stack **a, t_stack **b, t_list **instructions);
void				rra(t_stack **a, t_list **instructions, int print);
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
void				k_sorting(t_stack **a, t_stack **b, t_list **ins, int size);
int					mouv_cost_b(t_stack **b, t_stack *target, int direction);
int					mouv_cost_a(t_stack **a, t_stack *t, int size, int dir);
void				mouv_up_in_b(int s, t_stack **a, t_stack **b, t_list **ins);
void				get_best_mouvs(t_stack *a, t_stack *b, t_mouv *m, int size);
t_stack				*copy_stack(t_stack *stack, int size);
int					evaluate_branch(t_stack *a, t_stack *b, int depth,
						int size);
int					match_instr(t_list *node, char *instr1, char *instr2);
void				print_instr(char *instr);
char				**get_args(int ac, char **av);

#endif
