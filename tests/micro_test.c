#include "ps.h"
#include "stack.h"
#include <string.h>
#include <unistd.h>

// Global variable to control visualization
static int g_visual_mode = 1;
static int g_delay = 200000; // 0.5 seconds default

// Clear screen and show current state
void show_frame(t_ps *ps, const char *operation)
{
    if (!g_visual_mode)
        return;
    
    // Clear screen (works on most terminals)
    ft_printf("\033[2J\033[H");
    
    // Show operation
    if (operation)
        ft_printf("%s🔄 %s%s\n", YELLOW, operation, RESET);
    
    // Show stacks
    print_both_stacks(ps->stack_a, ps->stack_b);
    ft_printf("Size A: %d, Size B: %d\n", ps->size_a, ps->size_b);
    
    // Small delay to see the movement
    usleep(g_delay);
}

// Function pointer type for sorting algorithms
typedef void (*sort_algorithm_t)(t_ps *ps);

// Simple but effective sorting algorithm (your original)
void visual_sort(t_ps *ps)
{
    show_frame(ps, "INITIAL STATE");
    
    // Simple selection sort approach - find minimum and put it at bottom of A
    int operations_count = 0;
    int max_operations = ps->size_a * ps->size_a * 2; // Safety limit
    
    while (!is_sorted(ps->stack_a) && operations_count < max_operations)
    {
        int min_pos = find_min_position(ps->stack_a);
        
        // Move minimum to top of A
        if (min_pos == 0)
        {
            // Minimum is at top, push to B
            pb(ps);
            show_frame(ps, "PB - Moving minimum to B");
        }
        else if (min_pos <= ps->size_a / 2)
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

// Example: Simple algorithm that pushes all to B then back to A
void simple_algorithm(t_ps *ps)
{
    show_frame(ps, "SIMPLE ALGORITHM - INITIAL STATE");
    
    int operations_count = 0;
    int max_operations = ps->size_a * 4; // Safety limit
    
    // Push all elements to B
    while (ps->size_a > 0 && operations_count < max_operations)
    {
        pb(ps);
        show_frame(ps, "PB - Moving element to B");
        operations_count++;
    }
    
    // Push all elements back to A
    while (ps->size_b > 0 && operations_count < max_operations)
    {
        pa(ps);
        show_frame(ps, "PA - Moving element back to A");
        operations_count++;
    }
    
    if (is_sorted(ps->stack_a))
        show_frame(ps, "SIMPLE ALGORITHM COMPLETE - SUCCESS!");
    else
        show_frame(ps, "SIMPLE ALGORITHM COMPLETE - NOT SORTED (as expected)");
}

// Algorithm registry
typedef struct {
    const char *name;
    sort_algorithm_t algorithm;
    const char *description;
} algorithm_info_t;

static algorithm_info_t g_algorithms[] = {
    {"visual", visual_sort, "Original visual sort (selection sort approach)"},
    {"simple", simple_algorithm, "Simple algorithm that moves all to B then back to A"},
    {"radix", radix_sort, "efficient sorting usign bit operations"},
    {NULL, NULL, NULL}
};

// Function to list available algorithms
void list_algorithms()
{
    ft_printf("Available algorithms:\n");
    for (int i = 0; g_algorithms[i].name; i++)
    {
        ft_printf("  %s%s%s - %s\n", 
                  YELLOW, g_algorithms[i].name, RESET, 
                  g_algorithms[i].description);
    }
}

// Function to find algorithm by name
sort_algorithm_t find_algorithm(const char *name)
{
    for (int i = 0; g_algorithms[i].name; i++)
    {
        if (strcmp(g_algorithms[i].name, name) == 0)
            return g_algorithms[i].algorithm;
    }
    return NULL;
}

// Function to run any algorithm with visualization
void run_algorithm(t_ps *ps, sort_algorithm_t algorithm)
{
    if (!algorithm)
    {
        ft_printf("Error: Algorithm not found\n");
        return;
    }
    
    // Run the algorithm
    algorithm(ps);
}

// Parse command line options
void parse_options(int *argc, char ***argv, sort_algorithm_t *algorithm)
{
    *algorithm = visual_sort; // default
    
    for (int i = 1; i < *argc; i++)
    {
        if (strcmp((*argv)[i], "--help") == 0 || strcmp((*argv)[i], "-h") == 0)
        {
            ft_printf("Usage: %s [OPTIONS] <numbers>\n", (*argv)[0]);
            ft_printf("OPTIONS:\n");
            ft_printf("  -a, --algorithm ALGO  Choose sorting algorithm\n");
            ft_printf("  -s, --silent         Run without visualization\n");
            ft_printf("  -d, --delay MS       Set delay in microseconds (default: 500000)\n");
            ft_printf("  -l, --list           List available algorithms\n");
            ft_printf("  -h, --help           Show this help\n");
            ft_printf("\nExample: %s -a bubble 64 34 3 32 5 1 89 12 7\n", (*argv)[0]);
            exit(0);
        }
        else if (strcmp((*argv)[i], "--list") == 0 || strcmp((*argv)[i], "-l") == 0)
        {
            list_algorithms();
            exit(0);
        }
        else if (strcmp((*argv)[i], "--algorithm") == 0 || strcmp((*argv)[i], "-a") == 0)
        {
            if (i + 1 < *argc)
            {
                *algorithm = find_algorithm((*argv)[i + 1]);
                if (!*algorithm)
                {
                    ft_printf("Error: Unknown algorithm '%s'\n", (*argv)[i + 1]);
                    list_algorithms();
                    exit(1);
                }
                // Remove algorithm arguments
                for (int j = i; j < *argc - 2; j++)
                {
                    (*argv)[j] = (*argv)[j + 2];
                }
                *argc -= 2;
                i--; // Adjust index after removal
            }
            else
            {
                ft_printf("Error: --algorithm requires an argument\n");
                exit(1);
            }
        }
        else if (strcmp((*argv)[i], "--silent") == 0 || strcmp((*argv)[i], "-s") == 0)
        {
            g_visual_mode = 0;
            // Remove this argument
            for (int j = i; j < *argc - 1; j++)
            {
                (*argv)[j] = (*argv)[j + 1];
            }
            (*argc)--;
            i--;
        }
        else if (strcmp((*argv)[i], "--delay") == 0 || strcmp((*argv)[i], "-d") == 0)
        {
            if (i + 1 < *argc)
            {
                g_delay = ft_atoi((*argv)[i + 1]);
                // Remove delay arguments
                for (int j = i; j < *argc - 2; j++)
                {
                    (*argv)[j] = (*argv)[j + 2];
                }
                *argc -= 2;
                i--;
            }
            else
            {
                ft_printf("Error: --delay requires an argument\n");
                exit(1);
            }
        }
    }
}

int main(int argc, char **argv)
{
    t_ps ps;
    t_list *node;
    int i;
    sort_algorithm_t algorithm;
    
    // Initialize the push_swap structure
    ps.stack_a = NULL;
    ps.stack_b = NULL;
    ps.size_a = 0;
    ps.size_b = 0;
    
    // Parse command line options
    parse_options(&argc, &argv, &algorithm);
    
    if (argc == 1)
    {
        ft_printf("Usage: %s [OPTIONS] <numbers>\n", argv[0]);
        ft_printf("Use -h or --help for detailed usage information\n");
        ft_printf("Example: %s -a visual 64 34 3 32 5 1 89 12 7\n", argv[0]);
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
    
    // Start the sorting with chosen algorithm
    run_algorithm(&ps, algorithm);
    
    // Cleanup
    ft_lstclear(&ps.stack_a, free);
    ft_lstclear(&ps.stack_b, free);
    
    return (0);
}

// Utility functions to help with algorithm development
void debug_print_stack(t_ps *ps, const char *message)
{
    if (g_visual_mode)
        show_frame(ps, message);
    else
        ft_printf("%s\n", message);
}

// Helper function to add your own algorithms
void add_custom_algorithm(const char *name, sort_algorithm_t algorithm, const char *description)
{
    (void)algorithm;
    (void)description;
    // This is a simplified version - in a real implementation you'd want dynamic allocation
    // For now, manually add to the g_algorithms array above

    ft_printf("To add algorithm '%s': Add it to g_algorithms array in the source code\n", name);
}