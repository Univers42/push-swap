void print_array_stack(t_stack *stack, char name)
{
    ft_printf("%s%s╔══ Stack %c ══╗%s\n", BOLD, CYAN, name, RESET);
    if (!stack || stack->element_count == 0)
    {
        ft_printf("%s║  (empty)    ║%s\n", DIM, RESET);
        ft_printf("%s╚═════════════╝%s\n\n", CYAN, RESET);
        return;
    }
    
    for (int i = 0; i < stack->element_count; i++)
    {
        ft_printf("%s║%s %s[%s%d%s]%s      %s║%s\n", 
                  CYAN, RESET, YELLOW, BRIGHT_YELLOW, 
                  stack->stack[i], YELLOW, RESET, CYAN, RESET);
    }
    ft_printf("%s╚═════════════╝%s\n\n", CYAN, RESET);
}

void print_both_array_stacks(t_stack *stack_a, t_stack *stack_b)
{
    // Calculate dynamic widths based on content
    int max_width_a = 10;  // Minimum width
    int max_width_b = 10;  // Minimum width
    
    // Find maximum width needed for stack A
    for (int i = 0; i < stack_a->element_count; i++)
    {
        char temp[20];
        sprintf(temp, "[%d]", stack_a->stack[i]);
        int len = strlen(temp);
        if (len > max_width_a)
            max_width_a = len;
    }
    
    // Find maximum width needed for stack B
    for (int i = 0; i < stack_b->element_count; i++)
    {
        char temp[20];
        sprintf(temp, "[%d]", stack_b->stack[i]);
        int len = strlen(temp);
        if (len > max_width_b)
            max_width_b = len;
    }
    
    // Add some padding
    max_width_a += 2;
    max_width_b += 2;
    
    int total_width = max_width_a + max_width_b + 8; // 8 for borders and spacing
    
    // Top border
    ft_printf("%s+", BOLD);
    for (int i = 0; i < total_width; i++)
        ft_printf("=");
    ft_printf("+%s\n", RESET);
    
    // Header
    ft_printf("%s|%s  %s🅰 Stack A%s", BLUE, RESET, BRIGHT_GREEN, RESET);
    int header_padding = max_width_a - 9;  // 9 is length of "🅰 Stack A"
    for (int i = 0; i < header_padding; i++)
        ft_printf(" ");
    
    ft_printf("%s🅱 Stack B%s", BRIGHT_MAGENTA, RESET);
    header_padding = max_width_b - 9;  // 9 is length of "🅱 Stack B"
    for (int i = 0; i < header_padding; i++)
        ft_printf(" ");
    ft_printf("  %s|%s\n", BLUE, RESET);
    
    // Separator
    ft_printf("%s+", BLUE);
    for (int i = 0; i < total_width; i++)
        ft_printf("=");
    ft_printf("+%s\n", RESET);
    
    // Stack contents
    int max_elements = (stack_a->element_count > stack_b->element_count) ? 
                       stack_a->element_count : stack_b->element_count;
    
    for (int i = 0; i < max_elements; i++)
    {
        ft_printf("%s|%s  ", BLUE, RESET);
        
        // Stack A element
        if (i < stack_a->element_count)
        {
            ft_printf("%s[%d]%s", BRIGHT_YELLOW, stack_a->stack[i], RESET);
            char temp[20];
            sprintf(temp, "[%d]", stack_a->stack[i]);
            int padding = max_width_a - strlen(temp);
            for (int j = 0; j < padding; j++)
                ft_printf(" ");
        }
        else
        {
            for (int j = 0; j < max_width_a; j++)
                ft_printf(" ");
        }
        
        // Stack B element
        if (i < stack_b->element_count)
        {
            ft_printf("%s[%d]%s", BRIGHT_MAGENTA, stack_b->stack[i], RESET);
            char temp[20];
            sprintf(temp, "[%d]", stack_b->stack[i]);
            int padding = max_width_b - strlen(temp);
            for (int j = 0; j < padding; j++)
                ft_printf(" ");
        }
        else
        {
            for (int j = 0; j < max_width_b; j++)
                ft_printf(" ");
        }
        
        ft_printf("  %s|%s\n", BLUE, RESET);
    }
    
    // Bottom border
    ft_printf("%s+", BLUE);
    for (int i = 0; i < total_width; i++)
        ft_printf("=");
    ft_printf("+%s\n", RESET);
}

void show_frame(t_ps *ps, const char *operation)
{
    t_test_context *ctx = get_test_context();
    
    ft_printf("\033[2J\033[H"); // Clear screen
    
    if (operation)
        ft_printf("%s🔄 %s%s\n", YELLOW, operation, RESET);
    
    print_both_array_stacks(&ps->stack_a, &ps->stack_b);
    ft_printf("Size A: %d, Size B: %d\n", 
             ps->stack_a.element_count, ps->stack_b.element_count);
    
    if (ctx->delay_ms > 0)
        usleep(ctx->delay_ms * 1000);
}
