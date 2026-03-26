/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:32:28 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/26 14:58:52 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	values_cone(t_parse *p, t_objs *new, int *i)
{
	new->pos = parse_vector(p->tokens[(*i)++]);
	check_vector(new->pos, new, p, "Vector validation failed!\n");
	new->orientation = parse_normalized_vector(p->tokens[(*i)++]);
	check_normalized(new->orientation, new, p, "Axis must be normalized!\n");
	new->diameter = parse_float(p->tokens[(*i)++]);
	check_positive(new->diameter, new, p, "Diameter has to be positive!\n");
	new->radius = new->diameter / 2;
	new->height = parse_float(p->tokens[(*i)++]);
	check_positive(new->height, new, p, "Height has to be positive!\n");
	new->color = parse_color(p->tokens[(*i)++]);
	check_color(new->color, new, p, "Invalid color: cone!\n");
}

void	parse_cone(t_parse *p)
{
	int		line_args;
	t_objs	*new;
	int		i;

	line_args = arg_count(p->tokens);
	if (line_args < 6 || line_args > 9)
		free_parsing_fail(p, "Invalid argument for identifier: cone!\n");
	new = create_object(p, CONE);
	i = 1;
	values_cone(p, new, &i);
	args_loop(&i, &line_args, new, p);
	append_object(p->sc, new);
}
