/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:36:54 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/13 18:15:08 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"


void	check_if_map_has_player(t_world *all)
{
	if (all->checker->e == 0 && all->checker->w == 0
		&& all->checker->s == 0 && all->checker->n == 0)
		exit_error("Where is no player on the map", 12);
}

void	check_zeros_at_corners(t_world *all, int i, int j)
{
	if (i == 0 || i == all->height - 1 || j == 0 || j == all->width)
		exit_error("Zero is found in a corner. Wrong map", 13);
}

int	check_if_symbol_is_zero_or_player(t_world *all, char **map, int i, int j)
{
	return ((i >= 0 && i < all->height) && (j >= 0 && j < all->width)
		&& (map[i][j] == '0' || map[i][j] == 'N'
		|| map[i][j] == 'E' || map[i][j] == 'W'
		|| map[i][j] == 'S'));
}

int	check_if_symbol_is_zero(t_world *all, char **map, int i, int j)
{
	return ((i >= 0 && i < all->height)
		&& (j >= 0 && j < all->width) && map[i][j] == '0');
}

void	check_one_player(t_all *all, char **map, int i, int j)
{
	if (i == 0 || i == all->m->height)
		exit_error("Player in the wrong place", 14);
	if (map[i][j] == 'N' && all->checker->n == 0)
		all->checker->n++;
	else if (map[i][j] == 'E' && all->checker->e == 0)
		all->checker->e++;
	else if (map[i][j] == 'W' && all->checker->w == 0)
		all->checker->w++;
	else if (map[i][j] == 'S' && all->checker->s == 0)
		all->checker->s++;
	else
		exit_error("Something wrong with player", 15);
	if (all->checker->n + all->checker->e + all->checker->s
		+ all->checker->w > 1)
		exit_error("Something wrong with player", 15);
	if (!check_if_symbol_is_zero(all, map, i, j - 1)
		&& !check_if_symbol_is_zero(all, map, i, j + 1)
		&& !check_if_symbol_is_zero(all, map, i + 1, j)
		&& !check_if_symbol_is_zero(all, map, i - 1, j))
		exit_error("Player surrounded by walls. Wrong map", 16);
	add_player_to_struct(all, i, j, map[i][j]);
}


void	check_spaces(t_world *all, char **map, int i, int j)
{
	if (check_if_symbol_is_zero_or_player(all, map, i, j - 1)
		|| check_if_symbol_is_zero_or_player(all, map, i, j + 1)
		|| check_if_symbol_is_zero_or_player(all, map, i + 1, j)
		|| check_if_symbol_is_zero_or_player(all, map, i - 1, j)
		|| check_if_symbol_is_zero_or_player(all, map, i + 1, j + 1)
		|| check_if_symbol_is_zero_or_player(all, map, i - 1, j + 1)
		|| check_if_symbol_is_zero_or_player(all, map, i + 1, j - 1)
		|| check_if_symbol_is_zero_or_player(all, map, i - 1, j - 1))
		error_exit("Zero symbol found in wrong place", 3);
}

void	check_line_for_spaces(t_world *all, char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != ' ')
		{
			if (all->checker->space_line == 1)
				error_exit("Space line inside the map", 4);
			return ;
		}
		j++;
	}
	all->checker->space_line = 1;
}

void	check_map_correctness(t_world *all)
{
	char		**map;
	int			i;
	int			j;

	i = -1;
	map = all->map;
	while (map[i] && (++i < all->height))
	{
		j = -1;
		check_line_for_spaces(all, map, i);
		while (map[i][++j] && j < all->m->width)
		{
			if (map[i][j] == ' ')
				check_spaces(all, map, i, j);
			else if (map[i][j] == '0')
				check_zeros_at_corners(all, i, j);
			else if (map[i][j] == '1')
				;
			else if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				check_one_player(all, map, i, j);
			else
				error_exit("Invalid symbol in map", 5);
		}
	}
}
