/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 02:00:50 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/27 02:02:17 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_instr(char *instr)
{
	ft_putstr_fd(instr, 1);
	ft_putchar_fd('\n', 1);
}

int	match_instr(t_list *node, char *instr1, char *instr2)
{
	if (!node || !node->content)
		return (0);
	if (!ft_strncmp((char *)node->content, instr1, 4)
		|| !ft_strncmp((char *)node->content, instr2, 4))
		return (1);
	return (0);
}
