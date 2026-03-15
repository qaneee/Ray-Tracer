/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:02:50 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 17:54:05 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	move_pos_world(t_vec3 *pos, int keycode, float step)
{
	if (!pos)
		return (0);
	if (keycode == KEY_W || keycode == KEY_UP)
		pos->z -= step;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		pos->z += step;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		pos->x -= step;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		pos->x += step;
	else if (keycode == KEY_Q)
		pos->y += step;
	else if (keycode == KEY_E)
		pos->y -= step;
	else
		return (0);
	return (1);
}

void	move_camera_up(t_data *d, float step)
{
	d->scene.camera.pos.y += step;
}

void	move_camera_down(t_data *d, float step)
{
	d->scene.camera.pos.y -= step;
}

int	handle_refresh(t_data *data)
{
	if (!data || !data->mlx.mlx || !data->mlx.win || !data->mlx.img)
		return (0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
