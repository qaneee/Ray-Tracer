/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:44:09 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 12:03:19 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	change_mode(int keycode, t_data *data)
{
	t_editor_mode	new;

	new = data->mode;
	if (keycode == KEY_C || keycode == KEY_O || keycode == KEY_L)
	{
		if (keycode == KEY_C)
			new = EDIT_CAMERA;
		else if (keycode == KEY_O)
			new = EDIT_OBJECT;
		else if (keycode == KEY_L)
			new = EDIT_LIGHT;
	}
	if (new != data->mode)
	{
		data->mode = new;
		data->needs_redraw = 1;
		return (1);
	}
	return (0);
}

static int	change_obj(int keycode, t_data *data, t_objs *old_obj)
{
	if (keycode == KEY_N)
		data->selected_object = next_object(data->scene.objs,
				data->selected_object);
	else
		data->selected_object = prev_object(data->scene.objs,
				data->selected_object);
	if (old_obj != data->selected_object)
		return (data->needs_redraw = 1, 1);
	return (0);
}

static int	change_light(int keycode, t_data *data, t_light *old_light)
{
	if (keycode == KEY_N)
		data->selected_light = next_light(data->scene.lights,
				data->selected_light);
	else
		data->selected_light = prev_light(data->scene.lights,
				data->selected_light);
	if (old_light != data->selected_light)
		return (data->needs_redraw = 1, 1);
	return (0);
}

int	change_selection(int keycode, t_data *data)
{
	t_objs	*old_obj;
	t_light	*old_light;

	if (keycode != KEY_N && keycode != KEY_P)
		return (0);
	if (data->mode == EDIT_CAMERA)
		return (0);
	if (data->mode == EDIT_OBJECT)
	{
		old_obj = data->selected_object;
		return (change_obj(keycode, data, old_obj));
	}
	else if (data->mode == EDIT_LIGHT)
	{
		old_light = data->selected_light;
		return (change_light(keycode, data, old_light));
	}
	return (0);
}
