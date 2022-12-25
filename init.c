/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:57:34 by oufisaou          #+#    #+#             */
/*   Updated: 2022/12/25 12:10:35 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


void init(t_all *cub)
{
    cub->mlx = NULL;
    cub->mlx_win = NULL;
    cub->img = NULL;
    cub->addr = NULL;
    cub->bits_per_pixel = 0;
    cub->line_length = 0;
    cub->endian = 0;
    cub->player.x = 0;
    cub->player.y = 0;
    cub->player.ang = M_PI;
    cub->player.speed = 4;
    cub->player.rotation_speed = 3 * (M_PI / 180); //3 degree per frame it is in radian
    cub->player.turn_direction = 0; // -1 OR 1
    cub->player.walk_direction = 0;
    cub->var_d.x1 = 0; 
    cub->var_d.y1 = 0;
    cub->var_d.xx1 = 0;
    cub->var_d.yy1 = 0;
    cub->var_d.xinc = 0;
    cub->var_d.yinc = 0;
    cub->var_d.steps = 0;
    cub->var_d.dx = 0;
    cub->var_d.dy = 0;
    cub->player.view = FEILD;
    cub->map_i = 0;
    cub->map_j = 0;
    cub->map_x = 0;
    cub->map_y = 0;
    cub->black = 0x00000000;
    cub->yellow = 0x00FFFF00;
    cub->red = 0x00FF3333;
    cub->purple = 0x009966FF;
}

void set_direction(t_all *cub)
{
    int i = 0;
    int j = 0;

	while(i < cub->map_h / CUBE) // i will itterate on 7 height
    {
        j = 0;
        while(j < cub->map_w / CUBE) // j will itterate on 10 width
        {
            if (cub->walls[i][j] == 'N')
                cub->player.ang = (3 * M_PI) / 2; 
            else if(cub->walls[i][j] == 'S')
                cub->player.ang = M_PI / 2;
            else if(cub->walls[i][j] == 'E')
                cub->player.ang = M_PI;
            else if(cub->walls[i][j] == 'W')
                cub->player.ang = 0;
            j++;
        }
        i++;
    }
}

void launch_mlx(t_all *cub)
{
    cub->mlx = mlx_init();
    if (cub->mlx == NULL)
		ft_error("mlx_init failed\n");
	cub->mlx_win = mlx_new_window(cub->mlx, 1920, 1080, "Cub3D");
    if (cub->mlx_win == NULL)
		ft_error("mlx_new_window failed\n");
	cub->img = mlx_new_image(cub->mlx, cub->map_w, cub->map_h);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel, &cub->line_length,
								&cub->endian);
    draw_minimap(cub);
    put_player(cub);
    big_circle(cub);
    set_direction(cub);
    make_rays(cub);
    dda(cub);
    mlx_hook(cub->mlx_win, 2, 1L<<0 , mouvements, cub);
    mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img, 0, 0);
    mlx_hook(cub->mlx_win, 17, 0, exit_program, cub);
	mlx_loop(cub->mlx);
}


void	ft_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
