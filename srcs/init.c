/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:16:38 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/26 12:34:31 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene(t_scene *sc)
{
	sc->amb.color = (t_color){255, 255, 255};
	sc->camera.dir = (t_vec3){0.0, 0.0, 1.0};
	sc->width = WIN_WIDTH;
	sc->height = WIN_HEIGHT;
}

void	init_object(t_objs *obj)
{
	ft_bzero(obj, sizeof(t_objs));
	obj->shininess = 32.0f;
}

void	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		cleanup_and_error(data, "mlx_init() failed!\n");
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"miniRT");
	if (!data->mlx.win)
		cleanup_and_error(data, "mlx_new_window() failed!\n");
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->mlx.img)
		cleanup_and_error(data, "mlx_new_image() failed!\n");
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.lsize, &data->mlx.endian);
	if (!data->mlx.addr)
		cleanup_and_error(data, "mlx_get_data_addr() failed!\n");
}

void	init_scene_textures(t_data *data)
{
	load_skybox(data);
	load_object_textures(data);
}
