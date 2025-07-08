#include "ps.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/* ========================================================================== */
/*                           SINGLETON RECORDER                               */
/* ========================================================================== */

typedef struct s_operation {
    char *name;
    struct s_operation *next;
} t_operation;

typedef struct s_test_context {
    // Recorder data
    t_operation *operations;
    t_operation *last_op;
    int op_count;
    int is_recording;
    
    // Test configuration
    int delay_ms;
    int verbose_mode;
    
    // Test data structure
    t_ps *test_ps;
} t_test_context;

// Singleton instance
static t_test_context *get_test_context(void)
{
    static t_test_context context = {
        .operations = NULL,
        .last_op = NULL,
        .op_count = 0,
        .is_recording = 0,
        .delay_ms = 50,
        .verbose_mode = 0,
        .test_ps = NULL
    };
    return &context;
}

/* ========================================================================== */
/*                           RECORDER FUNCTIONS                               */
/* ========================================================================== */

void init_recorder(void)
{
    t_test_context *ctx = get_test_context();
    
    // Clean up any existing operations
    cleanup_recorder();
    
    ctx->operations = NULL;
    ctx->last_op = NULL;
    ctx->op_count = 0;
    ctx->is_recording = 1;
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

/* ========================================================================== */
/*                         VISUALIZATION FUNCTIONS                            */
/* ========================================================================== */

void print_array_stack(t_stack *stack, char name)
{
    ft_printf("%s%s╔══ Stack %c ══╗%s\n", BOLD, CYAN, name, RESET);
    if (!stack || stack->element_count == 0)
    {
        ft_printf("%s║  (empty)    ║%s\n", DIM, RESET);
        ft_printf("%s╚═════════════╝%s\n\n", CYAN, RESET);
        return;
    }
    
    for (int i = 0; i < stack->element_count; i++)
    {
        ft_printf("%s║%s %s[%s%d%s]%s      %s║%s\n", 
                  CYAN, RESET, YELLOW, BRIGHT_YELLOW, 
                  stack->stack[i], YELLOW, RESET, CYAN, RESET);
    }
    ft_printf("%s╚═════════════╝%s\n\n", CYAN, RESET);
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
        sprintf(temp, "[%d]", stack_a->stack[i]);
        int len = strlen(temp);
        if (len > max_width_a)
            max_width_a = len;
    }
    
    // Find maximum width needed for stack B
    for (int i = 0; i < stack_b->element_count; i++)
    {
        char temp[20];
        sprintf(temp, "[%d]", stack_b->stack[i]);
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
            ft_printf("%s[%d]%s", BRIGHT_YELLOW, stack_a->stack[i], RESET);
            char temp[20];
            sprintf(temp, "[%d]", stack_a->stack[i]);
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
            ft_printf("%s[%d]%s", BRIGHT_MAGENTA, stack_b->stack[i], RESET);
            char temp[20];
            sprintf(temp, "[%d]", stack_b->stack[i]);
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
    
    ft_printf("\033[2J\033[H"); // Clear screen
    
    if (operation)
        ft_printf("%s🔄 %s%s\n", YELLOW, operation, RESET);
    
    print_both_array_stacks(&ps->stack_a, &ps->stack_b);
    ft_printf("Size A: %d, Size B: %d\n", 
             ps->stack_a.element_count, ps->stack_b.element_count);
    
    if (ctx->delay_ms > 0)
        usleep(ctx->delay_ms * 1000);
}

/* ========================================================================== */
/*                      ALGORITHM EXECUTION WITH REPLAY                       */
/* ========================================================================== */

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
    
    // Initialize array-based stacks
    init_stack(&copy->stack_a, original->stack_a.capacity);
    init_stack(&copy->stack_b, original->stack_b.capacity);
    
    // Copy stack A data
    for (int i = 0; i < original->stack_a.element_count; i++)
        copy->stack_a.stack[i] = original->stack_a.stack[i];
    copy->stack_a.element_count = original->stack_a.element_count;
    
    // Copy stack B data
    for (int i = 0; i < original->stack_b.element_count; i++)
        copy->stack_b.stack[i] = original->stack_b.stack[i];
    copy->stack_b.element_count = original->stack_b.element_count;
    
    copy->total_size = original->total_size;
    copy->recording = false;  // Initialize recording flag
    
    // Don't copy the op_buffer - let each copy have its own
    
    return copy;
}

void replay_operations(t_ps *ps)
{
    t_test_context *ctx = get_test_context();
    
    ft_printf("\n📼 Replaying %d operations...\n", ctx->op_count);
    ft_printf("Press Enter to start visualization...\n");
    getchar();
    
    show_frame(ps, "🏁 INITIAL STATE");
    
    t_operation *current = ctx->operations;
    int step = 1;
    
    while (current)
    {
        execute_operation_for_visual(ps, current->name);
        
        char step_info[100];
        snprintf(step_info, sizeof(step_info), "Step %d: %s", step, current->name);
        show_frame(ps, step_info);
        
        current = current->next;
        step++;
    }
    
    if (is_sorted(&ps->stack_a) && ps->stack_b.element_count == 0)
        show_frame(ps, "✅ SORTING COMPLETE - SUCCESS!");
    else
        show_frame(ps, "❌ SORTING INCOMPLETE");
    
    ft_printf("\n📊 Visualization complete. Operations count: %d\n", ctx->op_count);
}

void run_algorithm_with_visualization(t_ps *ps, void (*algorithm)(t_ps *))
{
    t_test_context *ctx = get_test_context();
    
    // Create a copy for algorithm execution
    t_ps *algo_copy = create_ps_copy(ps);
    if (!algo_copy)
    {
        ft_printf("❌ Error: Could not create copy for algorithm\n");
        return;
    }
    
    // Initialize and enable recording in the copy
    init_op_buffer(&algo_copy->op_buffer, MAX_OPERATIONS);
    algo_copy->recording = true;
    
    // Run the algorithm
    ft_printf("🚀 Running algorithm...\n");
    algorithm(algo_copy);
    
    ft_printf("✅ Algorithm completed. %d operations recorded.\n", algo_copy->op_buffer.count);
    ft_printf("📊 Final state: %s\n", 
             is_sorted(&algo_copy->stack_a) ? "SORTED" : "NOT SORTED");
    
    // Ask for visualization
    ft_printf("\n🎬 Do you want to visualize the operations? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y')
    {
        t_ps *visual_copy = create_ps_copy(ps);
        if (!visual_copy)
        {
            ft_printf("❌ Error: Could not create copy for visualization\n");
            free_op_buffer(&algo_copy->op_buffer);
            free_stack(&algo_copy->stack_a);
            free_stack(&algo_copy->stack_b);
            free(algo_copy);
            return;
        }
        
        // Replay operations from buffer
        ft_printf("\n📼 Replaying %d operations from buffer...\n", algo_copy->op_buffer.count);
        ft_printf("Press Enter to start visualization...\n");
        getchar();
        getchar(); // Extra getchar for the newline
        
        show_frame(visual_copy, "🏁 INITIAL STATE");
        
        for (int i = 0; i < algo_copy->op_buffer.count; i++)
        {
            execute_operation_for_visual(visual_copy, algo_copy->op_buffer.operations[i]);
            
            char step_info[100];
            snprintf(step_info, sizeof(step_info), "Step %d: %s", i + 1, algo_copy->op_buffer.operations[i]);
            show_frame(visual_copy, step_info);
        }
        
        if (is_sorted(&visual_copy->stack_a) && visual_copy->stack_b.element_count == 0)
            show_frame(visual_copy, "✅ SORTING COMPLETE - SUCCESS!");
        else
            show_frame(visual_copy, "❌ SORTING INCOMPLETE");
        
        // Clean up visualization copy
        free_stack(&visual_copy->stack_a);
        free_stack(&visual_copy->stack_b);
        free(visual_copy);
    }
    
    // Print operations list if verbose
    if (ctx->verbose_mode)
    {
        ft_printf("\n📝 Operations list from buffer:\n");
        for (int i = 0; i < algo_copy->op_buffer.count; i++)
        {
            ft_printf("%3d: %s\n", i + 1, algo_copy->op_buffer.operations[i]);
        }
    }
    
    // Clean up algorithm copy
    free_op_buffer(&algo_copy->op_buffer);
    free_stack(&algo_copy->stack_a);
    free_stack(&algo_copy->stack_b);
    free(algo_copy);
}

/* ========================================================================== */
/*                              MAIN FUNCTION                                 */
/* ========================================================================== */

int main(int argc, char **argv)
{
    t_test_context *ctx = get_test_context();
    t_ps ps;
    int start_idx = 1;
    
    // Parse command line options
    while (start_idx < argc && argv[start_idx][0] == '-')
    {
        if (strcmp(argv[start_idx], "--delay") == 0 && start_idx + 1 < argc)
        {
            ctx->delay_ms = atoi(argv[++start_idx]);
            start_idx++;
        }
        else if (strcmp(argv[start_idx], "--verbose") == 0)
        {
            ctx->verbose_mode = 1;
            start_idx++;
        }
        else
        {
            ft_printf("Unknown option: %s\n", argv[start_idx]);
            return 1;
        }
    }
    
    if (argc - start_idx < 1)
    {
        ft_printf("Usage: %s [--delay ms] [--verbose] <numbers...>\n", argv[0]);
        return 1;
    }
    
    // Initialize stacks
    int count = argc - start_idx;
    init_stack(&ps.stack_a, count);
    init_stack(&ps.stack_b, count);
    
    // Load numbers into stack A
    for (int i = start_idx; i < argc; i++)
    {
        ps.stack_a.stack[ps.stack_a.element_count++] = ft_atoi(argv[i]);
    }
    ps.total_size = ps.stack_a.element_count;
    
    ft_printf("🎯 Testing with %d numbers\n", ps.total_size);
    
    // Run algorithm with visualization
    run_algorithm_with_visualization(&ps, chunk_sort);
    
    // Cleanup
    free_stack(&ps.stack_a);
    free_stack(&ps.stack_b);
    
    return 0;
}