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
}
