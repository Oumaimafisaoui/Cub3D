/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:39:22 by oufisaou          #+#    #+#             */
/*   Updated: 2023/01/15 15:50:37 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

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
    int  j = -1;

    int xnext = 0;
    int ynext = 0;

    int xnext1 = 0;
    int ynext1 = 0;

    double d1 = 0;
    double d2 = 0;

    if (cub->player.ang > 2 * M_PI) //to reset  to 0
        cub->player.ang -= 2 * M_PI;
    if (cub->player.ang  < 0)
        cub->player.ang += 2 * M_PI;

    cub->var_d.new_angle = cub->player.ang - (FEILD / 2);

    while(++j < NUM_RAYS)
    {
        if (cub->var_d.new_angle > 2 * M_PI) //to reset  to 0
        cub->var_d.new_angle -= 2 * M_PI;
        if (cub->var_d.new_angle  < 0)
            cub->var_d.new_angle += 2 * M_PI;

        
        if (cub->player.ang > 2 * M_PI) //to reset  to 0
            cub->player.ang -= 2 * M_PI;
        if (cub->player.ang  < 0)
            cub->player.ang += 2 * M_PI;
        fix_angle(cub);
        what_direction(cub);
        if (cub->var_d.is_down)
            printf("down\t");
        else
            printf("up\t");
        if (cub->var_d.is_left)
            printf("left\n");
        else
            printf("right\n");
        cub->var_d.yinter = floor(cub->player.y / CUBE) * CUBE;
        is_down(cub);
        cub->var_d.xinter = cub->player.x + (( cub->var_d.yinter - cub->player.y) / tan(cub->var_d.new_angle));
        cub->var_d.ysteps = CUBE;
        is_up(cub);

        cub->var_d.xsteps = CUBE / tan(cub->var_d.new_angle);
        is_left(cub);
        
        xnext = cub->var_d.xinter;
        ynext = cub->var_d.yinter;

        if(cub->var_d.is_up == 1)
            ynext -= 1;
    
        while(xnext >= 0 && xnext <= cub->map_w && ynext >= 0 && ynext <= cub->map_h)
        {
            if(cub->walls[ynext / CUBE][xnext / CUBE] == '1')
            {
                cub->var_d.h_found_wall = 1;
                cub->var_d.wallhitx = xnext;
                cub->var_d.wallhity = ynext;
                
                break ;
            }
            else
            {
                xnext += cub->var_d.xsteps;
                ynext += cub->var_d.ysteps;
            }
        }
        // what_direction(cub);
        cub->var_d.xinter1 = floor(cub->player.x / CUBE) * CUBE;
        is_right(cub);

        cub->var_d.yinter1 = cub->player.y + ((cub->var_d.xinter1 - cub->player.x) * tan(cub->var_d.new_angle));
       
        cub->var_d.xsteps1 = CUBE;
        is_left2(cub);

        cub->var_d.ysteps1 = CUBE * tan(cub->var_d.new_angle);
        is_up2(cub);
        
        xnext1 = cub->var_d.xinter1;
        ynext1 = cub->var_d.yinter1;

        if(cub->var_d.is_left == 1)
            xnext1 -= 1;

        while(xnext1 >= 0 && xnext1 < cub->map_w && ynext1 >= 0 && ynext1 < cub->map_h)
        {
            if(cub->walls[ynext1 / CUBE][xnext1 / CUBE] == '1')
            {
                cub->var_d.v_found_wall = 1;
                cub->var_d.wallhitx1 = xnext1;
                cub->var_d.wallhity1 = ynext1;
                
                break ;
            }
            else
            {
                xnext1 += cub->var_d.xsteps1;
                ynext1 += cub->var_d.ysteps1;
            }
        }

        d1 = sqrt(pow(cub->var_d.wallhitx - cub->player.x, 2) + pow(cub->var_d.wallhity - cub->player.y, 2));
        d2 = sqrt(pow(cub->var_d.wallhitx1 - cub->player.x, 2) + pow(cub->var_d.wallhity1 - cub->player.y, 2));

        if(d1 < d2)
        {
            cub->var_d.x1 = cub->var_d.wallhitx;
            cub->var_d.y1 = cub->var_d.wallhity;
        
        }
        else
        {
            cub->var_d.x1 = cub->var_d.wallhitx1;
            cub->var_d.y1 = cub->var_d.wallhity1;
        }
        
        cub->var_d.xx1 = cub->player.x;
        cub->var_d.yy1 =  cub->player.y;

        cub->var_d.dx = cub->var_d.x1 - cub->var_d.xx1;
        cub->var_d.dy = cub->var_d.y1 - cub->var_d.yy1;

        if(fabs(cub->var_d.dx) > fabs(cub->var_d.dy))
            cub->var_d.steps = fabs(cub->var_d.dx);
        else
            cub->var_d.steps = fabs(cub->var_d.dy);
        
        dda2(cub);
        cub->var_d.new_angle += (FEILD / (double) NUM_RAYS);
         if (cub->var_d.new_angle > 2 * M_PI) //to reset  to 0
        cub->var_d.new_angle -= 2 * M_PI;
        if (cub->var_d.new_angle  < 0)
            cub->var_d.new_angle += 2 * M_PI;



    if (cub->player.ang > 2 * M_PI) //to reset  to 0
        cub->player.ang -= 2 * M_PI;
    if (cub->player.ang  < 0)
        cub->player.ang += 2 * M_PI;
        cub->var_d.is_down = 0;
        cub->var_d.is_right = 0;
        cub->var_d.is_up = 0;
        cub->var_d.is_left = 0;

    }
    // exit(1);
}

