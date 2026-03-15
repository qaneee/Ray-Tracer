/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:16:38 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/16 20:39:36 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene(t_scene *sc)
{
	ft_bzero(sc, sizeof(t_scene));
	sc->amb.color = (t_color){255, 255, 255};
	sc->camera.dir = (t_vec3){0.0, 0.0, 1.0};
	sc->width = WIN_WIDTH;
	sc->height = WIN_HEIGHT;
}

void	init_object(t_objs *obj)
{
	ft_bzero(obj, sizeof(t_objs));
	obj->checkerboard = 0;
	obj->reflection = 0.0f;
	obj->bump_map = NULL;
	obj->specular = 0.0f;
	obj->shininess = 32.0f;
	obj->has_specular = 0;
	obj->has_shininess = 0;
	obj->next = NULL;
}

void	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		print_error("mlx_init() failed!\n");
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"miniRT");
	if (!data->mlx.win)
		mlx_error(&data->mlx);
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->mlx.img)
		mlx_error(&data->mlx);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.lsize, &data->mlx.endian);
	if (!data->mlx.addr)
		mlx_error(&data->mlx);
}

void	init_scene_textures(t_data *data)
{
	load_skybox(data);
	load_object_textures(data);
}
