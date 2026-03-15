/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:04:03 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/13 19:14:46 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vec3		t_vec3;
typedef struct s_color		t_color;
typedef struct s_texture	t_texture;
typedef struct s_objs		t_objs;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;
typedef struct s_hit		t_hit;
typedef struct s_mlx		t_mlx;
typedef struct s_scene		t_scene;
typedef struct s_parse		t_parse;

typedef enum e_type
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE
}	t_type;

typedef enum e_editor_mode
{
	EDIT_CAMERA,
	EDIT_OBJECT,
	EDIT_LIGHT
}	t_editor_mode;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_objs
{
	t_type			type;
	t_vec3			pos;
	t_color			color;
	t_vec3			orientation;
	float			diameter;
	float			radius;
	float			height;
	int				checkerboard;
	float			reflection;
	char			*bump_map;
	float			specular;
	float			shininess;
	int				has_specular;
	int				has_shininess;
	float			radius_sq;
	float			half_height;
	float			cone_k;
	t_vec3			cap_top_center;
	t_vec3			cap_bottom_center;
	t_vec3			cone_base_center;
	t_texture		*texture;
	struct s_objs	*next;
}	t_objs;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	float	fov;
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	right;
	t_vec3	forward; // normalized direction
	float	viewport_width;
	float	viewport_height;
	float	aspect_ratio;
}	t_camera;

typedef struct s_light
{
	t_color			color;
	t_vec3			pos;
	float			brightness;
	struct s_light	*next;
}	t_light;

typedef struct s_ray
{
	t_vec3	direct;
	t_vec3	origin;	
}	t_ray;

typedef struct s_hit
{
	float	t;
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
	t_objs	*objs;
	float	u;
	float	v;
}	t_hit;

typedef struct s_mlx
{
	void	*img;
	char	*addr;
	void	*mlx;
	void	*win;
	int		bpp;
	int		lsize;
	int		endian;
}	t_mlx;

typedef struct s_scene
{
	t_ambient	amb;
	t_camera	camera;
	t_light		*lights;
	t_objs		*objs;
	int			width;
	int			height;
	int			obj_count;
	int			light_count;
	int			has_amb;
	int			has_camera;
	int			has_skybox;
	char		*skybox_path;
	t_texture	*skybox;
}	t_scene;

typedef struct s_parse
{
	char	*line;
	char	**tokens;
	int		fd;
	t_scene	*sc;
}	t_parse;

typedef struct s_data
{
	t_mlx			mlx;
	t_scene			scene;
	t_objs			*selected_object;
	t_light			*selected_light;
	t_editor_mode	mode;
	int				needs_redraw;
}	t_data;

#endif
