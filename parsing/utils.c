/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:44:31 by skasmi            #+#    #+#             */
/*   Updated: 2023/01/15 11:50:21 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_check_content(t_map *map)
{
	int i;
	int j;
	int idx;
	i = 0;
	idx = 0;
	while (map->map2d[i])
	{
		j = 0;
		while (map->map2d[i][j])
		{
			if (ft_strchr("NSWE", map->map2d[i][j]))
				idx++;
			j++;
		}	
		i++;
	}
	if (idx > 1 || idx == 0)
		return (1);
	return (0);
}

int	ft_check_map_one(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(tab[i])
	{
		while (tab[j])
		{
			if (tab[i][j] != 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_file_map(char **map)
{
	int	i;

	i = 0;
	while (map[1][i])
		i++;
	if (map[1][i - 1] == 'b' && map[1][i - 2] == 'u'
		&& map[1][i - 3] == 'c' && map[1][i - 4] == '.')
		return (0);
	else
		return (1); 
	
}

void	ft_read_map(t_map *t, char **av)
{	
	int i;
	int j;

	j = 0;
	i = 0;
	t->fd = open(av[1], O_RDONLY);
	if (t->fd < 0)
	{
		ft_putstr_fd("\033[0;31mfile not found !!\n", 2);
		exit(1);		
	}
	t->tab = get_next_line(t->fd);
	while (t->tab)
	{
		free(t->tab);
		t->tab = get_next_line(t->fd);
		i++;
	}
	t->map2d = (char **)malloc((i + 1) * sizeof(char *));
	if (!t->map2d)
		return ;
	j = 0;
	close(t->fd);
	t->fd = open(av[1], O_RDONLY);
	t->map2d[j] = get_next_line(t->fd);
	while (j < i)
	{
		j++;
		t->map2d[j] = get_next_line(t->fd);
	}
	t->map2d[j] = NULL;
}


void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	if (!s)
		return ;
	while (s[index])
	{
		ft_putchar_fd(s[index], fd);
		index++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}