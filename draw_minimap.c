/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:58:11 by oufisaou          #+#    #+#             */
/*   Updated: 2022/12/25 13:22:19 by oufisaou         ###   ########.fr       */
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

/*
    This function uses
    @i : ittertate through themap height / CUBE dimension to have equal squares.
    @j : itterate through the map width / CUBE dimension to have equal squares.
    @y : the position of the y starting point of the square : 0 , 60 , 90, 120...
    @x:  the position of the x starting point of the square
    if (x, y) = '1'

    1 - itterate through : y = (i * CUBE) + CUBE
    2 - itterate through : x = (j * CUBE) + CUBE

    y = 0 => (x =0 ............. x = 60)

        x= 0    60    90
    y = 0---------------------------------------
           1|   1 |   1  |   1  |   1  |  1   |   1  |
    y = 60---------------------------------------
            1|   0 |   0  |  0   |   0  |   0  |   0  |
    y = 90---------------------------------------

    i = 0, j = 0
    Round one => (y=0 , (x= 0 .......... x = 60))
    (y = 0 => y < 60)
    (x = 0 = >  x < 60)
    the step is 60 and the pixel is one.
*/

void draw_grid(t_all *cub, int grid, int fill)
{
    cub->map_x = cub->map_j * CUBE;

        while (cub->map_x < (cub->map_j * CUBE) + CUBE)
        {
            if (cub->map_y % CUBE == 0 || cub->map_x % CUBE == 0) //put black line
                my_mlx_pixel_put(cub, cub->map_x, cub->map_y, grid);
            else
                my_mlx_pixel_put(cub, cub->map_x, cub->map_y, fill);
            cub->map_x++;
        }
        cub->map_y++;
    
}
void draw_minimap(t_all *cub)
{
    
	while(cub->map_i < cub->map_h / CUBE) // cub->map_i will itterate on 7 height
    {
        cub->map_j = 0;
        while(cub->map_j < cub->map_w / CUBE) // cub->map_j will itterate on 10 width
        {
            cub->map_y = cub->map_i * CUBE; 
            // cub->map_y will be the height of the square
            if (cub->walls[cub->map_i][cub->map_j] == '1')
            {
                while(cub->map_y < (cub->map_i * CUBE) + CUBE) //while the height is less than the end of the square  
                     draw_grid(cub, cub->black, cub->yellow);
            }
            else if(cub->walls[cub->map_i][cub->map_j] == '0')
            {
                while(cub->map_y < (cub->map_i * CUBE) + CUBE) 
                     draw_grid(cub, cub->black, cub->purple);
            }
            else
            {
                while(cub->map_y < (cub->map_i * CUBE) + CUBE) 
                     draw_grid(cub, cub->black, cub->red);
            }
            cub->map_j++;
        }
        cub->map_i++;
    }
    cub->map_i = 0;
    cub->map_j = 0;  //to prevent duplication
    cub->map_x = 0;
    cub->map_y = 0;
    return ;
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


