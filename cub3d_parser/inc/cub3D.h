#ifndef CUB3D_H
# define CUB3D_H

#include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
//# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

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
}	t_textures;
typedef struct s_ch_map
{
	int		n;
	int		s;
	int		w;
	int		e;
	int		amount;
	int		space_line;
}				t_ch_map;

typedef struct s_world {
	void		*mlx;
	t_window	window;
	t_vect		size;
	char			**map;
	int			width;
	int			height;
	t_camera	camera;
	t_textures	*textures;
	t_ch_map	*checker;
}	t_world;

typedef struct s_check
{
	int		north;
	int		south;
	int		west;
	int		east;
	int		floor;
	int		ceiling;
	int		amount;
	int		fd;
	char	*line;
	char	*trimmed;
}	t_check;

/*Parsing*/

void	parse_textures(char **argv, t_world  *world);
void	add_color_of_floor_and_ceiling(char **args, t_check *ch, t_textures *textures);
void	parse_map(t_check *ch, t_world *world);
void	exit_error(char *str, int num);
void	init_check_struct(t_check	*ch);
void	free_double_array(char **arr);
char	*ft_spaces_str(int width, int len);
void	check_map_correctness(t_world *all);
void	free_chained_list(t_list *head);

void set_vector(t_vect *vect, float x, float y);

#endif
