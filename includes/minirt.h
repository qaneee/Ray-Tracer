/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:22:16 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/13 19:37:15 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>
# include <sys/time.h>
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>
# include "structs.h"
# include "defines.h"

//utils
int		get_color(t_color color);
void	print_error(char *msg);
void	free_split(char **str);
void	skip_whitespaces(char **str);
int		valid_color(t_color *color);
void	trim_whitespaces(char *str);
void	free_scene(t_scene *sc);
int		is_normalized(t_vec3 vec);
void	make_all_spaces(char *line);
void	append_object(t_scene *sc, t_objs *new);
void	append_light(t_scene *sc, t_light *new);
int		arg_count(char **tokens);
void	mlx_error(t_mlx	*var);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	free_mlx(t_data *data);

//parser + validation
void	parse_file(t_scene *sc, char *file_name);
void	parse_line(t_parse *p, int *has_content);
int		is_valid_float(char *str);
int		parse_int(char *str);
float	parse_float(char *str);
t_vec3	parse_vector(char *str);
t_vec3	parse_normalized_vector(char *str);
t_color	parse_color(char *str);
void	parse_ambient(t_parse *p);
void	parse_camera(t_parse *p);
void	parse_light(t_parse *p);
void	parse_sphere(t_parse *p);
void	parse_cylinder(t_parse *p);
void	parse_plane(t_parse *p);
void	parse_cone(t_parse *p);
void	identify_all(t_parse *p);
int		parse_optional(t_objs *new, char *token);
void	args_loop(int *start, int *end, t_objs *new, t_parse *p);
void	parse_skybox(t_parse *p);
int		parse_texture(t_objs *new, char *token);
int		parse_mirror(t_objs *new, char *token);
int		parse_checker(t_objs *new, char *token);
int		parse_specular(t_objs *new, char *token);
int		parse_shininess(t_objs *new, char *token);
void	free_parsing_fail(t_parse *p);

// math
t_vec3	normal_vector(t_vec3 vec);
float	point_dist(const t_vec3 *point1, const t_vec3 *point2);
t_vec3	cross_product(t_vec3 a, t_vec3 b);
float	dot_product(t_vec3 a, t_vec3 b);
float	vec_length(t_vec3 vec);
float	ft_quadratic(float a, float b, float c);
t_vec3	vec_add(t_vec3 p1, t_vec3 p2);
t_vec3	vec_subt(t_vec3 p1, t_vec3 p2);
t_vec3	vec_scale(t_vec3 vec, float mult_factor);
t_vec3	set_vector(float x, float y, float z);
float	fov_to_radians(t_camera *c);

//init
void	init_scene(t_scene *sc);
void	init_object(t_objs *obj);
void	init_mlx(t_data *data);
void	init_scene_textures(t_data *data);

//rays
t_color	trace_ray(t_scene *sc, t_ray *ray, int depth);
void	render_scene(t_data *data);

// intersections
int		intersect_cylinder(t_ray ray, t_objs *cy, float *t);
int		clampf_height_cy(t_vec3 hit, t_objs *cy);
void	perp_component(t_ray ray, t_objs *cy, t_vec3 *d_perp, t_vec3 *co_perp);
float	quad_for_cyl(t_vec3 d_perp, t_vec3 co_perp, float radius);
int		inside_disk_cy(t_ray ray, t_vec3 center, float radius_sq, float t);
int		intersect_plane_at(t_ray ray, t_vec3 center, t_vec3 normal, float *t);
int		intersect_plane(t_ray ray, t_objs *plane, float *t);
int		intersect_sphere(t_ray ray, t_objs *sphere, float *t);
int		intersect_cone(t_ray ray, t_objs *co, float *t);
int		closest_intersection(t_scene *sc, t_ray *ray, t_hit *hit);
int		cone_base_normal(t_hit *hit, t_vec3 *out);
int		cylinder_cap_normal(t_hit *hit, t_vec3 *out);
t_vec3	cone_side_normal(t_hit *hit);
void	calculate_normal(t_hit *hit);
int		intersect_obj(t_ray *ray, t_objs *obj, float *t);
void	update_object_cache(t_objs *obj);

// camera
void	init_camera(t_camera *cam, int width, int height);
t_ray	get_camera_ray(t_camera *cam, int x, int y, t_scene *sc);

// lighting
t_color	calc_ambient(t_scene *sc, t_color obj_color);
t_color	calc_diffuse(t_scene *sc, t_hit *hit);
int		is_in_shadow(t_scene *s, t_vec3 p, t_vec3 light_norm, float light_dst);
t_color	combine_lighting(t_scene *sc, t_hit *hit, t_vec3 view_pos);
t_color	calc_specular(t_scene *sc, t_hit *hit, t_vec3 view_pos);
t_color	get_reflect_vec(t_scene *sc, t_hit *hit, t_ray *incoming, int depth);
t_color	blend_color(t_color base, t_color reflect, float ref_coef);

// events and hooks
void	mlx_exit(t_data *data);
void	cleanup_and_exit(t_data *data);
void	move_forward(t_data *d, float step);
void	move_backward(t_data *d, float step);
void	move_right(t_data *d, float step);
void	move_left(t_data *d, float step);
int		change_mode(int keycode, t_data *data);
int		change_selection(int keycode, t_data *data);
int		move_pos_world(t_vec3 *pos, int keycode, float step);
void	move_camera_down(t_data *d, float step);
void	move_camera_up(t_data *d, float step);
t_vec3	rotate_axis(t_vec3 vec, t_vec3 axis, float degrees);
int		rotate_camera_dir(t_camera *cam, int keycode, float degrees);
int		rotate_object(t_objs *obj, int keycode, float degrees);
t_objs	*next_object(t_objs *head, t_objs *curr);
t_objs	*prev_object(t_objs *head, t_objs *curr);
t_light	*next_light(t_light *head, t_light *curr);
t_light	*prev_light(t_light *head, t_light *curr);
int		resize_object(t_objs *obj, int keycode, float step);;
int		handle_refresh(t_data *data);

// patterns
t_color	get_object_color(t_hit *hit);
t_color	apply_checkerboard(t_hit *hit);

// uv mapping
void	calculate_uv_sphere(t_hit *hit);
void	calculate_uv_plane(t_hit *hit);
void	calculate_uv_cy_co(t_hit *hit);
void	calculate_uv(t_hit *hit);
t_color	get_texture_color(t_texture *tex, float u, float v);
t_vec3	perturb_normal(t_hit *hit);
void	load_skybox(t_data *data);
t_color	get_skybox_color(t_scene *sc, t_ray *ray);
void	load_object_textures(t_data *data);

#endif
