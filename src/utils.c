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
    
    while (stack)
    {
        sprintf(temp_str, "[%d]", stack->value);
        int current_width = strlen(temp_str);
        if (current_width > max_width)
            max_width = current_width;
        stack = stack->next;
    }
    return max_width;
}

void print_stack(t_stack *stack, char name)
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
                  CYAN, RESET, YELLOW, BRIGHT_YELLOW, stack->value, YELLOW, RESET, CYAN, RESET);
        stack = stack->next;
    }
    ft_printf("%s╚═════════════╝%s\n\n", CYAN, RESET);
}

// Count stack elements
int count_stack_elements(t_stack *stack)
{
    int count = 0;
    while (stack)
    {
        count++;
        stack = stack->next;
    }
    return count;
}

void print_both_stacks(t_stack *stack_a, t_stack *stack_b)
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
    t_stack *temp_a = stack_a;
    t_stack *temp_b = stack_b;
    
    while (temp_a || temp_b)
    {
        ft_printf("%s|%s  ", BLUE, RESET);
        
        if (temp_a)
        {
            char num_str[50];
            sprintf(num_str, "[%d]", temp_a->value);
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
            sprintf(num_str_b, "[%d]", temp_b->value);
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

// Function to check if stack is sorted
int is_sorted(t_stack *stack)
{
    if (!stack || !stack->next)
        return (1);
    
    t_stack *temp = stack;
    while (temp->next)
    {
        if (temp->value > temp->next->value)
            return (0);
        temp = temp->next;
    }
    return (1);
}

// Function to get stack size
int get_stack_size(t_stack *stack)
{
    int size = 0;
    t_stack *temp = stack;
    
    while (temp)
    {
        size++;
        temp = temp->next;
    }
    return (size);
}

// Function to get the minimum value in a stack
int get_min_value(t_stack *stack)
{
    if (!stack)
        return (0);
    
    int min = stack->value;
    t_stack *temp = stack->next;
    
    while (temp)
    {
        if (temp->value < min)
            min = temp->value;
        temp = temp->next;
    }
    return (min);
}

// Function to get the maximum value in a stack
int get_max_value(t_stack *stack)
{
    if (!stack)
        return (0);
    
    int max = stack->value;
    t_stack *temp = stack->next;
    
    while (temp)
    {
        if (temp->value > max)
            max = temp->value;
        temp = temp->next;
    }
    return (max);
}

// Function to find position of minimum value in stack
int find_min_position(t_stack *stack)
{
    if (!stack)
        return (-1);
    
    int min = get_min_value(stack);
    int pos = 0;
    t_stack *temp = stack;
    
    while (temp)
    {
        if (temp->value == min)
            return (pos);
        temp = temp->next;
        pos++;
    }
    return (-1);
}

t_stack *ft_new_node(int content)
{
    t_stack *stack;

    stack = malloc(sizeof(t_stack));
    if (!stack)
        return NULL;

    stack->value = content;
    stack->index = 0;
    stack->pos = 0;
    stack->target_pos = 0;
    stack->cost_a = 0;
    stack->cost_b = 0;
    stack->top = 0;
    stack->capacity = 0;
    stack->bottom = 0;
    stack->element_count = 0;
    stack->next = NULL;
    stack->prev = NULL;
    stack->size = 0;
    stack->is_circular = false;
    return stack;
}

// Helper function to create a node with integer content
t_stack *create_int_node(int value)
{
    return ft_new_node(value);
}


void ft_stkclear(t_stack **stk)
{
    t_stack *stk_temp;

    if (!stk || !*stk)
        return ;
    while (*stk)
    {
        stk_temp = (*stk)->next;
        free(*stk);
        *stk = stk_temp;
    }
}

void ft_stkadd_back(t_stack **stk, t_stack *new_node)
{
    t_stack *temp;

    if (!stk || !new_node)
        return ;
    if (!*stk)
    {
        *stk = new_node;
        return ;
    }
    temp = *stk;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}

void ft_stkadd_front(t_stack **stk, t_stack *new_node)
{
    if (!stk || !new_node)
        return ;
    new_node->next = *stk;
    *stk = new_node;
}

void    ft_stklast(t_stack *stk, t_stack **last)
{
    if (!stk || !last)
        return ;
    while (stk->next)
        stk = stk->next;
    *last = stk;
}