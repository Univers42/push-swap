/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:00:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 21:25:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

#define EXIT_SUCCESS 0

static void process_sorting(t_ps *data);
static void load_datas(t_ps *data, int argc, char **argv);
static void setlement(t_ps *data);

int main(int argc, char **argv)
{
    t_ps data;

    if (argc == 1)
        return (ft_putendl_fd("./usage (numbers)<...>", 2), 1);
    
    setlement(&data);
    load_datas(&data, argc, argv);
    process_sorting(&data);
    
    // Check if sorted and only print success if truly sorted
    if (is_sorted(&data.stack_a) && data.stack_b.element_count == 0)
    {
        ft_putendl_fd("success !", 1);
    }
    else
    {
        ft_putendl_fd("ERROR: Sorting failed!", 2);
        // Print final state for debugging
        ft_printf("Final state - Stack A has %d elements, Stack B has %d elements\n",
                 data.stack_a.element_count, data.stack_b.element_count);
    }
    
    // Clean up
    free_stack(&data.stack_a);
    free_stack(&data.stack_b);
    free_op_buffer(&data.op_buffer);
    
    return (EXIT_SUCCESS);
}

static void process_sorting(t_ps *data)
{
    const char *sorted_status;

    ft_printf("DEBUG: Entering process_sorting\n");
    
    // Initial check
    if (is_sorted(&data->stack_a))
        sorted_status = "✅ YES";
    else
        sorted_status = "❌ NO";
    
    ft_printf("Initial state - Stack A size: %d, Is sorted: %s\n",
            get_stack_size(&data->stack_a), sorted_status);

    // Print stack contents for debugging
    ft_printf("DEBUG: Initial stack contents:\n");
    for (int i = 0; i < data->stack_a.element_count; i++)
    {
        ft_printf("  stack_a[%d] = %d\n", i, data->stack_a.stack[i]);
    }

    run_sort_algo(data);

    // Final check with detailed output
    ft_printf("\nDEBUG: Final stack contents:\n");
    for (int i = 0; i < data->stack_a.element_count; i++)
    {
        ft_printf("  stack_a[%d] = %d\n", i, data->stack_a.stack[i]);
        if (i > 0 && data->stack_a.stack[i-1] > data->stack_a.stack[i])
        {
            ft_printf("  ^^^ ERROR: Not sorted here! %d > %d\n", 
                     data->stack_a.stack[i-1], data->stack_a.stack[i]);
        }
    }

    ft_printf("\nFinal state - Stack A size: %d, Is sorted: %s\n",
            get_stack_size(&data->stack_a), 
            is_sorted(&data->stack_a) ? "✅ YES" : "❌ NO");
    
    // Additional verification
    if (!is_sorted(&data->stack_a))
    {
        ft_printf("ERROR: Stack is NOT sorted after algorithm completion!\n");
    }
}

void run_sort_algo(t_ps *data)
{
    chunk_sort(data);
}

static void setlement(t_ps *data)
{
    data->total_size = 0;
    data->recording = false;  // Disable recording by default
    
    // Initialize array-based stacks with capacity 0 (will be set in load_datas)
    init_stack(&data->stack_a, 0);
    init_stack(&data->stack_b, 0);
    
    // Initialize operations buffer
    init_op_buffer(&data->op_buffer, MAX_OPERATIONS);
}

static void load_datas(t_ps *data, int argc, char **argv)
{
    int i;
    int count = argc - 1;

    ft_printf("DEBUG: Starting to load datas\n");
    
    // Initialize stacks with proper capacity
    init_stack(&data->stack_a, count);
    init_stack(&data->stack_b, count);
    
    // Load numbers into stack A
    for (i = 1; i < argc; i++)
    {
        int val = ft_atoi(argv[i]);
        ft_printf("DEBUG: Adding value %d to stack_a[%d]\n", val, data->stack_a.element_count);
        data->stack_a.stack[data->stack_a.element_count++] = val;
    }
    
    data->total_size = data->stack_a.element_count;
    ft_printf("DEBUG: Finished loading datas. Stack A size: %d\n", data->stack_a.element_count);
}