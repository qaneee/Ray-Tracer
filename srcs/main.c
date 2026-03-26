/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:53:16 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/26 12:07:58 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (argc != 2)
		print_error("Wrong argument count\n");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3))
		print_error("Wrong scene descriptor format\n");
	init_scene(&data.scene);
	parse_file(&data.scene, argv[1]);
	init_mlx(&data);
	data.mode = EDIT_CAMERA;
	data.selected_object = data.scene.objs;
	data.selected_light = data.scene.lights;
	data.needs_redraw = 0;
	init_scene_textures(&data);
	render_scene(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx.mlx);
	cleanup_and_exit(&data);
	return (0);
}
