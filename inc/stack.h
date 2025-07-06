/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:30:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 17:20:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHECK_STACK_H
#define FT_CHECK_STACK_H
#include "libft.h"
/**
 * full compatibility approach with the current t_list structure,
 * all functions that use t_list still work
 * we can access the underlying `t_list` directly when needed
 * no breaking chnages to existing code
 * @note strategic use :
 * stck operation(push, pop, rotate)
 * when we need size tracking
 * when we want circular/linear flexibility
 * 
 */
typedef struct s_stack
{
    t_list *head;
    t_list *tail;
    int size;
    bool is_circular;
}               t_stack;
#endif