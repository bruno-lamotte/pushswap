#include "push_swap.h"

static void	print_instr(char *instr)
{
	ft_putstr_fd(instr, 1);
	ft_putchar_fd('\n', 1);
}

static int	match_instr(t_list *node, char *instr1, char *instr2)
{
	if (!node || !node->content)
		return (0);
	if (!ft_strncmp((char *)node->content, instr1, 4) ||
		!ft_strncmp((char *)node->content, instr2, 4))
		return (1);
	return (0);
}

void print_multiple_instr(t_list **current, char *instr1, char *instr2, char *instr3)
{
	int instr1_count;
	int instr2_count;

	instr1_count = 0;
	instr2_count = 0;
	while (match_instr(*current, instr1, instr2))
	{
		if (!ft_strncmp((char *)(*current)->content, instr1, 4))
			instr1_count++;
		else
			instr2_count++;
		*current = (*current)->next;
	}
	while (instr1_count > 0 && instr2_count > 0)
	{
		print_instr(instr3);
		instr1_count--;
		instr2_count--;
	}
	while (instr1_count-- > 0)
		print_instr(instr1);
	while (instr2_count-- > 0)
		print_instr(instr2);
}

int is_cancelable(t_list *current)
{
	if (!current || !current->next || !current->content || !current->next->content)
		return (0);
	if ((!ft_strncmp((char *)current->content, "pa", 3) && !ft_strncmp((char *)current->next->content, "pb", 3)) ||
		(!ft_strncmp((char *)current->content, "pb", 3) && !ft_strncmp((char *)current->next->content, "pa", 3)) ||
		(!ft_strncmp((char *)current->content, "ra", 3) && !ft_strncmp((char *)current->next->content, "rra", 4)) ||
		(!ft_strncmp((char *)current->content, "rb", 3) && !ft_strncmp((char *)current->next->content, "rrb", 4)) ||
		(!ft_strncmp((char *)current->content, "rra", 4) && !ft_strncmp((char *)current->next->content, "ra", 3)) ||
		(!ft_strncmp((char *)current->content, "rrb", 4) && !ft_strncmp((char *)current->next->content, "rb", 3)))
		return (1);
	return (0);
}

static int	check_swap_optim(t_list **current)
{
	char	*s1;
	char	*s2;
	char	*s3;

	if (!*current || !(*current)->next || !(*current)->next->next)
		return (0);
	s1 = (char *)(*current)->content;
	s2 = (char *)(*current)->next->content;
	s3 = (char *)(*current)->next->next->content;
	if (s1 && s2 && s3)
	{
		if (!ft_strncmp(s1, "ra", 3) && !ft_strncmp(s2, "pb", 3) && !ft_strncmp(s3, "rra", 4))
		{
			print_instr("sa");
			print_instr("pb");
			*current = (*current)->next->next->next;
			return (1);
		}
		if (!ft_strncmp(s1, "rb", 3) && !ft_strncmp(s2, "pa", 3) && !ft_strncmp(s3, "rrb", 4))
		{
			print_instr("sb");
			print_instr("pa");
			*current = (*current)->next->next->next;
			return (1);
		}
	}
	return (0);
}

void print_list(t_list *instructions)
{
	t_list *current;

	current = instructions;
	while (current)
	{
		if (check_swap_optim(&current))
			continue ;
		if (is_cancelable(current))
			current = current->next->next;
		else if (current->content && (!ft_strncmp((char *)current->content, "ra", 3) || !ft_strncmp((char *)current->content, "rb", 3)))
			print_multiple_instr(&current, "ra", "rb", "rr");
		else if (current->content && (!ft_strncmp((char *)current->content, "rra", 4) || !ft_strncmp((char *)current->content, "rrb", 4)))
			print_multiple_instr(&current, "rra", "rrb", "rrr");
		else
		{
			if (current->content)
				print_instr((char *)current->content);
			current = current->next;
		}
	}
}

void add_instruction(t_list **instructions, char *instr)
{
	t_list *new;
	t_list *tmp;
	char *content;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	content = ft_strdup(instr);
	if (!content)
	{
		free(new);
		return ;
	}
	new->content = content;
	new->next = NULL;
	if (!*instructions)
		*instructions = new;
	else
	{
		tmp = *instructions;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
