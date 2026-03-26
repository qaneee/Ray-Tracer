/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:56:32 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/26 10:59:04 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	norminette_survivors(t_parse *p)
{
	if (ft_strcmp(p->tokens[0], "A") == 0)
	{
		if (p->sc->has_amb)
			free_parsing_fail(p, "Multiple ambient!\n");
		p->sc->has_amb = 1;
		parse_ambient(p);
	}
	else if (ft_strcmp(p->tokens[0], "C") == 0)
	{
		if (p->sc->has_camera)
			free_parsing_fail(p, "Multiple camera!\n");
		p->sc->has_camera = 1;
		parse_camera(p);
	}
	else if (ft_strcmp(p->tokens[0], "L") == 0)
		parse_light(p);
	else
		return (0);
	return (1);
}

static void	norminette_victims(t_parse *p)
{
	if (ft_strcmp(p->tokens[0], "sp") == 0)
		parse_sphere(p);
	else if (ft_strcmp(p->tokens[0], "cy") == 0)
		parse_cylinder(p);
	else if (ft_strcmp(p->tokens[0], "pl") == 0)
		parse_plane(p);
	else if (ft_strcmp(p->tokens[0], "co") == 0)
		parse_cone(p);
	else if (ft_strcmp(p->tokens[0], "S") == 0)
	{
		if (p->sc->has_skybox)
			free_parsing_fail(p, "Multiple skyboxes!\n");
		p->sc->has_skybox = 1;
		parse_skybox(p);
	}
	else
	{
		free_parsing_fail(p, "Invalid object\n");
	}
}

void	identify_all(t_parse *p)
{
	if (!norminette_survivors(p))
		norminette_victims(p);
}
