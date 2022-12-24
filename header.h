/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:18:49 by oufisaou          #+#    #+#             */
/*   Updated: 2022/12/24 16:37:31 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include "parsing/cub3d.h"

#define CUBE  20
#define W_M 10
#define H_M 7
#define VIEW  300 //length of ray
#define FEILD 60 * (M_PI / 180) //convert in RAD
#define W_STRIP 1
#define NUM_RAYS (W_M * CUBE) / W_STRIP //

#define UP  126
#define DOWN 125
#define RIGHT 124
#define LEFT 123

// char walls[7][10] = {
//     {'1','1','1','1','1','1','1','1','1','1'}, 
//     {'1','0','0','0','0','0','0','0','0','1'}, 
//     {'1','0','0','0','0','N','0','0','0','1'}, 
//     {'1','0','0','0','0','0','0','0','0','1'}, 
//     {'1','0','0','0','0','0','0','0','0','1'}, 
//     {'1','0','0','0','0','0','0','0','0','1'}, 
//     {'1','1','1','1','1','1','1','1','1','1'},   
// };

typedef struct s_player
{
    double x;
    double y; 
    double ang;
    double speed;
    double turn_direction;
    double walk_direction;
    double rotation_speed;
    
}t_player;

typedef struct s_ddavar
{
    double x1;
    double y1;
    double xx1;
    double yy1;
    double xinc;
    double yinc;
    int steps;
    double  new_angle;

} t_ddavar;

typedef struct s_cub
{
    void *mlx;
    void *mlx_win;
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int map_w;
    int map_h;
    t_player player;
    char **walls;
    t_ddavar var_d;
} t_all;

//all walls should be removed and added to a struct

/* Cub3d */


void init(t_all *cub);
void	ft_error(char *str);
void launch_mlx(t_all *cub);
void draw_minimap(t_all *cub);
void	my_mlx_pixel_put(t_all *cub, int x, int y, int color);
void put_player(t_all *cub);
int	mouvements(int key, t_all *cub);
void dda(t_all *cub);
void set_direction(t_all *cub);
int	exit_program(t_all *cub);
void event_left_right(t_all *cub, int key);
int check_walls2(t_all *cub, int flag);
int check_walls1(t_all *cub, int flag);
void	my_mlx_pixel_put2(t_all *cub, int x, int y, int color);
void init2(t_all *cub);

/*Cub3d outils*/
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

void big_circle(t_all *cub);
#endif