/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:29:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 13:46:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

// Find maximum width needed for a stack
int find_max_width(t_stack *stack)
{
    int max_width = 15; // Minimum width
    char temp_str[50];
    
    if (!stack || stack->element_count == 0)
        return max_width;
    
    for (int i = 0; i < stack->element_count; i++)
    {
        sprintf(temp_str, "[%d]", stack->stack[i]);
        int current_width = strlen(temp_str);
        if (current_width > max_width)
            max_width = current_width;
    }
    return max_width;
}

void print_stack(t_stack *stack, char name)
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

// Count stack elements (for array-based stack)
int count_stack_elements(t_stack *stack)
{
    if (!stack)
        return 0;
    return stack->element_count;
}

void print_both_stacks(t_stack *stack_a, t_stack *stack_b)
{
    // Calculate dynamic widths based on actual content
    int max_width_a = 8;  // Minimum width
    int max_width_b = 8;  // Minimum width
    
    // Find maximum width needed for stack A
    if (stack_a && stack_a->element_count > 0)
    {
        for (int i = 0; i < stack_a->element_count; i++)
        {
            char temp[30];
            sprintf(temp, "[%d]", stack_a->stack[i]);
            int len = strlen(temp);
            if (len > max_width_a)
                max_width_a = len;
        }
    }
    
    // Find maximum width needed for stack B
    if (stack_b && stack_b->element_count > 0)
    {
        for (int i = 0; i < stack_b->element_count; i++)
        {
            char temp[30];
            sprintf(temp, "[%d]", stack_b->stack[i]);
            int len = strlen(temp);
            if (len > max_width_b)
                max_width_b = len;
        }
    }
    
    // Add padding
    max_width_a += 2;
    max_width_b += 2;
    
    int total_width = max_width_a + max_width_b + 6; // 6 for borders and spacing
    
    // Top border
    ft_printf("%s%s+", BOLD, BLUE);
    for (int i = 0; i < total_width; i++)
        ft_printf("=");
    ft_printf("+%s\n", RESET);
    
    // Header
    ft_printf("%s|%s %s🅰 Stack A%s", BLUE, RESET, BRIGHT_GREEN, RESET);
    int space_needed = max_width_a - 10; // Account for "🅰 Stack A"
    for (int i = 0; i < space_needed; i++)
        ft_printf(" ");
    
    ft_printf(" %s🅱 Stack B%s", BRIGHT_MAGENTA, RESET);
    space_needed = max_width_b - 10; // Account for "🅱 Stack B"
    for (int i = 0; i < space_needed; i++)
        ft_printf(" ");
    ft_printf(" %s|%s\n", BLUE, RESET);
    
    // Separator
    ft_printf("%s+", BLUE);
    for (int i = 0; i < total_width; i++)
        ft_printf("=");
    ft_printf("+%s\n", RESET);
    
    // Content
    int max_elements = 0;
    if (stack_a) max_elements = stack_a->element_count;
    if (stack_b && stack_b->element_count > max_elements) 
        max_elements = stack_b->element_count;
    
    for (int i = 0; i < max_elements; i++)
    {
        ft_printf("%s|%s ", BLUE, RESET);
        
        // Stack A
        if (stack_a && i < stack_a->element_count)
        {
            char value_str[30];
            sprintf(value_str, "%s[%d]%s", BRIGHT_YELLOW, stack_a->stack[i], RESET);
            ft_printf("%s", value_str);
            
            // Calculate actual printed length (without color codes)
            char plain_str[30];
            sprintf(plain_str, "[%d]", stack_a->stack[i]);
            int padding = max_width_a - strlen(plain_str);
            for (int j = 0; j < padding; j++)
                ft_printf(" ");
        }
        else
        {
            for (int j = 0; j < max_width_a; j++)
                ft_printf(" ");
        }
        
        // Stack B
        if (stack_b && i < stack_b->element_count)
        {
            char value_str[30];
            sprintf(value_str, "%s[%d]%s", BRIGHT_MAGENTA, stack_b->stack[i], RESET);
            ft_printf("%s", value_str);
            
            // Calculate actual printed length (without color codes)
            char plain_str[30];
            sprintf(plain_str, "[%d]", stack_b->stack[i]);
            int padding = max_width_b - strlen(plain_str);
            for (int j = 0; j < padding; j++)
                ft_printf(" ");
        }
        else
        {
            for (int j = 0; j < max_width_b; j++)
                ft_printf(" ");
        }
        
        ft_printf(" %s|%s\n", BLUE, RESET);
    }
    
    // Bottom border
    ft_printf("%s+", BLUE);
    for (int i = 0; i < total_width; i++)
        ft_printf("=");
    ft_printf("+%s\n", RESET);
}

void ft_print_sub_banner(const char *title, const char *subtitle)
{
    printf("\n--- %s ---\n", title);
    if (subtitle)
        printf(">>> %s\n", subtitle);
    printf("\n");
}