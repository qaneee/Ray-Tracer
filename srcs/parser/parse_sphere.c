/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:30:39 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/26 11:19:08 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	values_sphere(t_objs *new, int *i, t_parse *p)
{
	new->pos = parse_vector(p->tokens[(*i)++]);
	if (isnan(new->pos.x) || isnan(new->pos.y) || isnan(new->pos.z))
	{
		free_objects(new);
		free_parsing_fail(p, "Failed parsing vector!\n");
	}
	new->diameter = parse_float(p->tokens[(*i)++]);
	if (isnan(new->diameter) || new->diameter <= 0)
	{
		free_objects(new);
		free_parsing_fail(p, "Diameter has to be a positive float!\n");
	}
	new->radius = new->diameter / 2;
	new->color = parse_color(p->tokens[(*i)++]);
	if (!valid_color(&new->color))
	{
		free_objects(new);
		free_parsing_fail(p, "Invalid color for sphere!\n");
	}
	return (*i);
}

void	parse_sphere(t_parse *p)
{
	int		line_args;
	t_objs	*new;
	int		i;

	line_args = arg_count(p->tokens);
	if (line_args < 4 || line_args > 7)
	{
		free_parsing_fail(p, "Invalid arguments for identifier: sphere!\n");
	}
	new = malloc(sizeof(t_objs));
	if (!new)
		free_parsing_fail(p, "Malloc failed!\n");
	init_object(new);
	new->type = SPHERE;
	i = 1;
	i = values_sphere(new, &i, p);
	args_loop(&i, &line_args, new, p);
	append_object(p->sc, new);
}
