/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:30:39 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/26 15:01:29 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	values_sphere(t_objs *new, int *i, t_parse *p)
{
	new->pos = parse_vector(p->tokens[(*i)++]);
	check_vector(new->pos, new, p, "Vector validation failed!\n");
	new->diameter = parse_float(p->tokens[(*i)++]);
	check_positive(new->diameter, new, p, "Diameter has to be positive!\n");
	new->radius = new->diameter / 2;
	new->color = parse_color(p->tokens[(*i)++]);
	check_color(new->color, new, p, "Invalid color: sphere!\n");
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
	new = create_object(p, SPHERE);
	i = 1;
	i = values_sphere(new, &i, p);
	args_loop(&i, &line_args, new, p);
	append_object(p->sc, new);
}
