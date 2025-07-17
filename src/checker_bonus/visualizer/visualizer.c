/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/17 01:41:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# ifndef _BSD_SOURCE
#  define _BSD_SOURCE
# endif
#include "push_swap.h"
#include "visualizer_bonus.h"
#include "checker_bonus.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Remove global variable - use static local variable instead
t_test_context *get_test_context(void)
{
    static t_test_context context = {0};
    return &context;
}

void init_recorder(void)
{
    t_test_context *ctx = get_test_context();
    
    // Clean up any existing operations
    cleanup_recorder();
    
    ctx->operations = NULL;
    ctx->last_op = NULL;
    ctx->op_count = 0;
    ctx->is_recording = 0;
    ctx->delay_ms = 500;
    ctx->verbose_mode = 0;
    ctx->test_ps = NULL;
}

void record_operation(const char *operation)
{
    t_test_context *ctx = get_test_context();
    
    if (!ctx->is_recording || !operation)
        return;
    
    t_operation *new_op = malloc(sizeof(t_operation));
    if (!new_op)
        return;
    
    new_op->name = ft_strdup(operation);
    new_op->next = NULL;
    
    if (!ctx->operations)
    {
        ctx->operations = new_op;
        ctx->last_op = new_op;
    }
    else
    {
        ctx->last_op->next = new_op;
        ctx->last_op = new_op;
    }
    ctx->op_count++;
}


void start_recording(void)
{
    t_test_context *ctx = get_test_context();
    ctx->is_recording = 1;
}

void stop_recording(void)
{
    t_test_context *ctx = get_test_context();
    ctx->is_recording = 0;
}

int is_recording(void)
{
    t_test_context *ctx = get_test_context();
    return ctx->is_recording;
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
        sprintf(temp, "[%d]", get_stack_element_at_position(stack_a, i + 1));
        int len = strlen(temp);
        if (len > max_width_a)
            max_width_a = len;
    }
    
    // Find maximum width needed for stack B
    for (int i = 0; i < stack_b->element_count; i++)
    {
        char temp[20];
        sprintf(temp, "[%d]", get_stack_element_at_position(stack_b, i + 1));
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
            int value = get_stack_element_at_position(stack_a, i + 1);
            ft_printf("%s[%d]%s", BRIGHT_YELLOW, value, RESET);
            char temp[20];
            sprintf(temp, "[%d]", value);
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
            int value = get_stack_element_at_position(stack_b, i + 1);
            ft_printf("%s[%d]%s", BRIGHT_MAGENTA, value, RESET);
            char temp[20];
            sprintf(temp, "[%d]", value);
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
    
    ft_printf("\033[2J\033[H");
    if (operation)
        ft_printf("🔄 %s\n", operation);
    print_both_array_stacks(&ps->a, &ps->b);
    ft_printf("Size A: %d, Size B: %d\n", 
        ps->a.element_count, ps->b.element_count);
    if (ctx->delay_ms > 0)
        usleep(ctx->delay_ms * 100);
}

void execute_operation_for_visual(t_ps *ps, const char *op)
{
    // Use checker operations instead of main operations
    t_op operation = string_to_op(op);
    if (operation != OP_NULL)
        execute_checker_operation(ps, operation);
}
  

void free_stack(t_stack *stack)
{
    if (stack && stack->stack)
    {
        free(stack->stack);
        stack->stack = NULL;
    }
}

bool is_sorted(t_stack *stack)
{
    int i;
    
    if (stack->element_count <= 1)
        return true;
    
    for (i = 0; i < stack->element_count - 1; i++)
    {
        if (get_stack_element_at_position(stack, i + 1) > 
            get_stack_element_at_position(stack, i + 2))
            return false;
    }
    return true;
}

void cleanup_recorder(void)
{
    t_test_context *ctx = get_test_context();
    t_operation *current = ctx->operations;
    t_operation *next;
    
    while (current)
    {
        next = current->next;
        if (current->name)
            free(current->name);
        free(current);
        current = next;
    }
    
    ctx->operations = NULL;
    ctx->last_op = NULL;
    ctx->op_count = 0;
    ctx->is_recording = 0;
}
