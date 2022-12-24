/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:39:22 by oufisaou          #+#    #+#             */
/*   Updated: 2022/12/24 16:31:39 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
/*
    this function calclates the position of the end of the ray,
*/
void dda(t_all *cub)
{
    //why pi / 2 looks down : becaue they go in the way of the horloge in game development
    //ihdatiyat dial no9ta
    cub->var_d.x1 = cub->player.x + (cos(cub->player.ang) * VIEW);
    cub->var_d.y1 = cub->player.y + (sin(cub->player.ang) * VIEW);

    cub->var_d.xx1  = cub->player.x;
    cub->var_d.yy1 = cub->player.y;

    if(fabs(cub->var_d.x1 - cub->player.x) > fabs(cub->var_d.y1 -  cub->player.y))
        cub->var_d.steps = fabs(cub->var_d.x1 - cub->player.x);
    else
        cub->var_d.steps = fabs(cub->var_d.y1 - cub->player.y);

    cub->var_d.xinc = (cub->var_d.x1 - cub->player.x) / cub->var_d.steps;
    cub->var_d.yinc = (cub->var_d.y1 - cub->player.y) / cub->var_d.steps;

    for(double i = 0; i < cub->var_d.steps; i++)
    {
            my_mlx_pixel_put2(cub, cub->var_d.xx1 , cub->var_d.yy1, 0x0000CC00);
            cub->var_d.xx1 = cub->var_d.xx1 + cub->var_d.xinc;
            cub->var_d.yy1 = cub->var_d.yy1 + cub->var_d.yinc;

    }
    
}

void dda2(t_all *cub)
{
    //why pi / 2 looks down : becaue they go in the way of the horloge in game development
    //ihdatiyat dial no9ta
    cub->var_d.x1 = cub->player.x + (cos(cub->player.ang) * VIEW);
    cub->var_d.y1 = cub->player.y + (sin(cub->player.ang) * VIEW);

    cub->var_d.xx1  = cub->player.x;
    cub->var_d.yy1 = cub->player.y;

    if(fabs(cub->var_d.x1 - cub->player.x) > fabs(cub->var_d.y1 -  cub->player.y))
        cub->var_d.steps = fabs(cub->var_d.x1 - cub->player.x);
    else
        cub->var_d.steps = fabs(cub->var_d.y1 - cub->player.y);

    cub->var_d.xinc = (cub->var_d.x1 - cub->player.x) / cub->var_d.steps;
    cub->var_d.yinc = (cub->var_d.y1 - cub->player.y) / cub->var_d.steps;

    for(double i = 0; i < cub->var_d.steps; i++)
    {
            my_mlx_pixel_put2(cub, cub->var_d.xx1 , cub->var_d.yy1, 0x0000CC00);
            cub->var_d.xx1 = cub->var_d.xx1 + cub->var_d.xinc;
            cub->var_d.yy1 = cub->var_d.yy1 + cub->var_d.yinc;

    }
    
}



// void make_raysI(t_all *cub)
// {
//     int i = 0;
    
//     while(i < NUM_RAYS)
//     {
        
//     }
// }