/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:31:33 by arvardan          #+#    #+#             */
/*   Updated: 2026/04/25 20:13:40 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	values_plane(t_objs *new, int *i, t_parse *p)
{
	new->pos = parse_vector(p->tokens[(*i)++]);
	check_vector(new->pos, new, p, ERR_VALID_VEC);
	new->orientation = parse_normalized_vector(p->tokens[(*i)++]);
	check_normalized(new->orientation, new, p, ERR_NORM_AXIS);
	new->color = parse_color(p->tokens[(*i)++]);
	check_color(new->color, new, p, "Invalid color: plane!\n");
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
		free_parsing_fail(p, "Invalid argument for identifier: plane!\n");
	}
	new = create_object(p, PLANE);
	i = 1;
	i = values_plane(new, &i, p);
	args_loop(&i, &line_args, new, p);
	append_object(p->sc, new);
}
