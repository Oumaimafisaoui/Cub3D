/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:49:34 by oufisaou          #+#    #+#             */
/*   Updated: 2022/12/24 13:30:32 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int check_walls1(t_all *cub, int flag)
{
    int	x;
	int	y;
    double angle;

    angle = 0;
    if(flag == 1)
    {
       angle = cub->player.ang - (90 * (M_PI / 180));
       x = (cub->player.x - (cos(angle) * cub->player.speed)) / CUBE;
       y = (cub->player.y - (sin(angle) * cub->player.speed)) / CUBE;

       if(cub->walls[y][x] == '1' || (cub->walls[y][(int)cub->player.x / CUBE] == '1' && cub->walls[(int)cub->player.y / CUBE][x] == '1')) //ta9ato3
            return (1);
       else
            return (0);
    }
    else if(flag == 0)
    {
        angle = cub->player.ang - (90 * (M_PI / 180));
        x = (cub->player.x + (cos(angle) * cub->player.speed)) / CUBE;
        y =  (cub->player.y + (sin(angle) * cub->player.speed)) / CUBE;
        
        if(cub->walls[y][x] == '1' || (cub->walls[y][(int)cub->player.x / CUBE] == '1' && cub->walls[(int)cub->player.y / CUBE][x] == '1'))
                return (1);
        else
                return (0);
    }
    return (1);
}


int check_walls2(t_all *cub, int flag)
{
    int	x;
	int	y;
    
    int speed;
    speed = cub->player.speed * -1;
    if(flag == 1)
    {
       x = (cub->player.x + (cos(cub->player.ang) * cub->player.speed)) / CUBE;
       y = (cub->player.y + (sin(cub->player.ang) * cub->player.speed)) / CUBE;
       if(cub->walls[y][x] == '1' || (cub->walls[y][(int)cub->player.x / CUBE] == '1' && cub->walls[(int)cub->player.y / CUBE][x] == '1')) //ta9ato3
            return (1);
       else
            return (0);
    }
     
    else if(flag == 0)
    {
        x = (cub->player.x + (cos(cub->player.ang) * speed)) / CUBE;
        y =  (cub->player.y + (sin(cub->player.ang) * speed)) / CUBE;

        if(cub->walls[y][x] == '1' || (cub->walls[y][(int)cub->player.x / CUBE] == '1' && cub->walls[(int)cub->player.y / CUBE][x] == '1'))
                return (1);
        else
                return (0);
    }
    return (1);
}