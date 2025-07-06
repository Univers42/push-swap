/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:29:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 17:52:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
// Find maximum width needed for a stack
int find_max_width(t_list *stack)
{
    int max_width = 15; // Minimum width
    char temp_str[50];
    
    while (stack)
    {
        sprintf(temp_str, "[%d]", *(int *)stack->content);
        int current_width = strlen(temp_str);
        if (current_width > max_width)
            max_width = current_width;
        stack = stack->next;
    }
    return max_width;
}

void    print_stack(t_list *stack, char name)
{
    ft_printf("%s%s╔══ Stack %c ══╗%s\n", BOLD, CYAN, name, RESET);
    if (!stack)
    {
        ft_printf("%s║  (empty)    ║%s\n", DIM, RESET);
        ft_printf("%s╚═════════════╝%s\n\n", CYAN, RESET);
        return;
    }
    while (stack)
    {
        ft_printf("%s║%s %s[%s%d%s]%s      %s║%s\n", 
                  CYAN, RESET, YELLOW, BRIGHT_YELLOW, *(int *)stack->content, YELLOW, RESET, CYAN, RESET);
        stack = stack->next;
    }
    ft_printf("%s╚═════════════╝%s\n\n", CYAN, RESET);
}


// New function to count stack elements
int count_stack_elements(t_list *stack)
{
    int count = 0;
    while (stack)
    {
        count++;
        stack = stack->next;
    }
    return count;
}

void    print_both_stacks(t_list *stack_a, t_list *stack_b)
{
    int col_width_a = find_max_width(stack_a);
    int col_width_b = find_max_width(stack_b);
    
    // Ensure minimum widths
    if (col_width_a < 12) col_width_a = 12;
    if (col_width_b < 12) col_width_b = 12;
    
    // Fixed header text widths (without emojis for calculation)
    int header_width_a = 9; // "A Stack A" 
    int header_width_b = 9; // "B Stack B"
    
    // Total width = border + padding + col_a + separator + col_b + padding + border
    int total_width = 1 + 2 + col_width_a + 3 + col_width_b + 2 + 1;
    
    // Top border
    ft_printf("%s%s+", BOLD, BLUE);
    for (int i = 1; i < total_width - 1; i++)
        ft_printf("=");
    ft_printf("+%s\n", RESET);
    
    // Print headers with proper centering
    int header_padding_a = (col_width_a - header_width_a) / 2;
    int header_padding_b = (col_width_b - header_width_b) / 2;
    if (header_padding_a < 0) header_padding_a = 0;
    if (header_padding_b < 0) header_padding_b = 0;
    
    ft_printf("%s|%s  %*s%sA Stack A%s%*s   %*s%sB Stack B%s%*s  %s|%s\n", 
              BLUE, RESET,
              header_padding_a, "", BRIGHT_GREEN, RESET, 
              col_width_a - header_width_a - header_padding_a, "",
              header_padding_b, "", BRIGHT_MAGENTA, RESET,
              col_width_b - header_width_b - header_padding_b, "",
              BLUE, RESET);
    
    // Separator line
    ft_printf("%s+", BLUE);
    for (int i = 1; i < total_width - 1; i++)
        ft_printf("=");
    ft_printf("+%s\n", RESET);
    
    // Print stack contents
    t_list *temp_a = stack_a;
    t_list *temp_b = stack_b;
    
    while (temp_a || temp_b)
    {
        ft_printf("%s|%s  ", BLUE, RESET);
        
        if (temp_a)
        {
            char num_str[50];
            sprintf(num_str, "[%d]", *(int *)temp_a->content);
            int num_len = strlen(num_str);
            int padding = col_width_a - num_len;
            if (padding < 0) padding = 0;
            
            ft_printf("%s%s%s%s%*s", 
                     YELLOW, BRIGHT_YELLOW, num_str, RESET, 
                     padding, "");
            temp_a = temp_a->next;
        }
        else
        {
            ft_printf("%*s", col_width_a, "");
        }
            
        ft_printf("   "); // Fixed separator (3 spaces)
        
        if (temp_b)
        {
            char num_str_b[50];
            sprintf(num_str_b, "[%d]", *(int *)temp_b->content);
            int num_len_b = strlen(num_str_b);
            int padding_b = col_width_b - num_len_b;
            if (padding_b < 0) padding_b = 0;
            
            ft_printf("%s%s%s%s%*s", 
                     MAGENTA, BRIGHT_MAGENTA, num_str_b, RESET,
                     padding_b, "");
            temp_b = temp_b->next;
        }
        else
        {
            ft_printf("%*s", col_width_b, "");
        }
        
        ft_printf("  %s|%s\n", BLUE, RESET);
    }
    
    // Bottom border
    ft_printf("%s+", BLUE);
    for (int i = 1; i < total_width - 1; i++)
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
