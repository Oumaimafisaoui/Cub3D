/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:49:34 by oufisaou          #+#    #+#             */
/*   Updated: 2023/01/26 16:04:30 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/*
    This function checks if a wall is there to no go through it
*/
int find_wall(double x, double y, t_all *cub)
{
    if(x < cub->map_w && x >= 0 && y < cub->map_h && y >= 0)
    {
        if(cub->walls[(int)y / CUBE][(int)x / CUBE] == '1' || (cub->walls[(int)y / CUBE][(int)cub->player.x / CUBE] == '1' && cub->walls[(int)cub->player.y / CUBE][(int)x / CUBE] == '1')) //ta9ato3
            return (1);
        else
            return (0);
    }
    return (1);
  
}

int check_walls1(t_all *cub, int flag)
{
    double	x;
	double	y;
    double angle;

    angle = cub->player.ang + (90 * (M_PI / 180));
            if (angle > 2 * M_PI)
                angle -= (2 * M_PI);
            if (angle < 0)
                angle += (2 * M_PI);
    if(flag == 1)
    {
       x = (cub->player.x + (cos(angle) * cub->player.speed));
       y = (cub->player.y + (sin(angle) * cub->player.speed));
        return (find_wall(x, y ,cub));

    }
    else if(flag == 0)
    {
        x = (cub->player.x - (cos(angle) * cub->player.speed));
        y =  (cub->player.y - (sin(angle) * cub->player.speed));
        return (find_wall(x, y ,cub));
    }
    return (1);
}

/*
    This function checks if a wall is there to no go through it
*/

int check_walls2(t_all *cub, int flag)
{
    double	x;
	double	y;
    
    double speed;
    speed = cub->player.speed * -1;
    if(flag == 1)
    {
       x = (cub->player.x + (cos(cub->player.ang) * cub->player.speed));
       y = (cub->player.y + (sin(cub->player.ang) * cub->player.speed));
       return (find_wall(x, y ,cub));
    }
    else if(flag == 0)
    {
        x = (cub->player.x + (cos(cub->player.ang) * speed));
        y =  (cub->player.y + (sin(cub->player.ang) * speed));
        return (find_wall(x, y ,cub));
    }
    return (1);
}