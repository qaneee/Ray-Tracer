/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:15:25 by arvardan          #+#    #+#             */
/*   Updated: 2025/10/07 13:19:55 by arvardan         ###   ########.fr       */
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

static float	set_sign(const char **str)
{
	float	sign;

	sign = 1.0f;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1.0f;
		(*str)++;
	}
	return (sign);
}

static float	calc_fract(const char **str)
{
	float	fraction;
	float	div;

	fraction = 0.0f;
	div = 1.0f;
	while (**str >= '0' && **str <= '9')
	{
		fraction = fraction * 10.0f + (**str - '0');
		div *= 10.0f;
		(*str)++;
	}
	return (fraction / div);
}

float	ft_atof(const char *str)
{
	float	number;
	float	sign;

	number = 0.0f;
	sign = 1.0f;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = set_sign(&str);
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10.0f + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		number += calc_fract(&str);
	}
	return (number * sign);
}
