#include "cub3D.h"

int	check_input_file(char *file)
{
	int	fd;
	int	len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	len = ft_strlen(file);
	if ((file[len - 3] != 'c' || file[len - 2] != 'u'
		|| file[len - 1] != 'b' || file[len - 4] != '.'))
		return (-1);
	return (0);
}

static int	lines_count(char *file)
{
	int	fd;
	char	*str;
	int	count;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error();
	else
	{
		str = get_next_line(fd);
		while (str != NULL)
		{
			count++;
			free(str);
			str = get_next_line(fd);
		}
		close(fd);
	}
	return (count);
}

strtic void	create_tab(int r, int c, int i, t_world *world)
{
	char	*str;

	str = get_next_line(world->map.fd);
	while (str != NULL)
	{
		data->map.tab[r] = ft_calloc(ft_strlen(str) + 1, sizeof(char));
		if (!world->map.tab[r])
		{
			print_error();
			return (free_tab((void **)data->map.tab));
		}
		while (str[i] != '\0')
			world_.map.tab[r][c++] = str[i++];
		world->map.tab[r++][c] = '\0';
		c = 0;
		i = 0;
		free(str);
		str = get_next_line(world->map.fd);
	}
	world->map.tab[r] = NULL;
}

void	parse_world(char *file, t_world *world)
{
	int	row;
	int	col;
	int	i;

	i = 0;
	row = 0;
	col = 0;
	world->map.lines = lines_count(file);
	world->map.file = file;
	world->map.tab = ft_calloc(world->map.lines + 1, sizeof(char *));
	if (!(world->map.tab))
	{
		print_error();
		return ;
	}
	world->map.fd = open(file, O_RDONLY);
	if (world->map.fd < 0)
		print_error();
	else
	{
		create_tab(row, col, i, world);
		close(world->map.fd);
	}
}
