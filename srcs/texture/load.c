/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:20:39 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/02 20:26:33 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_texture	*load_texture(void *mlx, char *filename)
{
	t_texture	*t;

	if (!filename)
		return (NULL);
	t = malloc(sizeof(t_texture));
	if (!t)
		return (NULL);
	t->img = mlx_xpm_file_to_image(mlx, filename, &t->width, &t->height);
	if (!t->img)
	{
		free(t);
		return (NULL);
	}
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
	return (t);
}

void	load_skybox(t_data *data)
{
	if (!data->scene.skybox_path)
	{
		data->scene.skybox = NULL;
		return ;
	}
	data->scene.skybox = load_texture(data->mlx.mlx, data->scene.skybox_path);
	if (!data->scene.skybox)
	{
		printf("Error\nFailed to load skybox!\n");
		cleanup_and_exit(data);
	}
}

void	load_object_textures(t_data *data)
{
	t_objs	*objs;

	objs = data->scene.objs;
	while (objs)
	{
		if (objs->bump_map)
		{
			objs->texture = load_texture(data->mlx.mlx, objs->bump_map);
			if (!objs->texture)
			{
				printf("Error\nFailed to load texture: %s\n", objs->bump_map);
				cleanup_and_exit(data);
			}
		}
		else
		{
			objs->texture = NULL;
		}
		objs = objs->next;
	}
}
