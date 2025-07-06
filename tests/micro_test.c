/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_stack_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 19:45:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "stack.h"
#include <string.h>
#include <unistd.h>

// Helper function to create a node with integer content
t_list *create_int_node(int value)
{
    int *content = malloc(sizeof(int));
    if (!content)
        return (NULL);
    *content = value;
    return (ft_lstnew(content));
}

// Function to get the minimum value in a stack
int get_min_value(t_list *stack)
{
    if (!stack)
        return (0);
    
    int min = *(int *)stack->content;
    t_list *temp = stack->next;
    
    while (temp)
    {
        if (*(int *)temp->content < min)
            min = *(int *)temp->content;
        temp = temp->next;
    }
    return (min);
}

// Function to get the maximum value in a stack
int get_max_value(t_list *stack)
{
    if (!stack)
        return (0);
    
    int max = *(int *)stack->content;
    t_list *temp = stack->next;
    
    while (temp)
    {
        if (*(int *)temp->content > max)
            max = *(int *)temp->content;
        temp = temp->next;
    }
    return (max);
}

// Function to find position of minimum value in stack
int find_min_position(t_list *stack)
{
    if (!stack)
        return (-1);
    
    int min = get_min_value(stack);
    int pos = 0;
    t_list *temp = stack;
    
    while (temp)
    {
        if (*(int *)temp->content == min)
            return (pos);
        temp = temp->next;
        pos++;
    }
    return (-1);
}

// Function to check if stack is sorted
int is_sorted(t_list *stack)
{
    if (!stack || !stack->next)
        return (1);
    
    t_list *temp = stack;
    while (temp->next)
    {
        if (*(int *)temp->content > *(int *)temp->next->content)
            return (0);
        temp = temp->next;
    }
    return (1);
}

// Function to get stack size
int get_stack_size(t_list *stack)
{
    int size = 0;
    t_list *temp = stack;
    
    while (temp)
    {
        size++;
        temp = temp->next;
    }
    return (size);
}

// Clear screen and show current state
void show_frame(t_ps *ps, const char *operation)
{
    // Clear screen (works on most terminals)
    ft_printf("\033[2J\033[H");
    
    // Show operation
    if (operation)
        ft_printf("%s🔄 %s%s\n", YELLOW, operation, RESET);
    
    // Show stacks
    print_both_stacks(ps->stack_a, ps->stack_b);
    ft_printf("Size A: %d, Size B: %d\n", ps->size_a, ps->size_b);
    
    // Small delay to see the movement
    usleep(500000); // 0.5 seconds
}

// Simple but effective sorting algorithm
void visual_sort(t_ps *ps)
{
    show_frame(ps, "INITIAL STATE");
    
    // Simple selection sort approach - find minimum and put it at bottom of A
    int operations_count = 0;
    int max_operations = ps->size_a * ps->size_a * 2; // Safety limit
    
    while (!is_sorted(ps->stack_a) && operations_count < max_operations)
    {
       // int min_val = get_min_value(ps->stack_a);
        int min_pos = find_min_position(ps->stack_a);
        int stack_size = get_stack_size(ps->stack_a);
        
        // Move minimum to top of A
        if (min_pos == 0)
        {
            // Minimum is at top, push to B
            pb(ps);
            show_frame(ps, "PB - Moving minimum to B");
        }
        else if (min_pos <= stack_size / 2)
        {
            // Minimum is in top half, rotate forward
            ra(ps);
            show_frame(ps, "RA - Rotating to bring minimum to top");
        }
        else
        {
            // Minimum is in bottom half, rotate backward
            rra(ps);
            show_frame(ps, "RRA - Rotating to bring minimum to top");
        }
        
        operations_count++;
        
        // If A is empty or has only one element, start moving back from B
        if (ps->size_a <= 1)
        {
            while (ps->size_b > 0)
            {
                pa(ps);
                show_frame(ps, "PA - Moving sorted elements back to A");
                operations_count++;
            }
        }
    }
    
    // Move all remaining elements from B back to A (they should be in sorted order)
    while (ps->size_b > 0 && operations_count < max_operations)
    {
        pa(ps);
        show_frame(ps, "PA - Moving sorted elements back to A");
        operations_count++;
    }
    
    if (is_sorted(ps->stack_a))
        show_frame(ps, "SORTING COMPLETE - SUCCESS!");
    else
        show_frame(ps, "SORTING INCOMPLETE - ALGORITHM NEEDS IMPROVEMENT");
}

int main(int argc, char **argv)
{
    t_ps ps;
    t_list *node;
    int i;

    // Initialize the push_swap structure
    ps.stack_a = NULL;
    ps.stack_b = NULL;
    ps.size_a = 0;
    ps.size_b = 0;

    if (argc == 1)
    {
        ft_printf("Usage: %s <numbers>\n", argv[0]);
        ft_printf("Example: %s 64 34 3 32 5 1 89 12 7\n", argv[0]);
        return (1);
    }

    // Build stack A from command line arguments
    i = argc - 1;
    while (i >= 1)
    {
        node = create_int_node(ft_atoi(argv[i]));
        if (!node)
            return (1);
        ft_lstadd_front(&ps.stack_a, node);
        ps.size_a++;
        i--;
    }
    ps.total_size = ps.size_a;

    // Start the visual sorting
    visual_sort(&ps);

    // Cleanup
    ft_lstclear(&ps.stack_a, free);
    ft_lstclear(&ps.stack_b, free);
    
    return (0);
}