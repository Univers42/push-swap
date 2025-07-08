#include "ps.h"

/**
 * Swap the first two elements of the stack
 * @param stack Array-based stack
 */
static void swap(t_stack *stack)
{
    int temp;

    if (!stack || stack->element_count < 2)
        return ;
    
    // Swap elements at index 0 and 1
    temp = stack->stack[0];
    stack->stack[0] = stack->stack[1];
    stack->stack[1] = temp;
}

void sa(t_ps *ps)
{
    swap(&ps->stack_a);
    
    if (ps->recording)
        append_operation(ps, "sa");
    
    if (is_recording())
        record_operation("sa");
    else if (!ps->recording)
        ft_printf("sa\n");
}

void sb(t_ps *ps)
{
    swap(&ps->stack_b);
    
    if (ps->recording)
        append_operation(ps, "sb");
    
    if (is_recording())
        record_operation("sb");
    else if (!ps->recording)
        ft_printf("sb\n");
}

void ss(t_ps *ps)
{
    swap(&ps->stack_a);
    swap(&ps->stack_b);
    
    if (ps->recording)
        append_operation(ps, "ss");
    
    if (is_recording())
        record_operation("ss");
    else if (!ps->recording)
        ft_printf("ss\n");
}