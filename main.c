/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:18:37 by oufisaou          #+#    #+#             */
/*   Updated: 2022/12/24 19:30:22 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main(int ac, char **av)
{
    t_all cub;
    t_map	map;
    
    if (ac != 2)
	{
		printf("Error Args !!!\n");
		exit(1); 
	}
	if (ft_check_file_map(av) == 1)
	{
		printf("\033[0;31mextention of map must finished -> .cub !!\n");
		exit(1);
	}
	ft_read_map(&map, av);
	map.map_height = ft_get_len_ofmap(map.map2d);
	map.map_width = get_len(map.map2d);
	retrun_map_2d(&map);
	if (ft_check_all_map(map.map2d) == 1 || ft_check_content(&map) == 1 || ft_check_horizontal(&map) == 1 || ft_check_vertical(&map) == 1)
	{
		printf("error walls\n");
		exit(EXIT_FAILURE);
	}
    cub.walls = map.map2d;
    cub.map_w = map.map_width * CUBE;
    cub.map_h = map.map_height * CUBE;
    init(&cub);
    launch_mlx(&cub);
} 