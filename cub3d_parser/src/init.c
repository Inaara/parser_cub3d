/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:51:25 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/13 16:51:54 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	init_check_struct(t_check	*ch)
{
	ch->amount = 0;
	ch->nt = 0;
	ch->st = 0;
	ch->wt = 0;
	ch->et = 0;
	ch->floor = 0;
	ch->ceiling = 0;
	ch->line = NULL;
	ch->trimmed = NULL;
	ch->fd = -1;
}
