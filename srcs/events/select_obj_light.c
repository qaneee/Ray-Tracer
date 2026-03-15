/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_obj_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:44:53 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 11:38:00 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_objs	*next_object(t_objs *head, t_objs *curr)
{
	if (!head)
		return (NULL);
	if (!curr)
		return (head);
	if (curr->next != NULL)
		return (curr->next);
	return (head);
}

t_objs	*prev_object(t_objs *head, t_objs *curr)
{
	if (!head)
		return (NULL);
	if (!curr || head == curr)
	{
		while (head->next)
			head = head->next;
		return (head);
	}
	while (head->next && head->next != curr)
		head = head->next;
	return (head);
}

t_light	*next_light(t_light *head, t_light *curr)
{
	if (!head)
		return (NULL);
	if (!curr)
		return (head);
	if (curr->next != NULL)
		return (curr->next);
	return (head);
}

t_light	*prev_light(t_light *head, t_light *curr)
{
	if (!head)
		return (NULL);
	if (!curr || head == curr)
	{
		while (head->next)
			head = head->next;
		return (head);
	}
	while (head->next && head->next != curr)
		head = head->next;
	return (head);
}
