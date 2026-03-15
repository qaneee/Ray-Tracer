/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:22:12 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/12 01:33:00 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	values_cylinder_height_color(t_objs *new, int *i, t_parse *p)
{
	new->height = parse_float(p->tokens[(*i)++]);
	if (isnan(new->height) || new->height <= 0)
	{
		free(new);
		free_parsing_fail(p);
		print_error("Height has to be a positive float!\n");
	}
	new->color = parse_color(p->tokens[(*i)++]);
	if (!valid_color(&new->color))
	{
		free(new);
		free_parsing_fail(p);
		print_error("Invalid color for cylinder!\n");
	}
}

static void	values_cylinder(t_objs *new, int *i, t_parse *p)
{
	new->pos = parse_vector(p->tokens[(*i)++]);
	if (isnan(new->pos.x) || isnan(new->pos.y) || isnan(new->pos.z))
	{
		free(new);
		free_parsing_fail(p);
		print_error("Failed parsing vector!\n");
	}
	new->orientation = parse_normalized_vector(p->tokens[(*i)++]);
	if (!is_normalized(new->orientation))
	{
		free(new);
		free_parsing_fail(p);
		print_error("Cylinder axis must be normalized\n");
	}
	new->diameter = parse_float(p->tokens[(*i)++]);
	if (isnan(new->diameter) || new->diameter <= 0)
	{
		free(new);
		free_parsing_fail(p);
		print_error("Diameter has to be a positive float!\n");
	}
	new->radius = new->diameter / 2;
	values_cylinder_height_color(new, i, p);
}

void	parse_cylinder(t_parse *p)
{
	int		line_args;
	t_objs	*new;
	int		i;

	line_args = arg_count(p->tokens);
	if (line_args < 6 || line_args > 9)
	{
		free_parsing_fail(p);
		print_error("Invalid argument for identifier: cylinder!\n");
	}
	new = malloc(sizeof(t_objs));
	if (!new)
		print_error("Malloc failed!\n");
	init_object(new);
	new->type = CYLINDER;
	i = 1;
	values_cylinder(new, &i, p);
	args_loop(&i, &line_args, new, p);
	append_object(p->sc, new);
}
