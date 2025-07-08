/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 18:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

// Stub implementations for when not using micro_test
// These will be overridden by the implementations in micro_test.c when linked

__attribute__((weak))
void record_operation(const char *operation)
{
    (void)operation;  // Suppress unused parameter warning
    // Do nothing in main program
}

__attribute__((weak))
int is_recording(void)
{
    return 0;  // Never recording in main program
}

__attribute__((weak))
void init_recorder(void)
{
    // Do nothing in main program
}

__attribute__((weak))
void start_recording(void)
{
    // Do nothing in main program
}

__attribute__((weak))
void stop_recording(void)
{
    // Do nothing in main program
}

__attribute__((weak))
void cleanup_recorder(void)
{
    // Do nothing in main program
}
