/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:59:47 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/13 17:55:11 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	ft_atoi_color(const char *str)
{
	int	num;

	num = 0;
	if (!*str || (*str < '1' && *str > '9'))
		return (-1);
	if (*str == '0')
	{
		if (str[1] && str[1] >= '0' && str[1] <= '9')
			return (-1);
		return (0);
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
		if (num > 255)
			return (-1);
	}
	return (num);
}

char	*add_color_to_struct(char *str, t_color *col, int index)
{
	int	num;

	if (!str)
		exit_error("Wrong color data", 17);
	num = ft_atoi_color(str);
	if (num == -1)
		exit_error("RGB data of color is wrong", 18);
	else
	{
		if (index == 0)
			col->r = num;
		else if (index == 1)
			col->g = num;
		else
			col->b = num;
		while (*str && *str >= '0' && *str <= '9')
			str++;
	}
	return (str);
}

void	check_correctness_of_color(char *str, t_color *col)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		str = add_color_to_struct(str, col, i);
		if (i < 2 && *str && *str == ',')
			str++;
		else if ((i < 2 && *str != ',') || (i == 2 && *str))
			exit_error("Wrong format of color data", 19);
		++i;
	}
}

void	add_color_of_floor_and_ceiling(char **args, t_check *ch, t_textures *textures)
{
	t_color	col;

	check_correctness_of_color(args[1], &col);
	if (!ft_strncmp("F", args[0], 2) && !ch->floor)
	{
		textures->floor.r = col.r;
		textures->floor.g = col.g;
		textures->floor.b = col.b;
		ch->floor++;
	}
	else if (!ft_strncmp("C", args[0], 2) && !ch->ceiling)
	{
		textures->ceiling.r = col.r;
		textures->ceiling.g = col.g;
		textures->ceiling.b = col.b;
		ch->ceiling++;
	}
	else
		exit_error("Identifiers repetitive", 20);
}
