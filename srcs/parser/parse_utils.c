/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 01:34:22 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/12 01:35:12 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_optional(t_objs *new, char *token)
{
	size_t	len;

	if (!token || !*token)
		return (-1);
	if (ft_strncmp(token, "specular=", 9) == 0)
		return (parse_specular(new, token + 9));
	else if (ft_strncmp(token, "shininess=", 10) == 0)
		return (parse_shininess(new, token + 10));
	len = ft_strlen(token);
	if (len >= 4 && ft_strcmp(token + len - 4, ".xpm") == 0)
		return (parse_texture(new, token));
	else if (ft_strcmp(token, "mirror") == 0)
		return (parse_mirror(new, token));
	else if (ft_strcmp(token, "checkerboard") == 0)
		return (parse_checker(new, token));
	else
		return (-1);
}
