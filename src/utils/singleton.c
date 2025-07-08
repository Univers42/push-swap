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
