/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TITLE "FDF - Wireframe 3D"

# define COLOR_WHITE 0xFFFFFFFF
# define COLOR_BLACK 0x000000FF
# define COLOR_RED 0xFF0000FF
# define COLOR_GREEN 0x00FF00FF
# define COLOR_BLUE 0x0000FFFF
# define COLOR_YELLOW 0xFFFF00FF
# define COLOR_CYAN 0x00FFFFFF
# define COLOR_MAGENTA 0xFF00FFFF

typedef enum e_view
{
	VIEW_ISO,
	VIEW_NORMAL,
	VIEW_TOP,
	VIEW_SIDE
}	t_view;

typedef enum e_color_mode
{
	COLOR_HEIGHT,
	COLOR_GRADIENT,
	COLOR_ORIGINAL,
	COLOR_SOLID
}	t_color_mode;

typedef struct s_fdf	t_fdf;

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	int			color;
	int			has_color;
	int			orig_x;
	int			orig_y;
}	t_point;

typedef struct s_line_data
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line_data;

typedef struct s_draw_params
{
	t_point		*p1;
	t_point		*p2;
	t_line_data	*data;
	t_fdf		*fdf;
}	t_draw_params;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rect;

typedef struct s_map
{
	t_point		**points;
	int			width;
	int			height;
	int			z_min;
	int			z_max;
}	t_map;

typedef struct s_cam
{
	float		zoom;
	float		x_offset;
	float		y_offset;
	float		x_angle;
	float		y_angle;
	float		z_angle;
	float		z_scale;
	t_view		view;
}	t_cam;

typedef struct s_mouse
{
	int			pressed;
	int			button;
	double		x;
	double		y;
	double		prev_x;
	double		prev_y;
}	t_mouse;

typedef struct s_fdf
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*ui_img;
	mlx_image_t		*question_img;
	mlx_image_t		*title_text;
	mlx_image_t		**info_texts;
	int				info_text_count;
	t_map			*map;
	t_cam			*cam;
	t_mouse			*mouse;
	t_color_mode	color_mode;
	int				show_info;
	int				bg_color;
	int				line_color;
	int				adaptive_color;
	int				gradient_color;
}	t_fdf;

t_map		*parse_map(char *filename);
int			get_map_dimensions(char *filename, t_map *map);
int			allocate_map(t_map *map);
int			parse_point(char *str, t_point *point, int x, int y);
void		find_z_limits(t_map *map);

void		draw_map(t_fdf *fdf);
void		draw_line(mlx_image_t *img, t_point p1, t_point p2, t_fdf *fdf);
void		draw_line_pixels(mlx_image_t *img, t_draw_params *params);
void		draw_horizontal_line(t_fdf *fdf, int x, int y);
void		put_pixel(mlx_image_t *img, int x, int y, int color);
void		clear_image(mlx_image_t *img, int color);

void		project_point(t_point *src, t_point *dst, t_fdf *fdf);
void		isometric_projection(t_point *p);
void		apply_rotation(t_point *p, t_cam *cam);
void		apply_view(t_point *p, t_cam *cam);

void		rotate_x(float *y, float *z, float angle);
void		rotate_y(float *x, float *z, float angle);
void		rotate_z(float *x, float *y, float angle);

int			get_point_color(t_point *p, t_fdf *fdf);
int			get_height_color(float z, float z_min, float z_max);
int			interpolate_color(int c1, int c2, float ratio);
int			get_brightness(int color);
int			generate_random_color(void);

void		key_hook(mlx_key_data_t keydata, void *param);
void		mouse_hook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);
void		scroll_hook(double xdelta, double ydelta, void *param);
void		cursor_hook(double xpos, double ypos, void *param);
void		loop_hook(void *param);

void		draw_ui(t_fdf *fdf);
void		draw_info_overlay(t_fdf *fdf);
void		draw_ascii_art(t_fdf *fdf);
void		delete_info_texts(t_fdf *fdf);
void		toggle_info(t_fdf *fdf);
void		draw_title(t_fdf *fdf);
void		draw_background_panel(t_fdf *fdf, t_rect *rect);

const char	*get_view_name(t_view view);
const char	*get_color_mode_name(t_color_mode mode);
int			calculate_total_lines(t_fdf *fdf);
void		draw_current_state(t_fdf *fdf, int x, int *y_pos, int *i);
void		draw_zoom_info(t_fdf *fdf, int x, int *y_pos, int *i);
void		draw_map_stats(t_fdf *fdf, int x, int *y_pos, int *i);
void		draw_controls(t_fdf *fdf, int x, int *y_pos, int *i);
void		draw_view_info(t_fdf *fdf, int x, int *y_pos, int *i);
void		draw_color_info(t_fdf *fdf, int x, int *y_pos, int *i);
void		draw_points_lines_info(t_fdf *fdf, int x, int *y_pos, int *i);
void		setup_panel_data(t_fdf *fdf, int *panel_data, t_rect *panel);
void		draw_all_sections(t_fdf *fdf, int *panel_data, int *i, int *y_pos);
void		init_info_texts(t_fdf *fdf, int *panel_data);
void		draw_info_header(t_fdf *fdf, int *panel_data, int *i, int *y_pos);

t_fdf		*init_fdf(char *filename);
t_cam		*init_camera(t_map *map);
t_mouse		*init_mouse(void);
int			map_has_colors(t_map *map);
void		reset_camera(t_fdf *fdf);
void		validate_camera(t_fdf *fdf);
void		free_map(t_map *map);
void		cleanup_fdf(t_fdf *fdf);
void		error_exit(char *msg);

#endif