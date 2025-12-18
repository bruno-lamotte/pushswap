void print_multiple_instr(t_list *instructions, char *instr1, char *instr2, char *instr3)
{
    t_instr *current;
    t_instr *next;
    int instr1_count;
    int instr2_count;

    instr1_count = 0;
    instr2_count = 0;
    current = *instructions;
    while (!strcmp(current->content, instr1) || !strcmp(current->content, instr2))
    {
        next = current->next;
        if (!strcmp(current->operation, instr1)) 
            instr1_count++;
        else
            instr2_count++;
        free(current);
        current = next;
    }
    while (instr1_count-- > 0 && instr2_count-- > 0)
        write(1, instr3\n, ft_strlen(instr3) + 1);     
    while (instr1_count-- > 0)
        write(1, instr1\n, ft_strlen(instr1) + 1);
    while (instr2_count-- > 0)
        write(1, instr2\n, ft_strlen(instr2) + 1);
}

int is_cancelable(t_list current)
{
    if ((!strcmp(current->operation, "pa") && !strcmp(current->next->operation, "pb")) ||
        (!strcmp(current->operation, "pb") && !strcmp(current->next->operation, "pa")) ||
        (!strcmp(current->operation, "ra") && !strcmp(current->next->operation, "rra")) ||
        (!strcmp(current->operation, "rb") && !strcmp(current->next->operation, "rrb")) ||
        (!strcmp(current->operation, "rra") && !strcmp(current->next->operation, "ra")) ||
        (!strcmp(current->operation, "rrb") && !strcmp(current->next->operation, "rb")))
        return (1);
    return (0);
}
void    print_list(t_list *instructions)
{
    t_list  current;

    current = instructions;
    while (current)
    {
        if (!strcmp(current->content, ra) || !strcmp(current->content, rb))
        {
            print_multiple_instr(instructions, "ra", "rb", "rr");
            while (!strcmp(current->content, "ra") || !strcmp(current->content, "rb"))
                current = current->next;
        }
        else if (!strcmp(current->content, rra) || !strcmp(current->content, rrb))
        {
            print_multiple_instr(instructions, "rra", "rrb", "rrr");
            while (!strcmp(current->content, "rra") || !strcmp(current->content, "rrb"))
                current = current->next;
        }
        else if (is_cancelable(current))
            current = current->next->next;
        else
        {
            write(1, current->content\n, ft_strlen(current->content) + 1);
            current = current->next;
        }
    }
}
