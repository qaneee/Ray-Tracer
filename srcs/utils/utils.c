/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:07:36 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/05 20:50:15 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_normalized(t_vec3 vec)
{
	float	len;

	len = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	if (len < 1e-6)
		return (0);
	return (fabs(len - 1.0) < 0.0001);
}

int	arg_count(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->lsize + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
