/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:39:22 by oufisaou          #+#    #+#             */
/*   Updated: 2022/12/28 11:40:07 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
/*
    this function calclates the position of the end of the ray,
    This is the function for the red line
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
            my_mlx_pixel_put2(cub, cub->var_d.xx1 , cub->var_d.yy1, 0x00FF0000);
            cub->var_d.xx1 = cub->var_d.xx1 + cub->var_d.xinc;
            cub->var_d.yy1 = cub->var_d.yy1 + cub->var_d.yinc;
    }
}
/*
    this fuction draw a ray in finction of the parameters:
    @var_d.xinc : the x increment value
    @
*/

void dda2(t_all *cub)
{
    //why pi / 2 looks down : becaue they go in the way of the horloge in game development
    //ihdatiyat dial no9ta
    cub->var_d.xinc = (cub->var_d.dx) / cub->var_d.steps;
    cub->var_d.yinc = (cub->var_d.dy) / cub->var_d.steps;

    for(double i = 0; i < cub->var_d.steps; i++)
    {
            my_mlx_pixel_put2(cub, cub->var_d.xx1 , cub->var_d.yy1, 0x0000CC00);
            cub->var_d.xx1 = cub->var_d.xx1 + cub->var_d.xinc;
            cub->var_d.yy1 = cub->var_d.yy1 + cub->var_d.yinc;
    }
}


/*
    This function  Takes the player angle and takes 30 degree from it and start creating each 
    ray by increasing the angle with a 60 / NUM RAY
*/
void make_rays(t_all *cub)
{
    int i = 0;
    
    cub->var_d.new_angle = cub->player.ang - (FEILD / 2);
    while(i < NUM_RAYS)
    {   
        fix_angle(cub);
        //Find the y and x horizental intersept
        what_direction(cub);
        cub->var_d.yinter = round(cub->player.y / CUBE) * CUBE;
        // is_down(cub);
        cub->var_d.xinter = cub->player.x + ((cub->player.y - cub->var_d.yinter) / tan(cub->var_d.new_angle));
        //get the xsteps adn the ysteps
        cub->var_d.ysteps = CUBE;
        // is_up(cub);
        cub->var_d.xsteps = cub->var_d.ysteps / tan(cub->var_d.new_angle);
        // is_left(cub);
        printf("is up : %d %f\n", cub->var_d.is_up, cub->player.ang);
        printf("is down : %d %f\n", cub->var_d.is_down, cub->player.ang);
        printf("is LEFT : %d %f\n", cub->var_d.is_left, cub->player.ang);
        printf("is RIGHT : %d %f\n", cub->var_d.is_right, cub->player.ang);
        
        cub->var_d.x1 = cub->player.x + (cos(cub->var_d.new_angle) * VIEW);
        cub->var_d.y1 = cub->player.y + (sin(cub->var_d.new_angle) * VIEW);

        cub->var_d.xx1 = cub->player.x;
        cub->var_d.yy1 =  cub->player.y;

        cub->var_d.dx = cub->var_d.x1 - cub->var_d.xx1;
        cub->var_d.dy = cub->var_d.y1 - cub->var_d.yy1;

        if(fabs(cub->var_d.dx) > fabs(cub->var_d.dy))
            cub->var_d.steps = fabs(cub->var_d.dx);
        else
            cub->var_d.steps = fabs(cub->var_d.dy);
        
        dda2(cub);
        cub->var_d.new_angle += (FEILD / NUM_RAYS); 
        i++;
    }
}


//direction of the ray
//probably wroong

void what_direction(t_all *cub)
{
    if(cub->var_d.new_angle > 0 && cub->var_d.new_angle < M_PI)
    {
        cub->var_d.is_up = 0;
        cub->var_d.is_down = 1;
    }
    else if (cub->var_d.new_angle < 0 && cub->var_d.new_angle > M_PI)
    {
        cub->var_d.is_down = 0;
        cub->var_d.is_up = 1;
    }
    else if ((cub->var_d.new_angle < M_PI * 0.5) || (cub->var_d.new_angle > 1.5 * M_PI))
    {
        cub->var_d.is_left = 0;
        cub->var_d.is_right = 1;
    }
    else if((cub->var_d.new_angle >  M_PI * 0.5) || (cub->var_d.new_angle <  1.5 * M_PI))
    {
        cub->var_d.is_right = 0;
        cub->var_d.is_left = 1;
    }
    else
    {
        cub->var_d.is_down *= 1;
        cub->var_d.is_right *= 1;
        cub->var_d.is_left *= 1;
        cub->var_d.is_up *= 1;
    }
}

void fix_angle(t_all *cub)
{
    if (cub->var_d.new_angle > 2 * M_PI)
        cub->var_d.new_angle -= 2 * M_PI;
    else if (cub->var_d.new_angle < 0)
        cub->var_d.new_angle += 2 * M_PI;
}

void is_down(t_all *cub)
{
    if(cub->var_d.is_down == 1)
        cub->var_d.yinter += CUBE;
    else
        cub->var_d.yinter += 0;
}

void is_up(t_all *cub)
{
    if(cub->var_d.is_up == 1)
        cub->var_d.ysteps *= -1;
    else
        cub->var_d.ysteps *= 1;
}

void is_left(t_all *cub)
{
    if(cub->var_d.is_left == 1 && cub->var_d.xsteps > 0)
        cub->var_d.xsteps *= -1;
    else if(cub->var_d.is_right == 1 && cub->var_d.xsteps < 0)
        cub->var_d.xsteps *= -1;
    else
        cub->var_d.xsteps *= 1;
}