/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:15:25 by arvardan          #+#    #+#             */
/*   Updated: 2026/05/31 20:55:47 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
	{
		str++;
	}
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return (number * sign);
}

static int	set_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static double	calc_fract(const char **str)
{
	double	fraction;
	double	div;

	fraction = 0.0;
	div = 1.0;
	while (**str >= '0' && **str <= '9')
	{
		fraction = fraction * 10.0 + (**str - '0');
		div *= 10.0;
		(*str)++;
	}
	return (fraction / div);
}

float	ft_atof(const char *str)
{
	double	number;
	int		sign;

	number = 0.0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = set_sign(&str);
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		number += calc_fract(&str);
	}
	return ((float)(number * sign));
}
