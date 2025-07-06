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

    if (is_sorted(data->stack_a))
        sorted_status = "✅ YES";
    else
        sorted_status = "❌ NO";
    
    ft_printf("Initial state - Stack A size: %d, Is sorted: %s\n",
            get_stack_size(data->stack_a), sorted_status);
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
    int *value;
    t_list *new_node;

    // Simple argument parsing - convert strings to integers
    for (i = 1; i < argc; i++)
    {
        value = malloc(sizeof(int));
        if (!value)
            exit(1); // Handle malloc failure
        
        *value = ft_atoi(argv[i]);
        new_node = ft_lstnew(value);
        if (!new_node)
        {
            free(value);
            exit(1);
        }
        
        ft_lstadd_back(&data->stack_a, new_node);
        data->size_a++;
        data->total_size++;
    }
}