/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:15:24 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/13 16:32:48 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/cub3D.h"

void	exit_error(char *str, int num)
{
	printf("Error:\n     %s", str);
	exit(num);
}

int	main(int argc, char **argv)
{
	t_world	world;
	int	len;

	if (argc != 2)
		exit_error("Wrong amount of arguments", 1);
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(".cub", argv[1] + len - 4, 5))
		exit_error("Wrong format of map", 2);
	parse_textures(argv, &world);
//	executing(&all);
}
