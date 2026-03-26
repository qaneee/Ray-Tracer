/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:32:28 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/26 11:01:56 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	values_cone_height_color(t_parse *p, t_objs *new, int *i)
{
	new->height = parse_float(p->tokens[(*i)++]);
	if (isnan(new->height) || new->height <= 0)
	{
		free_objects(new);
		free_parsing_fail(p, "Height has to be a positive float!\n");
	}
	new->color = parse_color(p->tokens[(*i)++]);
	if (!valid_color(&new->color))
	{
		free_objects(new);
		free_parsing_fail(p, "Invalid color for cone!\n");
	}
}

static void	values_cone(t_parse *p, t_objs *new, int *i)
{
	new->pos = parse_vector(p->tokens[(*i)++]);
	if (isnan(new->pos.x) || isnan(new->pos.y) || isnan(new->pos.z))
	{
		free_objects(new);
		free_parsing_fail(p, "Failed parsing vector!\n");
	}
	new->orientation = parse_normalized_vector(p->tokens[(*i)++]);
	if (!is_normalized(new->orientation))
	{
		free_objects(new);
		free_parsing_fail(p, "Cone axis must be normalized\n");
	}
	new->diameter = parse_float(p->tokens[(*i)++]);
	if (isnan(new->diameter) || new->diameter <= 0)
	{
		free_objects(new);
		free_parsing_fail(p, "Diameter has to be a positive float!\n");
	}
	new->radius = new->diameter / 2;
	values_cone_height_color(p, new, i);
}

void	parse_cone(t_parse *p)
{
	int		line_args;
	t_objs	*new;
	int		i;

	line_args = arg_count(p->tokens);
	if (line_args < 6 || line_args > 9)
		free_parsing_fail(p, "Invalid argument for identifier: cone!\n");
	new = malloc(sizeof(t_objs));
	if (!new)
		free_parsing_fail(p, "Malloc failed!\n");
	init_object(new);
	new->type = CONE;
	i = 1;
	values_cone(p, new, &i);
	args_loop(&i, &line_args, new, p);
	append_object(p->sc, new);
}
