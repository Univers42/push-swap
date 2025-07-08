#include "push_swap.h"
#include "algorithms.h"

void	sort_two(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
	{
		move_from_to(data, to_sort->loc, TOP_A);
		move_from_to(data, to_sort->loc, TOP_A);
	}
	if (get_stack_element_at_position(&data->a, 1)
		> get_stack_element_at_position(&data->a, 2))
		sa(data);
	to_sort->size -= 2;
}
