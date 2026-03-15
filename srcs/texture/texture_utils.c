/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:51:03 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/12 10:54:08 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	wrap_coord(float uv, int size)
{
	int	pos;

	pos = (int)(uv * size) % size;
	if (pos < 0)
		pos += size;
	return (pos);
}

static t_color	get_pixel_color(t_texture *tex, unsigned char *p)
{
	t_color	c;

	if (tex->endian == 0)
	{
		c.b = p[0];
		c.g = p[1];
		c.r = p[2];
	}
	else if (tex->bpp == 32)
	{
		c.r = p[1];
		c.g = p[2];
		c.b = p[3];
	}
	else
	{
		c.r = p[0];
		c.g = p[1];
		c.b = p[2];
	}
	return (c);
}

t_color	get_texture_color(t_texture *tex, float u, float v)
{
	int				x;
	int				y;
	int				offset;
	unsigned char	*p;

	if (!tex)
		return ((t_color){0, 0, 0});
	x = wrap_coord(u, tex->width);
	y = wrap_coord(v, tex->height);
	offset = y * tex->line_len + x * (tex->bpp / 8);
	p = (unsigned char *)tex->addr + offset;
	return (get_pixel_color(tex, p));
}

static t_vec3	get_tangent(t_hit *hit)
{
	if (hit->objs->type == PLANE)
		return ((t_vec3){1, 0, 0});
	return (normal_vector((t_vec3){-hit->normal.z, 0, hit->normal.x}));
}

t_vec3	perturb_normal(t_hit *hit)
{
	t_color	bump_color;
	t_vec3	tg;
	float	dhdu;
	float	dhdv;
	float	h0;

	if (!hit->objs->texture)
		return (hit->normal);
	tg = get_tangent(hit);
	bump_color = get_texture_color(hit->objs->texture, hit->u, hit->v);
	h0 = (bump_color.r + bump_color.g + bump_color.b) / (3.0f * 255.0f);
	bump_color = get_texture_color(hit->objs->texture, hit->u + 0.001f, hit->v);
	dhdu = (bump_color.r + bump_color.g + bump_color.b) / (3.0f * 255.0f) - h0;
	bump_color = get_texture_color(hit->objs->texture, hit->u, hit->v + 0.001f);
	dhdv = (bump_color.r + bump_color.g + bump_color.b) / (3.0f * 255.0f) - h0;
	return (normal_vector(vec_add(hit->normal,
				vec_add(vec_scale(tg, dhdu * 2.0f),
					vec_scale(cross_product(hit->normal, tg), dhdv * 2.0f)))));
}
