/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:39:22 by oufisaou          #+#    #+#             */
/*   Updated: 2023/01/15 16:42:26 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

/*
    this function calclates the position of the end of the ray,
    This is the function for the red line
*/

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

void normalize_player(t_all *cub)
{
    if (cub->player.ang > 2 * M_PI) //to reset  to 0
        cub->player.ang -= 2 * M_PI;
    if (cub->player.ang  < 0)
        cub->player.ang += 2 * M_PI;
}

void normalize_rayangle(t_all *cub)
{
    if (cub->var_d.new_angle > 2 * M_PI) //to reset  to 0
        cub->var_d.new_angle -= 2 * M_PI;
    if (cub->var_d.new_angle  < 0)
        cub->var_d.new_angle += 2 * M_PI;
}

/*
    This function  Takes the player angle and takes 30 degree from it and start creating each 
    ray by increasing the angle with a 60 / NUM RAY
*/
void make_rays(t_all *cub)
{
    int  j;

    j = -1;
    normalize_player(cub);
    cub->var_d.new_angle = cub->player.ang - (FEILD / 2);
    while(++j < NUM_RAYS)
    {
        horizontal_inter(cub); 
        vertical_inter(cub);
        decide_casting(cub);
        cub->var_d.new_angle += (FEILD / (double) NUM_RAYS);
        normalize_rayangle(cub);
        reset_directions(cub);
    }
}

void reset_directions(t_all *cub)
{
    cub->var_d.is_down = 0;
    cub->var_d.is_right = 0;
    cub->var_d.is_up = 0;
    cub->var_d.is_left = 0;
}

void decide_casting(t_all *cub)
{
        double d1 = 0;
        double d2 = 0;

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
        
}

void horizontal_inter(t_all *cub)
{
    normalize_rayangle(cub);
    normalize_player(cub);
    fix_angle(cub);
    what_direction(cub);
    cub->var_d.yinter = floor(cub->player.y / CUBE) * CUBE;
    is_down(cub);
    cub->var_d.xinter = cub->player.x + (( cub->var_d.yinter - cub->player.y) / tan(cub->var_d.new_angle));
    cub->var_d.ysteps = CUBE;
    is_up(cub);
    cub->var_d.xsteps = CUBE / tan(cub->var_d.new_angle);
    is_left(cub);
    cub->var_d.next_x_inter = cub->var_d.xinter;
    cub->var_d.next_y_inter = cub->var_d.yinter;
    if(cub->var_d.is_up == 1)
        cub->var_d.next_y_inter -= 1;
    while(cub->var_d.next_x_inter >= 0 && cub->var_d.next_x_inter <= cub->map_w \
    && cub->var_d.next_y_inter >= 0 && cub->var_d.next_y_inter <= cub->map_h)
    {
        if(cub->walls[cub->var_d.next_y_inter / CUBE][cub->var_d.next_x_inter / CUBE] == '1')
        {
            cub->var_d.h_found_wall = 1;
            cub->var_d.wallhitx = cub->var_d.next_x_inter;
            cub->var_d.wallhity = cub->var_d.next_y_inter;
            break ;
        }
        else
        {
            cub->var_d.next_x_inter += cub->var_d.xsteps;
            cub->var_d.next_y_inter += cub->var_d.ysteps;
        }
    }
    
}


void vertical_inter(t_all *cub)
{
    cub->var_d.xinter1 = floor(cub->player.x / CUBE) * CUBE;
    is_right(cub);
    cub->var_d.yinter1 = cub->player.y + ((cub->var_d.xinter1 - cub->player.x) * tan(cub->var_d.new_angle));
    cub->var_d.xsteps1 = CUBE;
    is_left2(cub);
    cub->var_d.ysteps1 = CUBE * tan(cub->var_d.new_angle);
    is_up2(cub);
    
    cub->var_d.next_x_inter1= cub->var_d.xinter1;
    cub->var_d.next_y_inter1 = cub->var_d.yinter1;

    if(cub->var_d.is_left == 1)
       cub->var_d.next_x_inter1 -= 1;
    
    while(cub->var_d.next_x_inter1  >= 0 &&cub->var_d.next_x_inter1  < cub->map_w \
    && cub->var_d.next_y_inter1 >= 0 && cub->var_d.next_y_inter1 < cub->map_h)
    {
        if(cub->walls[cub->var_d.next_y_inter1  / CUBE][cub->var_d.next_x_inter1 / CUBE] == '1')
        {
            cub->var_d.v_found_wall = 1;
            cub->var_d.wallhitx1 = cub->var_d.next_x_inter1;
            cub->var_d.wallhity1 = cub->var_d.next_y_inter1;
            break ;
        }
        else
        {
            cub->var_d.next_x_inter1 += cub->var_d.xsteps1;
            cub->var_d.next_y_inter1  += cub->var_d.ysteps1;
        }
    }
}