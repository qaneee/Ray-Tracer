/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:33:04 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/17 22:43:01 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	parse_vector(char *s)
{
	t_vec3	vector;
	char	**arr;

	if (!s || ft_strnstr(s, ",,", ft_strlen(s))
		|| (ft_strchr(s, ',') && (s[ft_strlen(s) - 1] == ',' || s[0] == ',')))
		return ((t_vec3){nanf(""), nanf(""), nanf("")});
	arr = ft_split(s, ',');
	if (!arr)
		print_error("Splitting failed\n");
	if (arg_count(arr) != 3)
	{
		return (free_split(arr), (t_vec3){nanf(""), nanf(""), nanf("")});
	}
	vector.x = parse_float(arr[0]);
	vector.y = parse_float(arr[1]);
	vector.z = parse_float(arr[2]);
	return (free_split(arr), vector);
}

t_vec3	parse_normalized_vector(char *s)
{
	t_vec3	vector;
	char	**arr;

	if (!s || ft_strnstr(s, ",,", ft_strlen(s))
		|| (ft_strchr(s, ',') && (s[ft_strlen(s) - 1] == ',' || s[0] == ',')))
		return ((t_vec3){nanf(""), nanf(""), nanf("")});
	arr = ft_split(s, ',');
	if (!arr)
		print_error("Splitting failed\n");
	if (arg_count(arr) != 3)
	{
		free_split(arr);
		return ((t_vec3){nanf(""), nanf(""), nanf("")});
	}
	vector.x = parse_float(arr[0]);
	vector.y = parse_float(arr[1]);
	vector.z = parse_float(arr[2]);
	if (vector.x < -1.0 || vector.x > 1.0
		|| vector.y < -1.0 || vector.y > 1.0
		||vector.z < -1.0 || vector.z > 1.0)
	{
		return (free_split(arr), (t_vec3){nanf(""), nanf(""), nanf("")});
	}
	return (free_split(arr), vector);
}

t_color	parse_color(char *s)
{
	t_color	c;
	char	**arr;

	if (!s || ft_strnstr(s, ",,", ft_strlen(s))
		|| (ft_strchr(s, ',') && (s[ft_strlen(s) - 1] == ',' || s[0] == ',')))
		return ((t_color){-1, -1, -1});
	arr = ft_split(s, ',');
	if (!arr)
		print_error("Splitting failed\n");
	if (arg_count(arr) != 3)
	{
		free_split(arr);
		return ((t_color){-1, -1, -1});
	}
	c.r = parse_int(arr[0]);
	c.g = parse_int(arr[1]);
	c.b = parse_int(arr[2]);
	return (free_split(arr), c);
}

void	args_loop(int *start, int *end, t_objs *new, t_parse *p)
{
	while (*start < *end)
	{
		if (parse_optional(new, p->tokens[*start]) == -1)
		{
			free(new->bump_map);
			free(new);
			free_parsing_fail(p);
			print_error("Invalid optional parameter!\n");
		}
		(*start)++;
	}
	if (new->has_specular != new->has_shininess)
	{
		free(new->bump_map);
		free(new);
		free_parsing_fail(p);
		print_error("Specular and shininess must be provided together!\n");
	}
}
