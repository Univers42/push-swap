#include "ps.h"

static void radix_sort_single_bit_pass(t_ps *data, int bit_position);
static int length_bit(int size);
static void turning_wheel(t_ps *data, int min_pos, int size_a);
static void radix_handle_small_arrays(t_ps *data);
static int find_min_position_radix(t_ps *data);
static void normalize_values(t_ps *data);
static int get_normalized_value(t_ps *data, int value);

void radix_sort(t_ps *data)
{
    int total_size;

    if (!data || !data->stack_a)
        return;

    total_size = get_stack_size(data->stack_a);

    if (total_size <= 3)
    {
        radix_handle_small_arrays(data);
        return;
    }
    if (is_sorted(data->stack_a))
        return;
    // Normalize values to ranks (0, 1, 2, ..., n-1)
    normalize_values(data);
    
    int max_bits = length_bit(total_size);
    for (int i = 0; i < max_bits; i++)
        radix_sort_single_bit_pass(data, i);

    int min_pos = find_min_position_radix(data);
    turning_wheel(data, min_pos, get_stack_size(data->stack_a));
}

/**
This function is super useful for radix sort when we're doing
a while loop to know the max_bits we need to iterate through
what kind of output we expect?
Decimal  |  Binary   |  Bits Needed
-------- | --------- | -------------
  0      |   0       | 1 bit (if you count just the 0)
  1      |   1       | 1 bit
  2      |  10       | 2 bits
  3      |  11       | 2 bits
  4      | 100       | 3 bits
  7      | 111       | 3 bits
  8      |1000       | 4 bits
  9      |1001       | 4 bits
 10      |1010       | 4 bits 
 */
static int length_bit(int size)
{
    int bits = 0;
    int value = size - 1;
    
    if (value == 0)
        return 1;
    
    while (value > 0)
    {
        value >>= 1;
        bits++;
    }
    return bits;
}

/**
This function rotates the stack so that the element at position
`min_pos` ends up at the top (index 0)
it will choose the shortest path between `ra` and `rra`
think of it like a circular playlist song
we're on song 0:
if we wanna jump on song 2:
--->  we scroll forward 2 times
if we wanna jump on song 8
<-- we scroll back two times
@param data entire data structure of stacks
@param min_pos index of the element we want to bring to top
@param size_a current size of stack A
 */
static void turning_wheel(t_ps *data, int min_pos, int size_a)
{
    int i;

    if (min_pos <= size_a / 2)
    {
        i = -1;
        while (++i < min_pos)
            ra(data);
    }
    else
    {
        i = -1;
        while (++i < size_a - min_pos)
            rra(data);
    }
}

// Helper function to find minimum position for radix sort
static int find_min_position_radix(t_ps *data)
{
    t_list *tmp = data->stack_a;
    int min = *(int *)tmp->content;
    int min_pos = 0;
    int i = 0;

    while (tmp)
    {
        if (*(int *)tmp->content < min)
        {
            min = *(int *)tmp->content;
            min_pos = i;
        }
        tmp = tmp->next;
        i++;
    }
    return min_pos;
}

// Does a full pass for one bit position using bit masking
static void radix_sort_single_bit_pass(t_ps *data, int bit_position)
{
    int total_elements = get_stack_size(data->stack_a);
    int processed = 0;

    while (processed < total_elements)
    {
        int normalized_value = get_normalized_value(data, *(int *)data->stack_a->content);
        
        // Check if the bit at bit_position is 0
        if ((normalized_value & (1 << bit_position)) == 0)
            pb(data);
        else
            ra(data);
        processed++;
    }

    // Move all elements back from stack B to stack A
    while (get_stack_size(data->stack_b) > 0)
        pa(data);
}

// Take care of the 2-3 element edge cases
static void radix_handle_small_arrays(t_ps *data)
{
    int size = get_stack_size(data->stack_a);

    if (size == 2 && *(int *)data->stack_a->content > *(int *)data->stack_a->next->content)
        sa(data);
    else if (size == 3)
        sort_three(data);
}

// Normalize values to their ranks (0, 1, 2, ..., n-1)
static void normalize_values(t_ps *data)
{
    int size = get_stack_size(data->stack_a);
    int *values = malloc(sizeof(int) * size);
    int *sorted_values = malloc(sizeof(int) * size);
    t_list *tmp = data->stack_a;
    int i = 0;

    // Extract all values
    while (tmp)
    {
        values[i] = *(int *)tmp->content;
        sorted_values[i] = *(int *)tmp->content;
        tmp = tmp->next;
        i++;
    }

    // Sort the copy to find ranks
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (sorted_values[j] > sorted_values[j + 1])
            {
                int temp = sorted_values[j];
                sorted_values[j] = sorted_values[j + 1];
                sorted_values[j + 1] = temp;
            }
        }
    }

    // Replace values with their ranks
    tmp = data->stack_a;
    i = 0;
    while (tmp)
    {
        int original_value = *(int *)tmp->content;
        int rank = 0;
        
        // Find the rank of this value
        for (int j = 0; j < size; j++)
        {
            if (sorted_values[j] == original_value)
            {
                rank = j;
                break;
            }
        }
        
        *(int *)tmp->content = rank;
        tmp = tmp->next;
        i++;
    }

    free(values);
    free(sorted_values);
}

// Get the normalized value (rank) for a given original value
static int get_normalized_value(t_ps *data, int value)
{
    (void)data;
    // Since we already normalized in normalize_values(), 
    // the value parameter is already the normalized value
    return value;
}