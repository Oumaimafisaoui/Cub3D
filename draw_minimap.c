/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:58:11 by oufisaou          #+#    #+#             */
/*   Updated: 2022/12/24 16:39:26 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

void	my_mlx_pixel_put(t_all *cub, int x, int y, int color)
{
	char	*dst;
    
	dst = cub->addr + (y * cub->line_length + x * (cub->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(t_all *cub, int x, int y, int color)
{
	char	*dst;
    
    if((x >= 0 && x < cub->map_w) && (y >= 0 && y < cub->map_h))
    {
        dst = cub->addr + (y * cub->line_length + x * (cub->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

void draw_minimap(t_all *cub)
{
	int i = 0;
    int j = 0;

    int y = 0;
    int x = 0;
	while(i < cub->map_h / CUBE) // i will itterate on 7 height
    {
        j = 0;
        while(j < cub->map_w / CUBE) // j will itterate on 10 width
        {
           
            y = i * CUBE; // y will be the height of the square
            if (cub->walls[i][j] == '1')
            {
                while(y < (i * CUBE) + CUBE) //while the height is less than the end of the square
                {
                     x = j * CUBE;
                     while (x < (j * CUBE) + CUBE)
                     {
                        if (y % CUBE == 0 || x % CUBE == 0) //put black line
                            my_mlx_pixel_put(cub, x, y, 0x00000000);
                        else
                            my_mlx_pixel_put(cub, x, y, 0x00FFFF00);
                        x++;
                     }
                     y++;
                }
            }
            else if(cub->walls[i][j] == '0')
            {
                while(y < (i * CUBE) + CUBE) 
                {
                     x = j * CUBE;
                     while (x < (j * CUBE) + CUBE)
                     {
                        if (y % CUBE == 0 || x % CUBE == 0)
                            my_mlx_pixel_put(cub, x, y, 0x00000000);
                        else
                            my_mlx_pixel_put(cub, x, y,0x009966FF);
                        x++;
                     }
                     y++;
                }
            }
            else
            {
                while(y < (i * CUBE) + CUBE) 
                {
                     x = j * CUBE;
                     while (x < (j * CUBE) + CUBE)
                     {
                        if (y % CUBE == 0 || x % CUBE == 0)
                            my_mlx_pixel_put(cub, x, y, 0x00000000);
                        else
                            my_mlx_pixel_put(cub, x, y,0x00FF3333);
                        x++;
                     }
                     y++;
                }
            }
            j++;
        }
        i++;
    }
    
}

void put_player(t_all *cub)
{
    int i = 0;
    int j = 0;

    while(i < cub->map_h / CUBE)
    {
        j = 0;
        while(j < cub->map_w / CUBE)
        {
            if (cub->walls[i][j] == 'N' || cub->walls[i][j] == 'S' || cub->walls[i][j] == 'W' || cub->walls[i][j] == 'E') //it can be other directions
            {
                    cub->player.y = (i * CUBE) + CUBE / 2;
                    cub->player.x = (j * CUBE) + CUBE / 2;
            }
            j++;
        }
        i++;
    } 
}

void big_circle(t_all *cub)
{
    double h;
    double angle;
    double xp;
    double yp;

    my_mlx_pixel_put(cub, cub->player.x, cub->player.y, 0x00FFFFFF);
    //x = cos(o) * h + xs
    //y = sin(o) * h + ys
    h = 1;
    while(h < 5) // this h increments
    {
        angle = 0;
        while(angle < 360)
        {
            xp = cos(angle) * h + cub->player.x;
            yp = sin(angle) * h + cub->player.y;
            my_mlx_pixel_put(cub, xp, yp, 0x00FFFFFF);
            angle++;
        }
        h++;
    }
}


