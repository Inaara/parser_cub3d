#include "../inc/cub3D.h"

static int	check_color(t_color *color)
{
	if (color->r < 0 || color->r > 255)
		return (print_error());
	if (color->g < 0 || color->g > 255)
		return (print_error());
	if (color->b < 0 || color->b > 255)
		return (print_error());
	return (0);
}

static unsigned long	convert_color_to_hex(t_color *color)
{
	unsigned long	hex;
	int		r;
	int		g;
	int		b;

	r = color->r;
	g = color->g;
	b = color->b;
	hex = ((r & 0xff) << 16) + ((g & 0Xff) << 8) + (b & 0xff);
	return (hex);
}

int	check_textures(t_world *world, t_textures *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (ptint_error());
	if (!textures->floor || !textures->ceiling)
		return (pint_error());
	if (check_texture_file(textures->north) == -1
		|| check_texture_file(textures->south) == -1
		|| check_texture_file(textures->west) == -1
		|| check_texture_file(textures->east) == -1
		|| check_color(textures->floor) == -1
		|| check_color(textures->ceiling) == -1)
		return (-1);
	textures->hex_floor = convert_color_to_hex(textures->floor);
	textures->hex_ceiling = convert_color_to_hex(textures->ceiling);
	return (0);
}
