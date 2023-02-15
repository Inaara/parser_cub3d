#include "../inc/cub3D.h"

static int	up_down_side(char **map, int i, int j)
{
	if (!map || !map[i] || !map[i][j])
		return (-1);
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\r'
		|| map[i][j] == '\v' || map[i][j] == '\f')
		j++;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (-1);
		j++;
	}
	return (0);
}

int	left_right_side(t_map *maptab, char **map)
{
	int	i;
	int	j;

	if (up_down-side(map, 0, 0) == -1)
		return (-1);
	i = 1;
	while (i < (maptab->height - 1))
	{
		j = ft_strlen(map[i]) - 1;
		if (map[i][j] != '1')
			return (-1);
		i++;
	}
	if (up_sown_side(map, i, 0) == -1)
		return (-1);
	return (0);
}
