#include "push_swap.h"

// ...existing code...

void	chunk_sort(t_ps *data)
{
	t_chunk	chunk_all;

	chunk_all.loc = TOP_A;
	chunk_all.size = data->a.capacity;
	rec_chunk_sort(data, &chunk_all);
}

void	sort(t_ps *data)
{
	t_chunk	to_sort;
	int		total_size;

	total_size = get_current_stack_size(&data->a);
	if (total_size <= 3)
	{
		if (total_size == 3)
			sort_three_simple(data);
		else if (total_size == 2)
		{
			if (get_stack_element_at_position(&data->a, 1)
				> get_stack_element_at_position(&data->a, 2))
				sa(data);
		}
		return ;
	}
	if (verify_stack_is_sorted(data))
		return ;
	to_sort.loc = TOP_A;
	to_sort.size = total_size;
	rec_chunk_sort(data, &to_sort);
}
// ...existing code...