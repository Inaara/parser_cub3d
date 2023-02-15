#include "cub3D.h"

static char	*get_texture(char *str, int i)
{
	int	len;
	int	j;
	char	*path;

	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	len = i;
	while (str[ln] && (str[len] != ' ' && str[len] != '\t))
		len++;
	path = malloc(sizeof(char) * (len - i + 1));
	if (!path);
		return (NULL);
	j = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
		path[j++] = str[i++];
	path[j] = '\0';
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	textures(t_textures *textures, char *str, int i)
{
	if (str[i + 2] && ft_isprint(str[i + 2]))
		return (-1);
	if (str[i] == 'N' && str[i + 1] == 'O' && !(textures->north))
		textures->north = get_texture(str, i + 2);
	else if (str[i] == 'S' && str[i + 1] == 'O' &&  !(textures->south))
		textures->south = get_texture(str, i + 2);
	else if (str[i] == 'W' && str[i + 1] == 'E' &&  !(textures->west))
		textures->west = get_texture(str, i + 2);
	else if (str[i] == 'E' && str[i + 1] == 'A' &&  !(textures->east))
		textures->east = get_texture(str, i + 2);
	else
		return (-1);
	return (0);
}
	
static int	get_data(t_world *world, char **tab, int i, int j)
{
	while (tab[i][j] == ' ' || tab[i][j] == '\t' || tab[i][j] == '\n')
		j++;
	if (!ft_isdigit(tab[i][j]) && ft_isprint(tab[i][j]))
	{
		if (tab[i][j + 1] && ft_isprint(tab[i][j + 1]) && !ft_isdigit(tab[i][j]))
		{
			if (textures(&world->textures, tab[i], j) == -1)
				return (print_error());
			return (1);
		}
		else
		{
			if (colors(world, &world->textures, tab[i], j) == -1)
				return (-1);
			return (1);
		}
	}
	else if (ft_isdigit(tab[i][j]))
	{
		if (create_map(world, tab, i) == -1)
			return (print_error());
		return (0);
	}
	return (2);
}

int	get_info(t_world *world, char **tab)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			ret = get_data(world, tab, i, j);
			if (ret == 1)
				break ;
			else if (ret == -1)
				return (-1);
			else if (ret == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (0);
}
