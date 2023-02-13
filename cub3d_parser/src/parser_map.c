/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:40:34 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/13 17:52:31 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*static void	make_double_array_map_2(t_world *world, t_list *head, int i)
{
	world->map[++i] = NULL;
	m->height = all->height;
	m->width = all->width;
	all->m = m;
	free_chained_list(head);
}*/

void	check_if_map_has_player(t_world *all)
{
	if (all->checker->e == 0 && all->checker->w == 0
		&& all->checker->s == 0 && all->checker->n == 0)
		exit_error("Where is no player on the map", 12);
}

void	make_double_array_map(t_world *world, t_list *lst, int height, int width)
{
	t_list	*head;
//	t_map	*m;
	char	*temp;
	int	i;

	i = -1;
	temp = NULL;
//	all->i = -1;
//	m = malloc(sizeof(t_map));
	world->map = malloc(sizeof(char *) * (height + 1));
	head = lst;
	while (lst)
	{
		if ((int)ft_strlen(lst->content) < width)
		{
			temp = ft_spaces_str(width, ft_strlen(lst->content));
			world->map[++i] = ft_strjoin(lst->content, temp);
			free(temp);
		}
		else
			world->map[++i] = ft_strdup(lst->content);
		free(lst->content);
		lst = lst->next;
	}
	world->map[++i] = NULL;
	free_chained_list(head);
//	make_double_array_map_2(world, head, i);
}

void	continue_parsing(t_world *world, t_list *lst)
{
	make_double_array_map(world, lst, world->height, world->width);
//	init_player_checker_struct(world);
	check_map_correctness(world);
	check_if_map_has_player(world);
}

void	parse_map(t_check *ch, t_world *world)
{
	t_list	*lst;
	int	temp;

	temp = 0;
	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(ch->line));
	world->width = ft_strlen(ch->line);
	world->height = 1;
	while (get_next_line(ch->fd, &ch->line))
	{
		ft_lstadd_back(&lst, ft_lstnew(ch->line));
		temp = ft_strlen(ch->line);
		if (temp > world->width)
			world->width = temp;
		world->height++;
	}
	if (world->height != 1)
	{
		ch->trimmed = ft_strtrim(ch->line, " \t\n");
		if (*(ch->trimmed))
		{
			ft_lstadd_back(&lst, ft_lstnew(ch->line));
			world->height++;
		}
		free(ch->trimmed);
	}
	continue_parsing(world, lst);
}
