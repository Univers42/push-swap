/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_bit_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:00:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 19:07:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int calc_bit_size(int size);

int main(void)
{
    int size;
    printf("give the value you want to enter please:");
    scanf("%d", &size);
    int l = calc_bit_size(size);
    printf("the length of bit necessary is : %d\n", l);
}

// this function tells how many bits are necessary to calcular
static int calc_bit_size(int size)
{
    int bits;
    int value;

    bits = 0;
    value = size - 1;
    while (value > 0)
    {
        value >>=1;
        bits++;
    }
    return (bits);
}
