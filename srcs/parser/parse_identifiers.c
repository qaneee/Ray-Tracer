/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:35:27 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/12 02:11:14 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(t_parse *p)
{
	float	ratio;

	ratio = p->sc->amb.ratio;
	if (arg_count(p->tokens) != 3)
	{
		free_parsing_fail(p);
		print_error("Invalid argument for identifier: Ambient\n");
	}
	ratio = parse_float(p->tokens[1]);
	if (isnan(ratio) || ratio < 0.0 || ratio > 1.0)
	{
		free_parsing_fail(p);
		print_error("Ratio range [0.0 - 1.0] or Invalid float\n");
	}
	p->sc->amb.color = parse_color(p->tokens[2]);
	if (!valid_color(&p->sc->amb.color))
	{
		free_parsing_fail(p);
		print_error("Invalid color!\n");
	}
}

void	parse_camera(t_parse *p)
{
	if (arg_count(p->tokens) != 4)
	{
		free_parsing_fail(p);
		print_error("Invalid argument for identifier: Camera\n");
	}
	p->sc->camera.pos = parse_vector(p->tokens[1]);
	if (isnan(p->sc->camera.pos.x) || isnan(p->sc->camera.pos.y)
		|| isnan(p->sc->camera.pos.z))
	{
		free_parsing_fail(p);
		print_error("Failed parsing vector!\n");
	}
	p->sc->camera.dir = parse_normalized_vector(p->tokens[2]);
	if (!is_normalized(p->sc->camera.dir))
	{
		free_parsing_fail(p);
		print_error("Camera direction must be normalized\n");
	}
	p->sc->camera.fov = parse_int(p->tokens[3]);
	if (p->sc->camera.fov < 0 || p->sc->camera.fov > 180)
	{
		free_parsing_fail(p);
		print_error("FOV range [0 - 180]\n");
	}
}

static void	parse_light_values(t_parse *p, t_light *new)
{
	new->pos = parse_vector(p->tokens[1]);
	if (isnan(new->pos.x) || isnan(new->pos.y) || isnan(new->pos.z))
	{
		free(new);
		free_parsing_fail(p);
		print_error("Failed parsing vector!\n");
	}
	new->brightness = parse_float(p->tokens[2]);
	if (new->brightness < 0.0 || new->brightness > 1.0)
	{
		free(new);
		free_parsing_fail(p);
		print_error("Wrong brightness ratio range\n");
	}
	if (arg_count(p->tokens) == 4)
		new->color = parse_color(p->tokens[3]);
	else
		new->color = (t_color){255, 255, 255};
	if (!valid_color(&new->color))
	{
		free(new);
		free_parsing_fail(p);
		print_error("Invalid color for light!\n");
	}
}

void	parse_light(t_parse *p)
{
	t_light	*new;

	if (arg_count(p->tokens) != 3 && arg_count(p->tokens) != 4)
	{
		free_parsing_fail(p);
		print_error("Invalid argument for identifier: Light\n");
	}
	new = malloc(sizeof(t_light));
	if (!new)
		print_error("Malloc failed\n");
	parse_light_values(p, new);
	append_light(p->sc, new);
}

void	parse_skybox(t_parse *p)
{
	char	*extension;

	if (arg_count(p->tokens) != 2)
	{
		free_parsing_fail(p);
		print_error("Invalid argument for identifier: Skybox\n");
	}
	if (ft_strlen(p->tokens[1]) < 4 || !p->tokens[1] || !*p->tokens[1])
	{
		free_parsing_fail(p);
		print_error("Filename too short or empty!\n");
	}
	extension = p->tokens[1] + ft_strlen(p->tokens[1]) - 4;
	if (ft_strncmp(extension, ".xpm", 4) != 0)
	{
		free_parsing_fail(p);
		print_error("Skybox must be a .xpm file\n");
	}
	p->sc->skybox_path = ft_strdup(p->tokens[1]);
	if (!p->sc->skybox_path)
	{
		free_parsing_fail(p);
		print_error("Memory allocation failed for skybox path\n");
	}
}
