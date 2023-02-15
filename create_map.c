#include "../inc/cub3D.h"

static void	space_to_wall(t_world *world)
{
	int	i;
	int	j;

	i = 0;
	while (world->maptab[i])
	{
		j = 0;
		while (world->maptab[i][j] == ' ' || world->maptab[i][j] == '\t'
			|| world->maptab[i][j] == '\r' || world->maptab == '\v'
			|| world->maptab[i][j] == '\f')
			j++;
		while (world->maptab[i][++j])
		{
			if (world->maptab[i][j] == ' '
				&& j != world->maptab[i][ft_strlen(world->maptab[i]) - 1])
				world->maptab[i][j] = '1';
		}
		i++;
	}
}

static int	lines_counter(t_world *world, char **map, int i)
{
	int	ind;
	int	j;

	ind = i;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\r'
			|| map[i][j] == '\v' || map[i][j] == '\f')
			j++;
		if (map[i][j] != '1')
			break ;
		i++;
	}
	data->map.map_end = i;
	return (i - ind);
}

static int	fill_tab(t_map *map, char **maptab, int i)
{
	int	k;
	int	l;

	map->width = get_max_len(map, i);
	k = 0;
	while (k < map->height)
	{
		l = 0;
		maptab[k] = malloc(sizeof(char) * (map->width + 1));
		if (!maptab[k])
			return (print_error());
		while (map->map[i][l] && map->map[i][l] != '\n')
		{
			maptab[k][l] = map->map[i][l];
			l++;
		}
		while (l < maptab->width)
			maptab[k][l++] = '\0';
		k++;
		i++;
	}
	maptab[k] = NULL;
	return (0);
}

static int	malloc_map(t_world *world, char **map, int i)
{
	world->map.height = lines_counter(world, map, i);
	world->maptab = malloc(sizeof(char *) * (world->map.height + 1));
	if (world->maptab)
		return (print_error());
	if (fill_tab(&world->map, world->maptab, i) == -1)
		return (-1);
	return (0);
}

int	create_map(t_world *world, char **map, int i)
{
	if (malloc_map(world, map, i) == -1)
		return (-1);
	space_to_wall(world);
	return (0);
}
