/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:04:42 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/13 19:15:13 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit (1);
}

void	mlx_error(t_mlx	*var)
{
	if (!var->win)
	{
		mlx_destroy_display(var->mlx);
		free(var->mlx);
		print_error("mlx_new_window() failed!\n");
	}
	else if (!var->img)
	{
		mlx_destroy_window(var->mlx, var->win);
		mlx_destroy_display(var->mlx);
		free(var->mlx);
		print_error("mlx_new_image() failed!\n");
	}
	else if (!var->addr)
	{
		mlx_destroy_image(var->mlx, var->img);
		mlx_destroy_window(var->mlx, var->win);
		mlx_destroy_display(var->mlx);
		free(var->mlx);
		print_error("mlx_get_data_addr() failed!\n");
	}
}
