/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:20:08 by arvardan          #+#    #+#             */
/*   Updated: 2026/01/27 22:52:10 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	set_vector(float x, float y, float z)
{
	t_vec3	new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}

t_vec3	vec_add(t_vec3 p1, t_vec3 p2)
{
	t_vec3	vec_upd;

	vec_upd.x = p1.x + p2.x;
	vec_upd.y = p1.y + p2.y;
	vec_upd.z = p1.z + p2.z;
	return (vec_upd);
}

t_vec3	vec_subt(t_vec3 p1, t_vec3 p2)
{
	t_vec3	vec_upd;

	vec_upd.x = p1.x - p2.x;
	vec_upd.y = p1.y - p2.y;
	vec_upd.z = p1.z - p2.z;
	return (vec_upd);
}

t_vec3	vec_scale(t_vec3 vec, float mult_factor)
{
	t_vec3	v;

	v.x = vec.x * mult_factor;
	v.y = vec.y * mult_factor;
	v.z = vec.z * mult_factor;
	return (v);
}
