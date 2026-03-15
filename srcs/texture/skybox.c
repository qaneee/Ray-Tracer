/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:15:33 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/16 20:39:03 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_skybox_color(t_scene *sc, t_ray *ray)
{
	t_vec3	dir;
	float	theta;
	float	phi;

	if (!sc->skybox)
		return ((t_color){0, 0, 0});
	dir = normal_vector(ray->direct);
	theta = acosf(-dir.y);
	phi = atan2f(-dir.z, dir.x) + M_PI;
	return (get_texture_color(sc->skybox,
			phi / (2.0f * M_PI), theta / M_PI));
}
