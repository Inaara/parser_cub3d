/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:32:26 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/13 17:32:58 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	print_double_array(t_map *m)
{
	char	**map;

	map = m->map;
	while (*map)
	{
		printf("%s\n", *map);
		map++;
	}
}

char	*ft_spaces_str(int width, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (width - len + 1));
	while (i < width - len)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}
