/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

// Global test context
static t_test_context g_test_context = {0};

t_test_context *get_test_context(void)
{
    return &g_test_context;
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
    
    new_op->name = strdup(operation);
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

void cleanup_recorder(void)
{
    t_test_context *ctx = get_test_context();
    t_operation *current = ctx->operations;
    
    while (current)
    {
        t_operation *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    
    ctx->operations = NULL;
    ctx->last_op = NULL;
    ctx->op_count = 0;
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
        usleep(ctx->delay_ms * 1000);
}

void print_both_array_stacks(t_stack *stack_a, t_stack *stack_b)
{
    int max_elements;
    int i;

    ft_printf("╔════════════╦════════════╗\n");
    ft_printf("║  Stack A   ║  Stack B   ║\n");
    ft_printf("╠════════════╬════════════╣\n");
    
    max_elements = stack_a->element_count;
    if (stack_b->element_count > max_elements)
        max_elements = stack_b->element_count;
    
    i = 0;
    while (i < max_elements)
    {
        ft_printf("║ ");
        if (i < stack_a->element_count)
            ft_printf("%4d       ", get_stack_element_at_position(stack_a, i + 1));
        else
            ft_printf("           ");
        ft_printf("║ ");
        if (i < stack_b->element_count)
            ft_printf("%4d       ", get_stack_element_at_position(stack_b, i + 1));
        else
            ft_printf("           ");
        ft_printf("║\n");
        i++;
    }
    ft_printf("╚════════════╩════════════╝\n");
}

void execute_operation_for_visual(t_ps *ps, const char *op)
{
    if (strcmp(op, "sa") == 0) sa(ps);
    else if (strcmp(op, "sb") == 0) sb(ps);
    else if (strcmp(op, "ss") == 0) ss(ps);
    else if (strcmp(op, "pa") == 0) pa(ps);
    else if (strcmp(op, "pb") == 0) pb(ps);
    else if (strcmp(op, "ra") == 0) ra(ps);
    else if (strcmp(op, "rb") == 0) rb(ps);
    else if (strcmp(op, "rr") == 0) rr(ps);
    else if (strcmp(op, "rra") == 0) rra(ps);
    else if (strcmp(op, "rrb") == 0) rrb(ps);
    else if (strcmp(op, "rrr") == 0) rrr(ps);
}

t_ps *create_ps_copy(t_ps *original)
{
    t_ps *copy = malloc(sizeof(t_ps));
    if (!copy)
        return NULL;
    
    // Initialize stacks
    copy->a.stack = malloc(sizeof(int) * original->a.capacity);
    copy->b.stack = malloc(sizeof(int) * original->b.capacity);
    if (!copy->a.stack || !copy->b.stack)
    {
        if (copy->a.stack) free(copy->a.stack);
        if (copy->b.stack) free(copy->b.stack);
        free(copy);
        return NULL;
    }
    
    copy->a.capacity = original->a.capacity;
    copy->b.capacity = original->b.capacity;
    copy->a.top = original->a.top;
    copy->b.top = original->b.top;
    copy->a.bottom = original->a.bottom;
    copy->b.bottom = original->b.bottom;
    copy->a.element_count = original->a.element_count;
    copy->b.element_count = original->b.element_count;
    
    // Copy stack data
    for (int i = 0; i < original->a.capacity; i++)
        copy->a.stack[i] = original->a.stack[i];
    for (int i = 0; i < original->b.capacity; i++)
        copy->b.stack[i] = original->b.stack[i];
    
    copy->total_size = original->total_size;
    copy->recording = false;
    copy->op_list = NULL;
    copy->op_count = 0;
    
    return copy;
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
    if (stack->element_count <= 1)
        return true;
    
    for (int i = 0; i < stack->element_count - 1; i++)
    {
        if (get_stack_element_at_position(stack, i + 1) > 
            get_stack_element_at_position(stack, i + 2))
            return false;
    }
    return true;
}

void run_algorithm_with_visualization(t_ps *ps, void (*algorithm)(t_ps *))
{
    // Implementation would go here - simplified for compilation
    (void)ps;
    (void)algorithm;
    ft_printf("Algorithm visualization not implemented yet\n");
}
