/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:13:58 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/15 03:14:50 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// push.c

// Fonction interne pour détacher le noeud du sommet de la pile
static t_stack	*pop_node(t_stack **stack)
{
	t_stack	*node;

	if (!*stack)
		return (NULL);
	node = *stack;
	if ((*stack)->next == *stack) // Cas : 1 seul élément
	{
		*stack = NULL;
	}
	else // Cas : Plusieurs éléments
	{
		*stack = node->next; // La tête avance
		node->prev->next = node->next; // Le dernier pointe sur le nouveau premier
		node->next->prev = node->prev; // Le nouveau premier pointe sur le dernier
	}
    // On isole le noeud pour qu'il soit propre avant réinsertion
    node->next = node; 
    node->prev = node;
	return (node);
}

// Fonction interne pour attacher un noeud au sommet
static void	push_node(t_stack **stack, t_stack *new_node)
{
	t_stack	*tail;

	if (!*stack) // Cas : Destination vide
	{
		*stack = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
	}
	else // Cas : Destination existante
	{
		tail = (*stack)->prev;
		
        // Insertion entre tail et head
		tail->next = new_node;
		new_node->prev = tail;
		new_node->next = *stack;
		(*stack)->prev = new_node;
		
        // Le nouveau devient la tête
		*stack = new_node;
	}
}

void	pa(t_stack **a, t_stack **b, int print)
{
	t_stack	*node;

	if (!*b)
		return ;
	node = pop_node(b);
	push_node(a, node);
	write(1, "pa\n", 3);
}

void	pb(t_stack **a, t_stack **b)
{
	t_stack	*node;

	if (!*a)
		return ;
	node = pop_node(a);
	push_node(b, node);
	write(1, "pb\n", 3);
}
