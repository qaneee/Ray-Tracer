/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:43:10 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/26 15:02:46 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_vector(t_vec3 vec, t_objs *obj, t_parse *p, char *msg)
{
	if (isnan(vec.x) || isnan(vec.y) || isnan(vec.z))
	{
		free_objects(obj);
		free_parsing_fail(p, msg);
	}
}

void	check_positive(float value, t_objs *obj, t_parse *p, char *msg)
{
	if (isnan(value) || value <= 0.0f)
	{
		free_objects(obj);
		free_parsing_fail(p, msg);
	}
}

void	check_color(t_color color, t_objs *obj, t_parse *p, char *msg)
{
	if (!valid_color(&color))
	{
		free_objects(obj);
		free_parsing_fail(p, msg);
	}
}

void	check_normalized(t_vec3 vec, t_objs *obj, t_parse *p, char *msg)
{
	if (!is_normalized(vec))
	{
		free_objects(obj);
		free_parsing_fail(p, msg);
	}
}

t_objs	*create_object(t_parse *p, t_type type)
{
	t_objs	*new;

	new = malloc(sizeof(t_objs));
	if (!new)
		free_parsing_fail(p, "Malloc failed!\n");
	init_object(new);
	new->type = type;
	return (new);
}
