/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:46:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 20:47:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ps.h"
# include "stack.h"
# include "algorithms.h"


//to verify the compatibility I need to know how organized is my data structure
// the size of the stack need to be by consequence into the struct of stack
static  int get_stack_size(t_stack *src);
static	int is_sorted(t_stack *src);
static void radix_sort_by_bit(t_ps *data, int bit_position);
static int	radix_find_min_position(t_ps *data, int size_a);
static void radix_process_all_bits(t_ps *data, int total_size);
static void radix_handle_small_arrays(t_ps *data);
static void radix_rotate_to_position(t_ps *data, int min_pos, int size_a);
static int  length_bit(int size);

void radix_sort(t_ps *data)
{
	int total_size;

	total_size = get_stack_size(&data->a);
	if (!data || total_size <= 3)
	{
		radix_handle_small_arrays(data);    // here maybe it's best to call that just do a best job than radix 
		return ;
	}
	if (is_sorted(data)) 
		return ;
	radix_process_all_bits(data, total_size);
	radix_final_rotation(data);
	
	if (verif)
}

static  int get_stack_size(t_stack *src)
{
	int count;

	count = 0;
	while (src)
	{
		count++;
		src =  src->next;
	}
	return (count);
}

/**
This function  is superuseful for radix sort when we're doing
a while loop to know the max_bits we need  to iterates through
what kind of output we expect ?
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
	int	bits;
	int	value;

	bits = 0;
	value = size - 1;
	while (value > 0)
	{
		value >>= 1;
		bits++;
	}
	return  (bits);
}

/**
This function rotates the stack so that the element  at position
`min_pos` end up at the top (index 0)
it will choses the shortest path between `ra` and `rra`
think of it like a circular playlist soong
we're ong song 0:
if we wanna jump on song 2:
--->  we scroll forward 2 times
if we wanna jump on song 8
<-- we scrool back two times
@param data entire jdata structure of stacks
@param min_pos index of the element  we want to bring to top
@param size_a current size of stack A
 */
void	turning_wheel(t_ps *data, int min_pos,  int size_a)
{
	int	i;

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



sort_two(t_ps *ps)
{
	sa(ps);
}

static int	find_min_position(t_ps *data,)
{
	
}

// alias radix_process_all_bits()
radix_sort_all_bits_passes(t_ps *data, int  total_size)
{
	int	max_bits;
	int	bit_position;

	max_bits = length_bit(total_size);
	bit_positiion = 0;
	while  (bit_position < max_bits)
	{
		radix_sort_single_bit_pass(data,  bit_position);
		bit_position++;
	}
}

static void	radix_sort_single_bit_pass(t_ps *data, int bit_position)
{
	int	total_elem;
	int	processed;
	int	curr_elem;
	int	zero_based_val;

	total_elements = get_stack_size(&data->a);
	processed = 0;
	while (processed < total_elements)
	{
		curr_elem = data->a.stack[data->a.top];
		zero_based_value = curr_elem - 1;
		if ((zero_based_value & (1 << bit_position)) == 0)
			pb(data);
		else
			ra(data);
		processed++;
	}
	while (get_stack_size(&data->b) > 0)
		pa(data);
}
