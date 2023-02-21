#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define mapWidth 24
#define mapHeight 24

typedef struct s_data {
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vect {
	float	x;
	float	y;
}	t_vect;

typedef struct s_camera {
	char	dir;
	t_vect	position;
	t_vect	direction;
	t_vect	plane;
}	t_camera;

typedef struct s_window {
	void	*reference;
	t_vect	size;
}	t_window;

typedef struct s_textures {
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	t_color	floor;
	t_color	ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int		index;
	float		step;
	float		pos;
	int		x;
	int		y;
	int		texil;
}	t_textures;

typedef struct s_map {
	int	fd;
	int	lines;
	char	*file;
	char	**tab;
	int	height;
	int	width;
	int	end;
}	t_map;

typedef struct s_world {
	void		*mlx;
	t_window	window;
	t_vect		size;
	t_map		map;
	char			**maptab;
	t_camera	camera;
	t_textures	textures;
	int		**tex;
	int		**texture_pixels;
}	t_world;

typedef struct s_raycast {
	int		x;
	t_vect	ray_direction;
	t_vect	camera_direction;
	t_vect	current_square;
	t_vect	side_dist;
	t_vect	delta_dist;
	t_vect	step;
	float	wall_dist;
	float	wall_x;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_stop;
	t_data	img;
	int		color;
}	t_raycast;

/*PARSING*/

int	check_map(t_world *world, char **map);
int	left_right_side(t_map *maptab, char **map);
int	check_textures(t_world *world, t_textures *textures);
void	parse_world(char *file, t_world *world);
int	check_input_file(char *file);
int	create_map(t_world *world, char **map, int i);
int	get_info(t_world *world, char **tab);
void	set_color(t_color *color, int r, int g, int b);
int	print_error(void);
int	colors(t_world *world, t_textures *tex, char *s, int i);
void	init_world(t_world *world);
void    init_raycast(t_raycast *ray);
void    set_textures(t_world *world);
void    init_texture_pixels(t_world *world);
void    update_texture_pixels(t_world *world, t_textures *tex, t_raycast *ray, int x);
void	get_texture_index(t_world *world, t_raycast *ray);

void set_vector(t_vect *vect, float x, float y);
float absolute_value(float value);
float get_dist_side(float ray_direction);
void raycasting_init(t_raycast *r, t_world *world);
void	raycasting_step_init(t_raycast *r, t_world *w);
void	dda_init(t_raycast *r, t_world *w);
void	dda_step(t_raycast *r, t_world *w);
void	wall_dist(t_raycast *r);
void	get_line(t_raycast *r, t_camera *camera);
void	choose_color(t_raycast *r, t_world *world);
int	create_trgb(int t, int r, int g, int b);
void	world_init(t_world *world);
int	monitor_input(int key, t_world *world);
void	sub_vector(t_vect v1, t_vect v2, t_vect *result);
void	mult_vector(float m, t_vect vect, t_vect *result);
void	add_vector(t_vect v1, t_vect v2, t_vect *result);
void	copy_vector(t_vect src, t_vect *dst);
void	get_perpandicular(t_vect src, t_vect *result);
void	init_data(t_data *data);

int	free_world(t_world *world);
int	free_data(t_data *data);
void	exit_cub3d(t_world *world);
void	free_maptab(void **map);
#endif
