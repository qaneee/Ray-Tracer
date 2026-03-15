/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:51:46 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/02 09:19:30 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void	free_objects(t_objs *head)
{
	t_objs	*temp;

	while (head)
	{
		temp = head->next;
		if (head->bump_map)
			free(head->bump_map);
		free(head);
		head = temp;
	}
}

static void	free_lights(t_light *head)
{
	t_light	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

void	free_scene(t_scene *sc)
{
	if (!sc)
		return ;
	free_objects(sc->objs);
	free_lights(sc->lights);
	if (sc->skybox_path)
		free(sc->skybox_path);
}
