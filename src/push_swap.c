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
    if (is_sorted(data.stack_a))
        return (ft_putendl_fd("success !", 1), 0);
    return (EXIT_SUCCESS);
}

static void process_sorting(t_ps *data)
{
    const char *sorted_status;

    ft_printf("DEBUG: Entering process_sorting\n");
    if (is_sorted(data->stack_a))
        sorted_status = "✅ YES";
    else
        sorted_status = "❌ NO";
    
    ft_printf("Initial state - Stack A size: %d, Is sorted: %s\n",
            get_stack_size(data->stack_a), sorted_status);

    // Print stack contents for debugging
    t_stack *tmp = data->stack_a;
    int idx = 0;
    while (tmp)
    {
        ft_printf("DEBUG: stack_a[%d] = %d\n", idx, tmp->value);
        tmp = tmp->next;
        idx++;
    }

    run_sort_algo(data);

    ft_printf("Final state - Stack A size: %d, Is sorted: %s\n",
            get_stack_size(data->stack_a), 
            is_sorted(data->stack_a) ? "✅ YES" : "❌ NO");
}

void run_sort_algo(t_ps *data)
{
    radix_sort(data);
}

static void setlement(t_ps *data)
{
    data->stack_a = NULL;
    data->stack_b = NULL;
    data->size_a = 0;
    data->size_b = 0;
    data->total_size = 0;
}

static void load_datas(t_ps *data, int argc, char **argv)
{
    int i;
    t_stack *new_node;

    ft_printf("DEBUG: Starting to load datas\n");
    for (i = 1; i < argc; i++)
    {
        int val = ft_atoi(argv[i]);
        ft_printf("DEBUG: Creating node for argv[%d]=%s (int: %d)\n", i, argv[i], val);
        new_node = create_int_node(val);
        if (!new_node)
        {
            ft_printf("ERROR: Failed to create node for value %d\n", val);
            exit(1);
        }
        ft_stkadd_back(&data->stack_a, new_node);
        data->size_a++;
        data->total_size++;
        ft_printf("DEBUG: Added node with value %d to stack_a (size now %d)\n", val, data->size_a);
    }
    ft_printf("DEBUG: Finished loading datas. Stack A size: %d\n", data->size_a);
}