/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 02:57:52 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/15 22:53:33 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	apply_checkerboard(t_hit *hit)
{
	int		is_white;
	int		pattern_x;
	int		pattern_y;
	int		pattern_z;

	if (!hit->objs->checkerboard)
		return (hit->objs->color);
	pattern_x = (int)floorf(hit->point.x / CHECKER_SCALE);
	pattern_y = (int)floorf(hit->point.y / CHECKER_SCALE);
	pattern_z = (int)floorf(hit->point.z / CHECKER_SCALE);
	is_white = (pattern_x + pattern_y + pattern_z) % 2;
	if (is_white)
		return ((t_color){255, 255, 255});
	else
		return (hit->objs->color);
}

t_color	get_object_color(t_hit *hit)
{
	if (hit->objs->texture)
		return (get_texture_color(hit->objs->texture, hit->u, hit->v));
	if (hit->objs->checkerboard)
		return (apply_checkerboard(hit));
	return (hit->objs->color);
}
