#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "push_swap.h"
#include "algorithms.h"

int		backtrack_sort(t_ps *data, int max_size);
void	backtrack_sort_chunk(t_ps *data, t_chunk *to_sort);
void	enhanced_sort_three_with_backtrack(t_ps *data);

#endif
