#include "ps.h"
#include "stack.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// Operation recording system
typedef struct s_operation {
    char *name;
    struct s_operation *next;
} t_operation;

typedef struct s_recorder {
    t_operation *operations;
    t_operation *last;
    int count;
    int recording;
} t_recorder;

// Global recorder
static t_recorder g_recorder = {NULL, NULL, 0, 0};

// Initialize recorder
void init_recorder(void)
{
    g_recorder.operations = NULL;
    g_recorder.last = NULL;
    g_recorder.count = 0;
    g_recorder.recording = 1;
}

// Add operation to recording
void record_operation(const char *operation)
{
    if (!g_recorder.recording)
        return;
    
    t_operation *new_op = malloc(sizeof(t_operation));
    if (!new_op)
        return;
    
    new_op->name = strdup(operation);
    new_op->next = NULL;
    
    if (!g_recorder.operations)
    {
        g_recorder.operations = new_op;
        g_recorder.last = new_op;
    }
    else
    {
        g_recorder.last->next = new_op;
        g_recorder.last = new_op;
    }
    g_recorder.count++;
}

// Clean up recorder
void cleanup_recorder(void)
{
    t_operation *current = g_recorder.operations;
    while (current)
    {
        t_operation *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    g_recorder.operations = NULL;
    g_recorder.last = NULL;
    g_recorder.count = 0;
}

// Start/stop recording
void start_recording(void)
{
    g_recorder.recording = 1;
}

void stop_recording(void)
{
    g_recorder.recording = 0;
}

// Modified operation functions that record themselves
void recorded_sa(t_ps *ps)
{
    sa(ps);
    record_operation("sa");
}

void recorded_sb(t_ps *ps)
{
    sb(ps);
    record_operation("sb");
}

void recorded_ss(t_ps *ps)
{
    ss(ps);
    record_operation("ss");
}

void recorded_pa(t_ps *ps)
{
    pa(ps);
    record_operation("pa");
}

void recorded_pb(t_ps *ps)
{
    pb(ps);
    record_operation("pb");
}

void recorded_ra(t_ps *ps)
{
    ra(ps);
    record_operation("ra");
}

void recorded_rb(t_ps *ps)
{
    rb(ps);
    record_operation("rb");
}

void recorded_rr(t_ps *ps)
{
    rr(ps);
    record_operation("rr");
}

void recorded_rra(t_ps *ps)
{
    rra(ps);
    record_operation("rra");
}

void recorded_rrb(t_ps *ps)
{
    rrb(ps);
    record_operation("rrb");
}

void recorded_rrr(t_ps *ps)
{
    rrr(ps);
    record_operation("rrr");
}

// Visualization functions
void show_frame(t_ps *ps, const char *operation, int delay_ms)
{
    // Clear screen
    ft_printf("\033[2J\033[H");
    
    // Show operation
    if (operation)
        ft_printf("%s🔄 %s%s\n", YELLOW, operation, RESET);
    
    // Show stacks
    print_both_stacks(ps->stack_a, ps->stack_b);
    ft_printf("Size A: %d, Size B: %d\n", ps->size_a, ps->size_b);
    
    // Delay
    if (delay_ms > 0)
        usleep(delay_ms * 1000);
}

// Execute a single operation for visualization
void execute_operation_for_visual(t_ps *ps, const char *operation)
{
    if (strcmp(operation, "sa") == 0)
        sa(ps);
    else if (strcmp(operation, "sb") == 0)
        sb(ps);
    else if (strcmp(operation, "ss") == 0)
        ss(ps);
    else if (strcmp(operation, "pa") == 0)
        pa(ps);
    else if (strcmp(operation, "pb") == 0)
        pb(ps);
    else if (strcmp(operation, "ra") == 0)
        ra(ps);
    else if (strcmp(operation, "rb") == 0)
        rb(ps);
    else if (strcmp(operation, "rr") == 0)
        rr(ps);
    else if (strcmp(operation, "rra") == 0)
        rra(ps);
    else if (strcmp(operation, "rrb") == 0)
        rrb(ps);
    else if (strcmp(operation, "rrr") == 0)
        rrr(ps);
}

// Replay all recorded operations with visualization
void replay_operations(t_ps *ps, int delay_ms)
{
    ft_printf("Replaying %d operations...\n", g_recorder.count);
    ft_printf("Press Enter to start visualization...\n");
    getchar();
    
    show_frame(ps, "INITIAL STATE", delay_ms);
    
    t_operation *current = g_recorder.operations;
    int step = 1;
    
    while (current)
    {
        execute_operation_for_visual(ps, current->name);
        
        char step_info[100];
        snprintf(step_info, sizeof(step_info), "Step %d: %s", step, current->name);
        show_frame(ps, step_info, delay_ms);
        
        current = current->next;
        step++;
    }
    
    if (is_sorted(ps->stack_a))
        show_frame(ps, "SORTING COMPLETE - SUCCESS!", delay_ms);
    else
        show_frame(ps, "SORTING INCOMPLETE", delay_ms);
    
    ft_printf("\nVisualization complete. Operations count: %d\n", g_recorder.count);
}

// Function to create a copy of the push_swap structure for visualization
t_ps *copy_ps_structure(t_ps *original)
{
    t_ps *copy = malloc(sizeof(t_ps));
    if (!copy)
        return NULL;
    
    copy->stack_a = NULL;
    copy->stack_b = NULL;
    copy->size_a = 0;
    copy->size_b = 0;
    copy->total_size = original->total_size;
    
    // Copy stack A
    t_stack *current = original->stack_a;
    t_stack *prev = NULL;
    
    while (current)
    {
        t_stack *new_node = create_int_node(current->value);
        if (!new_node)
        {
            // Cleanup on error
            ft_stkclear(&copy->stack_a);
            free(copy);
            return NULL;
        }
        if (!copy->stack_a)
        {
            copy->stack_a = new_node;
            prev = new_node;
        }
        else
        {
            prev->next = new_node;
            prev = new_node;
        }
        
        copy->size_a++;
        current = current->next;
    }
    ft_printf("DEBUG: Finished copying stack_a (size %d)\n", copy->size_a);

    // Copy stack B (if it exists)
    current = original->stack_b;
    prev = NULL;
    
    while (current)
    {
        t_stack *new_node = create_int_node(current->value);
        if (!new_node)
        {
            // Cleanup on error
            ft_stkclear(&copy->stack_a);
            ft_stkclear(&copy->stack_b);
            free(copy);
            return NULL;
        }
        
        if (!copy->stack_b)
        {
            copy->stack_b = new_node;
            prev = new_node;
        }
        else
        {
            prev->next = new_node;
            prev = new_node;
        }
        
        copy->size_b++;
        current = current->next;
    }
    ft_printf("DEBUG: Finished copying stack_b (size %d)\n", copy->size_b);

    return copy;
}

// Function type for algorithms
typedef void (*algorithm_func_t)(t_ps *);

// Example algorithm for testing - you can replace this with your actual algorithm
void example_algorithm(t_ps *ps)
{
    // Simple example - just demonstrate recording
    if (ps->size_a > 1)
    {
        recorded_pb(ps);
        recorded_pa(ps);
        if (ps->size_a > 2)
        {
            recorded_ra(ps);
            recorded_ra(ps);
        }
    }
}

// Add this function to your micro_test.c file, after the other recorder functions

// Check if recording is active
int is_recording(void)
{
    return g_recorder.recording;
}

// Update the run_algorithm_with_visualization function to use your original radix_sort
void run_algorithm_with_visualization(t_ps *ps, void (*algorithm)(t_ps *), int delay_ms)
{
    // Create a copy for the algorithm to work on
    ft_printf("DEBUG: Creating copy of ps structure for algorithm\n");
    t_ps *algo_copy = copy_ps_structure(ps);
    if (!algo_copy)
    {
        ft_printf("Error: Could not create copy for algorithm\n");
        return;
    }
    
    ft_printf("DEBUG: Running algorithm...\n");
    
    // Print initial stack state
    t_stack *tmp = algo_copy->stack_a;
    int idx = 0;
    if (!tmp)
        ft_printf("DEBUG: algo_copy->stack_a is NULL\n");
    while (tmp)
    {
        ft_printf("DEBUG: algo_copy->stack_a[%d] = %d\n", idx, tmp->value);
        tmp = tmp->next;
        idx++;
    }
    tmp = algo_copy->stack_b;
    idx = 0;
    if (!tmp)
        ft_printf("DEBUG: algo_copy->stack_b is NULL\n");
    while (tmp)
    {
        ft_printf("DEBUG: algo_copy->stack_b[%d] = %d\n", idx, tmp->value);
        tmp = tmp->next;
        idx++;
    }

    // Initialize recorder
    ft_printf("DEBUG: Initializing recorder\n");
    init_recorder();
    start_recording();
    
    // Run the algorithm on the copy
    ft_printf("DEBUG: Calling algorithm function pointer\n");
    if (!algorithm)
    {
        ft_printf("ERROR: Algorithm function pointer is NULL\n");
        return;
    }
    ft_printf("DEBUG: About to call chunk_sort (or your algorithm)\n");
    algorithm(algo_copy);
    ft_printf("DEBUG: Algorithm function returned\n");
    
    // Stop recording
    stop_recording();
    ft_printf("DEBUG: Algorithm completed. %d operations recorded.\n", g_recorder.count);
    ft_printf("Algorithm is %s sorted\n", is_sorted(algo_copy->stack_a) ? "" : "not");
    
    // Print final stack state
    tmp = algo_copy->stack_a;
    idx = 0;
    if (!tmp)
        ft_printf("DEBUG: FINAL algo_copy->stack_a is NULL\n");
    while (tmp)
    {
        ft_printf("DEBUG: FINAL algo_copy->stack_a[%d] = %d\n", idx, tmp->value);
        tmp = tmp->next;
        idx++;
    }
    tmp = algo_copy->stack_b;
    idx = 0;
    if (!tmp)
        ft_printf("DEBUG: FINAL algo_copy->stack_b is NULL\n");
    while (tmp)
    {
        ft_printf("DEBUG: FINAL algo_copy->stack_b[%d] = %d\n", idx, tmp->value);
        tmp = tmp->next;
        idx++;
    }

    // Clean up algorithm copy
    ft_printf("DEBUG: Cleaning up algo_copy\n");
    ft_stkclear(&algo_copy->stack_a);
    ft_stkclear(&algo_copy->stack_b);
    free(algo_copy);
    
    // Ask user if they want to visualize
    ft_printf("Do you want to visualize the operations? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y')
    {
        ft_printf("DEBUG: Creating copy of ps structure for visualization\n");
        // Create another copy for visualization
        t_ps *visual_copy = copy_ps_structure(ps);
        if (!visual_copy)
        {
            ft_printf("Error: Could not create copy for visualization\n");
            cleanup_recorder();
            return;
        }
        
        ft_printf("DEBUG: Replaying operations with visualization...\n");
        // Replay operations with visualization
        replay_operations(visual_copy, delay_ms);
        
        // Clean up visualization copy
        ft_printf("DEBUG: Cleaning up visual_copy\n");
        ft_stkclear(&visual_copy->stack_a);
        ft_stkclear(&visual_copy->stack_b);
        free(visual_copy);
    }
    
    // Print operations list
    ft_printf("\nOperations list:\n");
    t_operation *current = g_recorder.operations;
    int count = 1;
    while (current)
    {
        ft_printf("%d: %s\n", count, current->name);
        current = current->next;
        count++;
    }
    cleanup_recorder();
}

// Update the main function to use your original radix_sort
#define MAX_INPUT 500

int main(int argc, char **argv)
{
    t_ps ps;
    int i;
    int delay_ms = 50; // Default delay

    // Initialize t_stack as array-based buffer
    t_stack stack_buffer;
    stack_buffer.top = 0;
    stack_buffer.capacity = MAX_INPUT;
    stack_buffer.bottom = 0;
    stack_buffer.element_count = 0;
    stack_buffer.size = 0;
    stack_buffer.is_circular = false;
    stack_buffer.next = NULL;
    stack_buffer.prev = NULL;
    // ...initialize other fields if needed...

    // Parse arguments into stack_buffer.buffer
    int start_idx = 1;
    if (argc > 2 && strcmp(argv[1], "--delay") == 0)
    {
        delay_ms = atoi(argv[2]);
        start_idx = 3;
    }
    int count = 0;
    for (i = argc - 1; i >= start_idx && count < MAX_INPUT; i--)
    {
        stack_buffer.buffer[count++] = ft_atoi(argv[i]);
    }
    stack_buffer.element_count = count;
    stack_buffer.size = count;

    // Set up ps to use the array-based stack
    ps.stack_a = &stack_buffer;
    ps.stack_b = NULL;
    ps.size_a = count;
    ps.size_b = 0;
    ps.total_size = count;

    // Now you can use ps.stack_a as an array-based stack in chunk algorithms

    run_algorithm_with_visualization(&ps, chunk_sort, delay_ms);

    // No need to free stack_buffer as it's on the stack

    return 0;
}
// Instructions for integrating with your existing code:
/*
TO USE THIS WITH YOUR EXISTING ALGORITHMS:

1. Create a new function that uses recorded_ operations:

```c
void my_radix_sort_visualized(t_ps *ps)
{
    // Copy your radix sort logic here, but use recorded_ functions
    // Instead of: pb(ps);  -> Use: recorded_pb(ps);
    // Instead of: ra(ps);  -> Use: recorded_ra(ps);
    // etc.
    
    // Example structure:
    int max_bits = get_max_bits(ps->stack_a);
    for (int bit = 0; bit < max_bits; bit++)
    {
        int size = ps->size_a;
        for (int i = 0; i < size; i++)
        {
            if (should_push_to_b(ps->stack_a, bit))
                recorded_pb(ps);  // Instead of pb(ps)
            else
                recorded_ra(ps);  // Instead of ra(ps)
        }
        while (ps->size_b > 0)
            recorded_pa(ps);  // Instead of pa(ps)
    }
}
```

2. Replace the example_algorithm call in main() with your function:
   run_algorithm_with_visualization(&ps, my_radix_sort_visualized, delay_ms);

3. Keep your original algorithm unchanged - this is just for visualization!

This way you don't modify your original radix_sort function, and you avoid
naming conflicts with existing functions in your codebase.
*/