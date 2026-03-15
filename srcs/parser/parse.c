/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:03:15 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/13 19:38:58 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	validate_scene(t_scene *sc)
{
	if (!sc->has_amb || !sc->has_camera || sc->light_count == 0)
	{
		free_scene(sc);
		get_next_line(-1);
		print_error("Mandatory identifier is missing in the map!\n");
	}
}

void	parse_file(t_scene *sc, char *file_name)
{
	t_parse	p;
	int		has_content;

	p.sc = sc;
	p.line = NULL;
	p.tokens = NULL;
	has_content = 0;
	p.fd = open(file_name, O_RDONLY);
	if (p.fd == -1)
		print_error("Can't open file!\n");
	p.line = get_next_line(p.fd);
	while (p.line != NULL)
	{
		parse_line(&p, &has_content);
		free(p.line);
		p.line = get_next_line(p.fd);
	}
	if (close(p.fd) == -1)
		print_error("Can't close file!\n");
	if (!has_content)
		print_error("Map is empty!\n");
	validate_scene(sc);
}

void	parse_line(t_parse *p, int *has_content)
{
	char	*original;

	original = p->line;
	skip_whitespaces(&p->line);
	if (*p->line == '\0')
	{
		p->line = original;
		return ;
	}
	*has_content = 1;
	trim_whitespaces(p->line);
	make_all_spaces(p->line);
	p->tokens = ft_split(p->line, ' ');
	p->line = original;
	if (!p->tokens || !p->tokens[0])
	{
		free_split(p->tokens);
		return ;
	}
	identify_all(p);
	free_split(p->tokens);
}
