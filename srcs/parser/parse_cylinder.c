/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:22:12 by arvardan          #+#    #+#             */
/*   Updated: 2026/04/25 20:12:46 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	values_cylinder(t_objs *new, int *i, t_parse *p)
{
	new->pos = parse_vector(p->tokens[(*i)++]);
	check_vector(new->pos, new, p, ERR_VALID_VEC);
	new->orientation = parse_normalized_vector(p->tokens[(*i)++]);
	check_normalized(new->orientation, new, p, ERR_NORM_AXIS);
	new->diameter = parse_float(p->tokens[(*i)++]);
	check_positive(new->diameter, new, p, ERR_POS_DIAMETER);
	new->radius = new->diameter / 2;
	new->height = parse_float(p->tokens[(*i)++]);
	check_positive(new->height, new, p, ERR_POS_HEIGHT);
	new->color = parse_color(p->tokens[(*i)++]);
	check_color(new->color, new, p, "Invalid color: cylinder!\n");
}

void	parse_cylinder(t_parse *p)
{
	int		line_args;
	t_objs	*new;
	int		i;

	line_args = arg_count(p->tokens);
	if (line_args < 6 || line_args > 9)
		free_parsing_fail(p, "Invalid argument for identifier: cylinder!\n");
	new = create_object(p, CYLINDER);
	i = 1;
	values_cylinder(new, &i, p);
	args_loop(&i, &line_args, new, p);
	append_object(p->sc, new);
}
