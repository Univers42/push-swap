/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:30:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 18:06:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ps.h"
# include "stack.h"
#include <string.h>


// Helper function to create a node with integer content
t_list *create_int_node(int value)
{
    int *content = malloc(sizeof(int));
    if (!content)
        return (NULL);
    *content = value;
    return (ft_lstnew(content));
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
        ft_printf("%s%sUsage: %s <numbers>%s\n", BOLD, RED, argv[0], RESET);
        return (1);
    }

    // Build stack A from command line arguments
    i = argc - 1;
    while (i >= 1)  // Build in reverse to maintain order
    {
        node = create_int_node(ft_atoi(argv[i]));
        if (!node)
            return (1);
        ft_lstadd_front(&ps.stack_a, node);
        ps.size_a++;
        i--;
    }
    ps.total_size = ps.size_a;

    // Display initial state
    ft_print_banner("PUSH_SWAP OPERATION TESTER", "", BANNER_DOUBLE);
    ft_print_sub_banner("INITIAL STATE", "Displaying the starting configuration of both stacks");
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);
              
    // first pb operations
    ft_print_banner("TESTING PB OPERATIONS", "", BANNER_DOUBLE);    
    ft_print_sub_banner("First PB Operation", "Push top element from A to B");
    pb(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);

    // second pb operation
    ft_print_sub_banner("Second PB Operation", "Push another element from A to B");
    pb(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);

    // Test pa operations
    ft_print_banner("TESTING PA OPERATIONS", "", BANNER_DOUBLE);
    ft_print_sub_banner("PA Operation", "Moving top element from B back to A");
    pa(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);

    // Test edge case: pb when A is empty
    ft_print_sub_banner("EDGE CASE PREPARATION", "Moving all elements to stack B to empty A");
    while (ps.stack_a)
        pb(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);
    
    // ANOTHER EDGE CASE
    ft_print_sub_banner("EDGE CASE TEST", "Attempting PB when stack A is empty - should do nothing");
    pb(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);

    ft_print_banner("TESTING SWAP OPERATIONS", "", BANNER_DOUBLE);
    ft_print_sub_banner("SA operation", "swap top node with second node value");
    pa(&ps);
    pa(&ps);
    sa(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);


    ft_print_sub_banner("SB operation", "swap top node with second node value");
    sb(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);

    ft_print_sub_banner("SS operation", "same but this time with both stack");
    ss(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);

    ft_print_banner("TESTING ROTATE OPERATIONS", "", BANNER_DOUBLE);
    ft_print_sub_banner("RA operation", "rotate in a way that the fist node is gets at the tail");
    ra(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);

    ft_print_sub_banner("RB operation", "same but this time with stack B");
    rb(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);

    ft_print_sub_banner("RR operation", "same but this time with both stack");
    rr(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);
    
    ft_print_banner("TESTING REVERSE ROTATE OPERATIONS", "", BANNER_DOUBLE);
    ft_print_sub_banner("RRA operation", "it's the same as the rotation before but this time we reverse the order");
    rr(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);
    
    ft_print_sub_banner("RRB operation", "same but this time with stack B");
    rr(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);
    
    ft_print_sub_banner("RRR operation", "same but this time with both stack");
    rr(&ps);
    print_both_stacks(ps.stack_a, ps.stack_b);
    ft_printf("%s📈 Size A: %s%d%s, Size B: %s%d%s\n\n", CYAN, BRIGHT_YELLOW, ps.size_a, CYAN, BRIGHT_YELLOW, ps.size_b, RESET);

    //footer information + free memory
    ft_print_notification("CLEAN", "cleanup complete", "success");
    // Cleanup (you'll need to implement this)
    ft_lstclear(&ps.stack_a, free);
    ft_lstclear(&ps.stack_b, free);
    ft_print_notification("TERMINATING", "All the test have been completed", "success");
    return (0);
}