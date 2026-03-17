/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:31:33 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/17 22:55:42 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	values_plane(t_objs *new, int *i, t_parse *p)
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
		print_error("Plane axis must be normalized\n");
	}
	new->color = parse_color(p->tokens[(*i)++]);
	if (!valid_color(&new->color))
	{
		free(new);
		free_parsing_fail(p);
		print_error("Invalid color for plane!\n");
	}
	return (*i);
}

void	parse_plane(t_parse *p)
{
	int		line_args;
	t_objs	*new;
	int		i;

	line_args = arg_count(p->tokens);
	if (line_args < 4 || line_args > 7)
	{
		free_parsing_fail(p);
		print_error("Invalid argument for identifier: plane!\n");
	}
	new = malloc(sizeof(t_objs));
	if (!new)
		print_error("Malloc failed!\n");
	init_object(new);
	new->type = PLANE;
	i = 1;
	i = values_plane(new, &i, p);
	args_loop(&i, &line_args, new, p);
	append_object(p->sc, new);
}
