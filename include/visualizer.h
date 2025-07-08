#ifndef VISUALIZER_H
# define VISUZALIZER_H

typedef struct s_operation
{
    char *name;
    struct s_operation *next;
} t_operation;

typedef struct s_test_context
{
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

# endif