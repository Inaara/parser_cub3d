/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:09:45 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/13 17:17:12 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	skip_empty_lines(t_check *ch)
{
	ch->trimmed = ft_strtrim(ch->line, " \t\v\f\r");
	if (ch->trimmed && *(ch->trimmed))
	{
		free(ch->trimmed);
		return ;
	}
	if (ch->line)
		free(ch->line);
	if (ch->trimmed)
		free(ch->trimmed);
	while (get_next_line(ch->fd, &ch->line))
	{
		ch->trimmed = ft_strtrim(ch->line, " \t\v\f\r");
		if (ch->trimmed && *(ch->trimmed))
		{
			free(ch->trimmed);
			break ;
		}
		free(ch->line);
		ch->line = NULL;
		free(ch->trimmed);
		ch->trimmed = NULL;
	}
	if (!ch->line || !*(ch->line))
		exit_error("Error with map data!", 6);
}

void	check_path_to_texture(char *str)
{
	int	len;
	int	fd;

	len = ft_strlen(str);
	if (ft_strncmp(".xpm", str + len - 4, 5))
		exit_error("Wrong texture format", 7);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_error("Couldn't open file with texture", 8);
	close(fd);
}

void	add_path_to_texture(char **args, t_check *ch, t_textures *textures)
{
	check_path_to_texture(args[1]);
	if (!ft_strncmp("NO", args[0], 3) && !ch->north)
	{
		textures->north = ft_strdup(args[1]);
		ch->north++;
	}
	else if (!ft_strncmp("SO", args[0], 3) && !ch->south)
	{
		textures->south = ft_strdup(args[1]);
		ch->south++;
	}
	else if (!ft_strncmp("WE", args[0], 3) && !ch->west)
	{
		textures->west = ft_strdup(args[1]);
		ch->west++;
	}
	else if (!ft_strncmp("EA", args[0], 3) && !ch->east)
	{
		textures->east = ft_strdup(args[1]);
		ch->east++;
	}
	else
		exit_error("Identifiers repetitive", 9);
}

void	add_texture_to_struct(t_textures *textures, t_check *ch)
{
	char	**args;

	args = ft_split(ch->trimmed, ' ');
	free(ch->trimmed);
	ch->trimmed = NULL;
	if (args[2] || !args[0] || !args[1])
		exit_error("Wrong amount of args in texture parsing", 10);
	if (!ft_strncmp("NO", args[0], 3) || !ft_strncmp("SO", args[0], 3)
		|| !ft_strncmp("WE", args[0], 3) || !ft_strncmp("EA", args[0], 3))
		add_path_to_texture(args, ch, textures);
	else if (!ft_strncmp("F", args[0], 2) || !ft_strncmp("C", args[0], 2))
		add_color_of_floor_and_ceiling(args, ch, textures);
	else
		exit_error("Wrong texture identifier", 11);
	ch->amount++;
	free_double_array(args);
}

void	parse_textures(char **argv, t_world  *world)
{
	t_textures	*textures;
	t_check		ch;

	init_check_struct(&ch);
	textures = malloc(sizeof(t_textures));
	if (!textures)
		exit_error("Malloc error", 21);
	ch.fd = open(argv[1], O_RDONLY);
	if (ch.fd == -1)
		exit_error("Couldn't open thefile", 22);
	while (get_next_line(ch.fd, &ch.line) && ch.amount < 6)
	{
		ch.trimmed = ft_strtrim(ch.line, " \t\v\f\r");
		free(ch.line);
		if (ch.trimmed && *(ch.trimmed))
			add_texture_to_struct(textures, &ch);
		else if (ch.trimmed)
			free(ch.trimmed);
	}
	if (ch.amount < 6)
		exit_error("Not enough data", 23);
	skip_empty_lines(&ch);
	parse_map(&ch, world);
	world->textures = textures;
	close(ch.fd);
}
