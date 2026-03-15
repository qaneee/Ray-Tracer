/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 22:11:18 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 17:53:10 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	handle_x(t_data *data)
{
	cleanup_and_exit(data);
	return (0);
}

static int	ret_moved(int keycode, t_data *data, int *moved)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		return (move_forward(data, STEP), *moved = 1, *moved);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		return (move_right(data, STEP), *moved = 1, *moved);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		return (move_backward(data, STEP), *moved = 1, *moved);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		return (move_left(data, STEP), *moved = 1, *moved);
	else if (keycode == KEY_Q)
		return (move_camera_up(data, STEP), *moved = 1, *moved);
	else if (keycode == KEY_E)
		return (move_camera_down(data, STEP), *moved = 1, *moved);
	return (0);
}

static int	handle_object_mode(int keycode, t_data *data)
{
	int	moved;

	moved = 0;
	moved |= move_pos_world(&data->selected_object->pos, keycode, STEP);
	moved |= rotate_object(data->selected_object, keycode, ROTATE_STEP);
	moved |= resize_object(data->selected_object, keycode, RESIZE_STEP);
	if (moved)
		update_object_cache(data->selected_object);
	return (moved);
}

static int	key_handle(int keycode, t_data *data)
{
	int	moved;
	int	changed;

	moved = 0;
	changed = 0;
	changed |= change_mode(keycode, data);
	changed |= change_selection(keycode, data);
	if (data->mode == EDIT_CAMERA)
	{
		ret_moved(keycode, data, &moved);
		moved |= rotate_camera_dir(&data->scene.camera, keycode, ROTATE_STEP);
	}
	if (data->mode == EDIT_OBJECT && data->selected_object)
		moved |= handle_object_mode(keycode, data);
	if (data->mode == EDIT_LIGHT && data->selected_light)
		moved |= move_pos_world(&data->selected_light->pos, keycode, STEP);
	if (keycode == KEY_ESC)
		cleanup_and_exit(data);
	if (moved || changed || data->needs_redraw)
	{
		render_scene(data);
		data->needs_redraw = 0;
	}
	return (0);
}

void	mlx_exit(t_data *data)
{
	mlx_expose_hook(data->mlx.win, handle_refresh, data);
	mlx_hook(data->mlx.win, 22, 1L << 17, handle_refresh, data);
	mlx_hook(data->mlx.win, 2, 1L << 0, key_handle, data);
	mlx_hook(data->mlx.win, 17, 0, handle_x, data);
}
