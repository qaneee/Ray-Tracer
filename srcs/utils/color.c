/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:53:13 by arvardan          #+#    #+#             */
/*   Updated: 2026/01/26 18:47:11 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | (color.b));
}

int	valid_color(t_color *color)
{
	if (color->r >= 0 && color->r <= 255
		&& color->g >= 0 && color->g <= 255
		&& color->b >= 0 && color->b <= 255)
		return (1);
	return (0);
}
