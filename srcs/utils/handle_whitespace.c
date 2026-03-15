/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_whitespace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:52:26 by arvardan          #+#    #+#             */
/*   Updated: 2026/01/25 14:07:18 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	skip_whitespaces(char **str)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
}

void	trim_whitespaces(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return ;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' '
			|| (str[len - 1] >= '\t' && str[len - 1] <= '\r')))
		str[--len] = '\0';
}

void	make_all_spaces(char *line)
{
	while (*line)
	{
		if (ft_isspace((unsigned char)*line))
		{
			*line = ' ';
		}
		line++;
	}
}
