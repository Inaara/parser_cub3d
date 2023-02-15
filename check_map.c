#include "../inc/cub3D.h"

static int	check_content(t_world *world, char **map)
{
	int	i;
	int	j;

	i = 0;
	world->camera.dir = '0';
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			while (world->maptab[i][j] == ' ' || world->maptab[i][j] == '\t'
			|| world->maptab[i][j] == '\r' || world->maptab[i][j] == '\v'
			|| world->maptab[i][j] == '\f')
				j++;
			if (!(ft_strchr("01NSEW", map[i][j])))
				return (print_error());
			if (ft_strchr("NSEW", map[i][j]) && world->camera.dir != '0')
				return (print_error());
			if (ft_strchr("NSEW", map[i][j]) && data->camera.dir == '0')
				data->camera.dir = map[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

static int	valid_position(t_world *world, char **map)
{
	int	i;
	int	j;

	i = (int)world->camera.position.y;
	j = (int)world->camera.position.x;
	if (ft_strlen(map[i - 1]) < (size_t)j
		|| ft_strlen(map[i + 1] < (size_t)j
		|| is_a_white_space(map[i][j - 1]) == 0
		|| is_a_white_space(map[i][j + 1]) == 0
		|| is_a_white_space(map[i - 1][j]) == 0
		|| is_a_white_space(map[i + 1][j]) == 0)
		return (-1);
	return (0);
}

static int	check_position(t_world *world, char **map)
{
	int	i;
	int	j;

	if (world->camera.dir == '0')
		return (print_error());
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				data->camera.position.x = (double)j + 0.5;
				data->camera.position.y = (double)i + 0.5;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (valid_position(world, map) == -1)
		return (print_error());
	return (0);
}

static int	check_map_position(t_map *map)
{
	int	i;
	int	j;

	i = map->end;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != ' ' && map->map[i][j] != '\t'
				&& map->map[i][j] != '\r' && map->map[i][j] != '\n'
				&& map->map[i][j] != '\v' && map->map[i][j] !+ '\f')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
int	check_map(t_world *world, char **map)
{
	if (!world->map)
		return (print_error());
	if (check_borders(&world->map, map) == -1)
		return (print_error());
	if (world->map.height < 3)
		return (print_error());
	if (check_content(world, map) == -1)
		return (-1);
	if (check_position(world, map) == -1)
		return (-1);
	if (check_map_position(&world->map) == -1)
		return (print_error());
	return (0);
}
