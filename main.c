#include "../includes/cub3d.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	pixel;

	pixel = y * (data->line_length / 4) + x;
	data->addr[pixel] = color;
//	char	*dst;
//
//	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//	*(unsigned int*)dst = color;
}


void draw_vertical_line(t_data *data, t_textures *tex, int x, int draw_start, int draw_end, t_world *world, t_raycast *ray)
{
	int	y;
	int	color;
//	(void)draw_end;
//	(void)color;

	get_texture_index(world, ray);
	tex->x = (int)(ray->wall_x * 64);
//	printf("tex->x = %d\n", tex->x);
	if ((ray->side == 0 && ray->ray_direction.x < 0)
		|| (ray->side == 1 && ray->ray_direction.y > 0))
		tex->x = 64 - tex->x - 1;
	tex->step = 1.0 * 64 / ray->line_height;
	tex->pos = (ray->draw_start - SCREEN_HEIGHT / 2
			+ ray->line_height / 2) * tex->step;
//	y = ray->draw_start;
	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(data, x, y, create_trgb(0, tex->ceiling.r, tex->ceiling.g, tex->ceiling.b));
		y++;
	}
	while (y < draw_end)
	{
		tex->y = (int)tex->pos & (64 - 1);
		tex->pos += tex->step;
		color = world->tex[tex->index][64 * tex->y + tex->x];
		if (tex->index == 0 || tex->index == 2)
			color = (color >> 1) & 8355711;
		if (color > 0)
			world->texture_pixels[y][x] = color;

		my_mlx_pixel_put(data, x, y, world->texture_pixels[y][x]);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(data, x, y, create_trgb(0, tex->floor.r, tex->floor.g, tex->floor.b));
		y++;
	}
}

void print_vector(char *name, t_vect vector)
{
	printf("%s : (%f, %f)\n", name, vector.x, vector.y);
}

int raycast(t_world *world)
{
	t_raycast r; 

	init_raycast(&r);
	init_texture_pixels(world);
	raycasting_init(&r, world);
	while (r.x < SCREEN_WIDTH)
	{
		raycasting_step_init(&r, world);
		dda_init(&r, world);
		while (!r.hit)
			dda_step(&r, world);
		wall_dist(&r);
		get_line(&r, &world->camera);
//		choose_color(&r, world);
		draw_vertical_line(&r.img, &world->textures, r.x, r.draw_start, r.draw_stop, world, &r);
		r.x++;
	}
	mlx_put_image_to_window(world->mlx, world->window.reference, r.img.img, 0, 0);
	mlx_destroy_image(world->mlx, r.img.img);
	return (0);
}

static int	check_input(t_world *world, char **av)
{
	if (check_input_file(av[1]) == -1)
		return (-1);
	parse_world(av[1], world);
	if (get_info(world, world->map.tab) == -1)
		return (free_world(world));
	if (check_map(world, world->maptab) == -1)
		return (free_world(world));
	if (check_textures(world, &world->textures) == -1)
		return (free_world(world));
	return (0);
}

/*static void	print_world(t_world *world)
{
	int i = 0, j = 0;

	printf("WORLD->MAPTAB\n\n");
	while (world->maptab[i])
	{
		j = 0;
		while (world->maptab[i][j])
		{
			printf("%c ", world->maptab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
	printf("WORLD->MAP.TAB");
	i = 0;
	while (world->map.tab[i])
	{
		j = 0;
		while (world->map.tab[i][j])
		{
			printf("%c", world->map.tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
	printf("WORLD->MAP.HEIGHT AND WIDTH\n");
	printf("%d %d\n\n", world->map.height, world->map.width);
	printf("\nWORLD->CAMERA.DIR, POSITION, DIRECTION, PLANE\n");
	printf("%c\n", world->camera.dir);
	print_vector("Position", world->camera.position);
	print_vector("\nDirection", world->camera.direction);
	print_vector("\nPlane", world->camera.plane);
	printf("\nWORLD->CAMERA.TEXTURES\n");
	printf("north = %s\n south = %s\n west = %s\n east = %s\n", world->textures.north,
		world->textures.south, world->textures.west, world->textures.east);
	printf("\nhex_floor = %lu\nhex_ceiling = %lu\n", world->textures.hex_floor, world->textures.hex_ceiling);
}*/
	


int main(int ac, char **av)
{
	t_world	world;

	if (ac != 2)
		return (print_error());
	init_world(&world);
	world.textures.texil = 64;
	world.mlx = mlx_init();
	if (check_input(&world, av) != 0)
		return (print_error());
	if (!world.mlx)
		return (print_error());
	world.window.reference = mlx_new_window(world.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!world.window.reference)
		return (print_error());
	set_vector(&world.camera.plane, 1, 0.66);
	set_textures(&world);
	/* print_world(&world); */
	mlx_loop_hook(world.mlx, &raycast, (void *)&world);
	mlx_key_hook(world.window.reference, &monitor_input, &world);
	mlx_loop(world.mlx);
}
