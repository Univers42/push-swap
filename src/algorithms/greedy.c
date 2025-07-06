#include "ps.h"

typedef struct s_greedy_node 
{
	int	value;
	int	index;
	int	target_pos;
	int	cost_a;
	int	cost_b;
	int	total_cost;
}			t_greedy_node;

/* Static function prototypes */
static void	greedy_push_to_b(t_ps *data);
static void	greedy_push_back_to_a(t_ps *data);
static void	greedy_final_rotation(t_ps *data);
static void	rotation_a(t_ps *data, int moves_a, bool rotate_a_up);
static void	rotation_b(t_ps *data, int moves_b, bool rotate_b_up);
static void	greedy_execute_combined_and_remaining(t_ps *data, int moves_a, 
		int moves_b, t_greedy_node *node);
static void	greedy_rotate_to_top(t_ps *data, int min_pos, int size_a);
static void	greedy_execute_move(t_ps *data, t_greedy_node *node);
static void	greedy_push_element_strategically(t_ps *data, int current, 
		int total_size);
static void	greedy_calculate_costs(t_ps *data, t_greedy_node *nodes, 
		int size_b);
static void	greedy_calculate_move_costs(t_greedy_node *node, int size_a, 
		int size_b);
static int	greedy_find_target_position(t_ps *data, int value);
static int	greedy_find_best_target(t_ps *data, int value, int size_a);
static int	greedy_find_min_target(t_ps *data, int size_a);
static int	greedy_calculate_total_cost(int cost_a, int cost_b, int pos_a, 
		int pos_b, int size_a, int size_b);
static int	find_min_value_in_stack(t_list *stack);
static int	greedy_find_cheapest(t_greedy_node *nodes, int size);
static int	greedy_find_min_pos(t_ps *data, int size_a, int min_value);
static int	get_value_at_position(t_list *stack, int position);
void	sort_three_simple(t_ps *data);

/*
** greedy_sort - Main sorting function using greedy algorithm
** @data: pointer to push_swap data structure containing both stacks
**
** This function implements the greedy sorting algorithm for push_swap.
** It handles edge cases for small stacks (size <= 3) and delegates
** the sorting process to specialized functions for larger stacks.
** The algorithm consists of three main phases:
** 1. Push elements strategically to stack B
** 2. Push elements back to stack A optimally
** 3. Final rotation to get minimum element at top
*/
void	greedy_sort(t_ps *data)
{
	int	size;

	size = get_stack_size(data->stack_a);
	if (!data || size <= 3)
	{
		if (size == 3)
			sort_three(data);
		else if (size == 2
			&& get_value_at_position(data->stack_a, 1)
			> get_value_at_position(data->stack_a, 2))
			sa(data);
		return ;
	}
	if (is_sorted(data->stack_a))
		return ;
	greedy_push_to_b(data);
	greedy_push_back_to_a(data);
	greedy_final_rotation(data);
}

/*
** greedy_push_to_b - Push elements from stack A to stack B strategically
** @data: pointer to push_swap data structure
**
** This function pushes elements from stack A to stack B using a strategic
** approach. It always pushes the first two elements, then analyzes each
** remaining element to determine the optimal push strategy based on value
** ranges. Elements are distributed to optimize future moves.
*/
static void	greedy_push_to_b(t_ps *data)
{
	int	total_size;
	int	current;

	total_size = get_stack_size(data->stack_a);
	if (total_size > 3)
	{
		pb(data);
		pb(data);
	}
	while (get_stack_size(data->stack_a) > 3)
	{
		current = get_value_at_position(data->stack_a, 1);
		greedy_push_element_strategically(data, current, total_size);
	}
	if (get_stack_size(data->stack_a) == 3)
		sort_three(data);
}

/*
** greedy_push_back_to_a - Push all elements from stack B back to stack A
** @data: pointer to push_swap data structure
**
** This function pushes all elements from stack B back to stack A using
** the greedy algorithm. For each iteration, it calculates the cost of
** moving each element in stack B to its optimal position in stack A,
** then executes the move with the lowest total cost.
*/
static void	greedy_push_back_to_a(t_ps *data)
{
	t_greedy_node	*nodes;
	int				size_b;
	int				cheapest_idx;

	while (get_stack_size(data->stack_b) > 0)
	{
		size_b = get_stack_size(data->stack_b);
		nodes = malloc(sizeof(t_greedy_node) * size_b);
		if (!nodes)
			return ;
		greedy_calculate_costs(data, nodes, size_b);
		cheapest_idx = greedy_find_cheapest(nodes, size_b);
		greedy_execute_move(data, &nodes[cheapest_idx]);
		free(nodes);
	}
}

/*
** greedy_final_rotation - Rotate stack A to put minimum element at top
** @data: pointer to push_swap data structure
**
** This function performs the final rotation of stack A to ensure the
** minimum element is at the top, resulting in a fully sorted stack.
** It finds the minimum value and its position, then rotates efficiently.
*/
static void	greedy_final_rotation(t_ps *data)
{
	int	min_value;
	int	min_pos;
	int	size_a;

	min_value = find_min_value_in_stack(data->stack_a);
	size_a = get_stack_size(data->stack_a);
	min_pos = greedy_find_min_pos(data, size_a, min_value);
	greedy_rotate_to_top(data, min_pos, size_a);
}

/*
** greedy_execute_move - Execute the optimal move for a given node
** @data: pointer to push_swap data structure
** @node: pointer to the greedy node containing move information
**
** This function executes the complete move sequence for pushing an element
** from stack B to stack A. It handles both individual and combined rotations
** to minimize the total number of operations, then pushes the element.
*/
static void	greedy_execute_move(t_ps *data, t_greedy_node *node)
{
	int	moves_a;
	int	moves_b;

	moves_a = node->cost_a;
	moves_b = node->cost_b;
	greedy_execute_combined_and_remaining(data, moves_a, moves_b, node);
	pa(data);
}

/*
** rotation_a - Perform rotations on stack A
** @data: pointer to push_swap data structure
** @moves_a: number of rotations to perform
** @rotate_a_up: true for ra (rotate up), false for rra (rotate down)
**
** This function performs the specified number of rotations on stack A
** in the direction determined by rotate_a_up parameter.
*/
static void	rotation_a(t_ps *data, int moves_a, bool rotate_a_up)
{
	while (moves_a > 0)
	{
		if (rotate_a_up)
			ra(data);
		else
			rra(data);
		moves_a--;
	}
}

/*
** rotation_b - Perform rotations on stack B
** @data: pointer to push_swap data structure
** @moves_b: number of rotations to perform
** @rotate_b_up: true for rb (rotate up), false for rrb (rotate down)
**
** This function performs the specified number of rotations on stack B
** in the direction determined by rotate_b_up parameter.
*/
static void	rotation_b(t_ps *data, int moves_b, bool rotate_b_up)
{
	while (moves_b > 0)
	{
		if (rotate_b_up)
			rb(data);
		else
			rrb(data);
		moves_b--;
	}
}

/*
** greedy_execute_combined_and_remaining - Execute combined and remaining moves
** @data: pointer to push_swap data structure
** @moves_a: number of moves needed for stack A
** @moves_b: number of moves needed for stack B
** @node: pointer to greedy node containing position information
**
** This function optimizes rotation operations by performing combined
** rotations (rr or rrr) when both stacks need to rotate in the same
** direction, then performs any remaining individual rotations.
*/
static void	greedy_execute_combined_and_remaining(t_ps *data, int moves_a,
		int moves_b, t_greedy_node *node)
{
	int		size_a;
	int		size_b;
	bool	rotate_a_up;
	bool	rotate_b_up;

	size_a = get_stack_size(data->stack_a);
	size_b = get_stack_size(data->stack_b);
	rotate_a_up = (node->target_pos <= size_a / 2);
	rotate_b_up = (node->index <= size_b / 2);
	while (moves_a > 0 && moves_b > 0 && rotate_a_up == rotate_b_up)
	{
		if (rotate_a_up)
			rr(data);
		else
			rrr(data);
		moves_a--;
		moves_b--;
	}
	rotation_a(data, moves_a, rotate_a_up);
	rotation_b(data, moves_b, rotate_b_up);
}

/*
** greedy_rotate_to_top - Rotate stack A to bring element to top
** @data: pointer to push_swap data structure
** @min_pos: position of the element to bring to top
** @size_a: size of stack A
**
** This function efficiently rotates stack A to bring the element at
** min_pos to the top. It chooses the shorter rotation path (up or down).
*/
static void	greedy_rotate_to_top(t_ps *data, int min_pos, int size_a)
{
	if (min_pos <= size_a / 2)
	{
		while (min_pos > 0)
		{
			ra(data);
			min_pos--;
		}
	}
	else
	{
		min_pos = size_a - min_pos;
		while (min_pos > 0)
		{
			rra(data);
			min_pos--;
		}
	}
}

/*
** greedy_find_target_position - Find target position for a value in stack A
** @data: pointer to push_swap data structure
** @value: value to find target position for
**
** This function finds the optimal position in stack A where the given
** value should be inserted to maintain sorted order. It first looks for
** the best target (smallest value greater than the given value), and
** falls back to the minimum value position if no such target exists.
**
** Return: target position index in stack A
*/
static int	greedy_find_target_position(t_ps *data, int value)
{
	int	size_a;
	int	target_pos;

	size_a = get_stack_size(data->stack_a);
	target_pos = greedy_find_best_target(data, value, size_a);
	if (target_pos == -1)
		target_pos = greedy_find_min_target(data, size_a);
	return (target_pos);
}

/*
** greedy_find_best_target - Find the best target position for a value
** @data: pointer to push_swap data structure
** @value: value to find target for
** @size_a: size of stack A
**
** This function finds the position of the smallest value in stack A
** that is greater than the given value. This represents the optimal
** insertion point to maintain sorted order.
**
** Return: position index of best target, or -1 if no target found
*/
static int	greedy_find_best_target(t_ps *data, int value, int size_a)
{
	int	best_target;
	int	target_pos;
	int	current_value;
	int	i;

	best_target = 2147483647;
	target_pos = -1;
	i = 1;
	while (i <= size_a)
	{
		current_value = get_value_at_position(data->stack_a, i);
		if (current_value > value && current_value < best_target)
		{
			best_target = current_value;
			target_pos = i - 1;
		}
		i++;
	}
	return (target_pos);
}

/*
** greedy_find_min_target - Find position of minimum value in stack A
** @data: pointer to push_swap data structure
** @size_a: size of stack A
**
** This function finds the position of the minimum value in stack A.
** This is used as a fallback target position when no suitable target
** is found by greedy_find_best_target.
**
** Return: position index of minimum value in stack A
*/
static int	greedy_find_min_target(t_ps *data, int size_a)
{
	int	min_value;
	int	target_pos;
	int	i;

	min_value = find_min_value_in_stack(data->stack_a);
	target_pos = 0;
	i = 1;
	while (i <= size_a)
	{
		if (get_value_at_position(data->stack_a, i) == min_value)
		{
			target_pos = i - 1;
			break ;
		}
		i++;
	}
	return (target_pos);
}

/*
** greedy_calculate_total_cost - Calculate total cost of a move
** @cost_a: cost of moving in stack A
** @cost_b: cost of moving in stack B
** @pos_a: position in stack A
** @pos_b: position in stack B
** @size_a: size of stack A
** @size_b: size of stack B
**
** This function calculates the total cost of a move operation.
** If both stacks rotate in the same direction, the cost is the maximum
** of the two costs (due to combined operations). Otherwise, it's the sum.
**
** Return: total cost of the move operation
*/
static int	greedy_calculate_total_cost(int cost_a, int cost_b, int pos_a, 
		int pos_b, int size_a, int size_b)
{
	bool	rotate_a_up;
	bool	rotate_b_up;

	rotate_a_up = (pos_a <= size_a / 2);
	rotate_b_up = (pos_b <= size_b / 2);
	if (rotate_a_up == rotate_b_up)
	{
		if (cost_a > cost_b)
			return (cost_a);
		else
			return (cost_b);
	}
	return (cost_a + cost_b);
}

/*
** sort_three_simple - Sort exactly three elements in stack A
** @data: pointer to push_swap data structure
**
** This function sorts exactly three elements using the minimum number
** of operations. It handles all possible permutations of three elements
** and applies the appropriate sequence of operations.
*/
void	sort_three_simple(t_ps *data)
{
	int	first;
	int	second;
	int	third;

	if (get_stack_size(data->stack_a) != 3)
		return ;
	first = get_value_at_position(data->stack_a, 1);
	second = get_value_at_position(data->stack_a, 2);
	third = get_value_at_position(data->stack_a, 3);
	if (first > second && second < third && first < third)
		sa(data);
	else if (first > second && second > third)
	{
		sa(data);
		rra(data);
	}
	else if (first > second && second < third && first > third)
		ra(data);
	else if (first < second && second > third && first < third)
	{
		sa(data);
		ra(data);
	}
	else if (first < second && second > third && first > third)
		rra(data);
}

/*
** find_min_value_in_stack - Find minimum value in a stack
** @stack: pointer to stack (t_list)
**
** This function iterates through the entire stack to find the minimum
** value. It handles empty stacks by returning 0.
**
** Return: minimum value in the stack, or 0 if stack is empty
*/
static int	find_min_value_in_stack(t_list *stack)
{
	int		min_value;
	int		stack_size;
	int		i;
	int		current_value;

	stack_size = get_stack_size(stack);
	if (stack_size == 0)
		return (0);
	min_value = get_value_at_position(stack, 1);
	i = 2;
	while (i <= stack_size)
	{
		current_value = get_value_at_position(stack, i);
		if (current_value < min_value)
			min_value = current_value;
		i++;
	}
	return (min_value);
}

/*
** greedy_push_element_strategically - Push element with strategic positioning
** @data: pointer to push_swap data structure
** @current: current element value being pushed
** @total_size: total size of the original stack
**
** This function pushes an element to stack B and positions it strategically
** based on its value relative to the total range. Small values are rotated
** in stack B to optimize future operations.
*/
static void	greedy_push_element_strategically(t_ps *data, int current,
		int total_size)
{
	if (current <= total_size / 3)
	{
		pb(data);
		if (get_stack_size(data->stack_b) > 1)
			rb(data);
	}
	else if (current >= 2 * total_size / 3)
	{
		pb(data);
	}
	else
	{
		pb(data);
		if (get_stack_size(data->stack_b) > 1
			&& get_value_at_position(data->stack_b, 1) < total_size / 2)
			rb(data);
	}
}

/*
** greedy_calculate_costs - Calculate costs for all elements in stack B
** @data: pointer to push_swap data structure
** @nodes: array of greedy nodes to populate
** @size_b: size of stack B
**
** This function calculates the cost of moving each element in stack B
** to its optimal position in stack A. It populates the nodes array
** with all necessary information for making optimal move decisions.
*/
static void	greedy_calculate_costs(t_ps *data, t_greedy_node *nodes, int size_b)
{
	int	size_a;
	int	i;

	size_a = get_stack_size(data->stack_a);
	i = 0;
	while (i < size_b)
	{
		nodes[i].value = get_value_at_position(data->stack_b, i + 1);
		nodes[i].index = i;
		nodes[i].target_pos = greedy_find_target_position(data, nodes[i].value);
		greedy_calculate_move_costs(&nodes[i], size_a, size_b);
		i++;
	}
}

/*
** greedy_calculate_move_costs - Calculate individual move costs for a node
** @node: pointer to greedy node to calculate costs for
** @size_a: size of stack A
** @size_b: size of stack B
**
** This function calculates the individual costs for moving an element
** from its current position in stack B to its target position in stack A.
** It considers the shorter rotation path for both stacks.
*/
static void	greedy_calculate_move_costs(t_greedy_node *node, int size_a, 
		int size_b)
{
	if (node->index <= size_b / 2)
		node->cost_b = node->index;
	else
		node->cost_b = size_b - node->index;
	if (node->target_pos <= size_a / 2)
		node->cost_a = node->target_pos;
	else
		node->cost_a = size_a - node->target_pos;
	node->total_cost = greedy_calculate_total_cost(node->cost_a, node->cost_b,
			node->target_pos, node->index, size_a, size_b);
}

/*
** greedy_find_cheapest - Find the node with minimum total cost
** @nodes: array of greedy nodes
** @size: number of nodes in the array
**
** This function finds the index of the node with the minimum total cost.
** This represents the optimal move to make in the current iteration.
**
** Return: index of the cheapest node
*/
static int	greedy_find_cheapest(t_greedy_node *nodes, int size)
{
	int	cheapest_idx;
	int	min_cost;
	int	i;

	cheapest_idx = 0;
	min_cost = nodes[0].total_cost;
	i = 1;
	while (i < size)
	{
		if (nodes[i].total_cost < min_cost)
		{
			min_cost = nodes[i].total_cost;
			cheapest_idx = i;
		}
		i++;
	}
	return (cheapest_idx);
}

/*
** greedy_find_min_pos - Find position of minimum value in stack A
** @data: pointer to push_swap data structure
** @size_a: size of stack A
** @min_value: minimum value to find position for
**
** This function finds the position of the specified minimum value
** in stack A. Used during final rotation to position the minimum
** element at the top of the stack.
**
** Return: position index of the minimum value (0-based)
*/
static int	greedy_find_min_pos(t_ps *data, int size_a, int min_value)
{
	int	min_pos;
	int	i;

	min_pos = 0;
	i = 1;
	while (i <= size_a)
	{
		if (get_value_at_position(data->stack_a, i) == min_value)
		{
			min_pos = i - 1;
			break ;
		}
		i++;
	}
	return (min_pos);
}

/*
** get_value_at_position - Get value at specific position in stack
** @stack: pointer to stack (t_list)
** @position: position to get value from (1-based)
**
** This function retrieves the value at a specific position in the stack.
** Position 1 is the top of the stack.
**
** Return: value at the specified position
@note 
must cast the value first into a pointer integer and then dereference it to
comply modernn compiler
*/
static int	get_value_at_position(t_list *stack, int position)
{
	t_list	*current;
	int		i;

	if (!stack || position <= 0)
		return (0);
	current = stack;
	i = 1;
	while (current && i < position)
	{
		current = current->next;
		i++;
	}
	if (current)
		return (*(int *)(current->content));
	return (0);
}