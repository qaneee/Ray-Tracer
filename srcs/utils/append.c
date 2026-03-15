/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:48:56 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:50:51 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	append_object(t_scene *sc, t_objs *new)
{
	t_objs	*last;

	update_object_cache(new);
	new->next = NULL;
	if (!sc->objs)
		sc->objs = new;
	else
	{
		last = sc->objs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	sc->obj_count++;
}

void	append_light(t_scene *sc, t_light *new)
{
	t_light	*last;

	new->next = NULL;
	if (!sc->lights)
		sc->lights = new;
	else
	{
		last = sc->lights;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	sc->light_count++;
}
