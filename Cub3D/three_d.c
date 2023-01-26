/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:55:40 by oufisaou          #+#    #+#             */
/*   Updated: 2023/01/25 14:16:57 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void generate_3d(t_all *cub)
{
     int i;
     i = 0;
     while(i < cub->var_d.num_rays)
     {
          cub->three.d_player_pro = (WINDOW_W / 2) / tan(FEILD / 2);
          cub->three.ray_distance = cub->ray[i].distance * (cos(cub->ray[i].angle  - cub->player.ang));
          cub->three.wall_projection = (CUBE / cub->three.ray_distance) * cub->three.d_player_pro;

          int wall_height = (int)cub->three.wall_projection;
          int wall_top_pix = (WINDOW_H / 2) - (wall_height / 2);
          if(wall_top_pix < 0)
               wall_top_pix = 0;
          else
               wall_top_pix += 0;
          int wall_bott_pix = (WINDOW_H / 2) + (wall_height / 2);
           if(wall_bott_pix < 0)
               wall_bott_pix = 0;
          else
               wall_bott_pix += 0;
          
          for (int x = 0; x < wall_top_pix; x++)
          {
                my_mlx_pixel_put3(cub, i, x, cub->purple);
          }
          for(int j = wall_top_pix; j < wall_bott_pix; j++)
          {

               my_mlx_pixel_put3(cub, i, j, cub->yellow);
          }
          for(int y = wall_bott_pix; y < WINDOW_H; y++)
          {

               my_mlx_pixel_put3(cub, i, y, cub->black);
          }
          i++;
     }
}