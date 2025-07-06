/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_algos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:11:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 20:12:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ps.h"

/**
the sort three algorithme is just an algorithm  that verify some conditons
and permute the value if they are complied 
 */
void	sort_three(t_ps *ps)
{
	int	a = ps->a->content;
	int	b = ps->a->next->content;
	int	c = ps->a->next->next->content;

	if (a > b && b < c && a < c)
		sa(ps);								// case: 2 1 3 → 1 2 3
	else if (a > b && b > c)
	{
		sa(ps); rra(ps);					// case: 3 2 1 → 1 2 3
	}
	else if (a > b && b < c && a > c)
		ra(ps);								// case: 2 1 3 → 1 3 2 → rra later maybe
	else if (a < b && b > c && a < c)
	{
		sa(ps); ra(ps);						// case: 1 3 2 → 3 1 2 → rotate to 1 2 3
	}
	else if (a < b && b > c && a > c)
		rra(ps);							// case: 2 3 1 → 1 2 3
}
