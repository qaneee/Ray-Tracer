/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_optional.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:36:03 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/12 01:10:02 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_texture(t_objs *new, char *token)
{
	if (new->bump_map || new->checkerboard || new->reflection != 0.0f
		|| !token || !*token)
		return (-1);
	new->bump_map = ft_strdup(token);
	if (!new->bump_map)
		return (-1);
	return (0);
}

int	parse_mirror(t_objs *new, char *token)
{
	if (new->bump_map || new->reflection != 0.0f || new->checkerboard)
		return (-1);
	if (ft_strcmp(token, "mirror") == 0)
		new->reflection = 1.0f;
	else
		return (-1);
	return (0);
}

int	parse_checker(t_objs *new, char *token)
{
	if (new->bump_map || new->reflection != 0.0f || new->checkerboard)
		return (-1);
	if (ft_strcmp(token, "checkerboard") == 0)
		new->checkerboard = 1;
	else
		return (-1);
	return (0);
}

int	parse_specular(t_objs *new, char *token)
{
	if (!is_valid_float(token))
		return (-1);
	new->specular = parse_float(token);
	if (new->specular < 0.0f || new->specular > 1.0f)
		return (-1);
	new->has_specular = 1;
	return (0);
}

int	parse_shininess(t_objs *new, char *token)
{
	if (!is_valid_float(token))
		return (-1);
	new->shininess = parse_float(token);
	if (new->shininess < 2.0f || new->shininess > 200.0f)
		return (-1);
	new->has_shininess = 1;
	return (0);
}
