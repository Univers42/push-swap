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
