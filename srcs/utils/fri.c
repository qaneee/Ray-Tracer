/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:44:39 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/13 19:29:28 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_texture(t_data *data)
{
	t_objs	*objs;

	objs = data->scene.objs;
	while (objs)
	{
		if (objs->texture)
		{
			mlx_destroy_image(data->mlx.mlx, objs->texture->img);
			free(objs->texture);
		}
		objs = objs->next;
	}
	if (data->scene.skybox)
	{
		mlx_destroy_image(data->mlx.mlx, data->scene.skybox->img);
		free(data->scene.skybox);
	}
}

void	free_mlx(t_data *data)
{
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->mlx.mlx)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
}

void	cleanup_and_exit(t_data *data)
{
	free_texture(data);
	free_mlx(data);
	free_scene(&data->scene);
	exit(0);
}

void	free_parsing_fail(t_parse *p)
{
	free_split(p->tokens);
	free_scene(p->sc);
	get_next_line(-1);
	free (p->line);
	if (p->fd > 0)
		close(p->fd);
}
