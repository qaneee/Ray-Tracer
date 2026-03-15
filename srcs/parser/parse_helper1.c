/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:03:43 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/02 09:51:46 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_valid_float(char *str)
{
	int	fl_dot;
	int	fl_digit;

	fl_dot = 0;
	fl_digit = 0;
	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	if (*str == '.')
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str))
			fl_digit = 1;
		else if (*str == '.' && !fl_dot)
			fl_dot = 1;
		else
			return (0);
		str++;
	}
	return (fl_digit);
}

static int	is_valid_int(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

float	parse_float(char *str)
{
	if (!is_valid_float(str))
		return (nanf(""));
	return (ft_atof(str));
}

int	parse_int(char *str)
{
	if (!is_valid_int(str))
		return (-1);
	return (ft_atoi(str));
}
