/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:13:47 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/22 12:55:17 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_gun(t_glob *glob, int index)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	// if (glob->txtrs.gun_txtr[gun])
		// mlx_delete_texture(glob->txtrs.gun_txtr);
	// glob->txtrs.gun_txtr = mlx_load_png(path);
	// if (!glob->txtrs.gun_txtr)
		// error_log("faild to load gun image");
	while (i < HEIGHT && i < (int)glob->txtrs.gun_txtr[index]->height)
	{
		j = 0;
		while (j < WIDTH && j < (int)glob->txtrs.gun_txtr[index]->width)
		{
			color = get_color_from_textrs(j, i, glob->txtrs.gun_txtr[index]);
			if (color != 0)
				mlx_put_pixel(glob->gun_img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_glob *glob)
{
	if (glob->redraw)
	{
		draw_sky(glob);
		draw_floor(glob);
		cast_all_rays(glob);
		draw_minimap(glob);
		put_player(glob);
		end_point(glob, 30, glob->vue_angle);
		draw_line(glob, glob->end_x, glob->end_y, 0xFF000000);
		glob->redraw = 0;
	}
	// put_gun(glob, "textures/pics/gun01.png");
	// mlx_image_to_window(glob->mlx, glob->image, 0, 0);
	// mlx_image_t *img = mlx_new_image(glob->mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(glob->mlx, img, 0, 0);
}

void	init_player_pos(t_glob *glob, char *vue)
{
	int	i;
	int	j;

	i = 0;
	while (glob->map[i])
	{
		j = 0;
		while (glob->map[i][j])
		{
			if (glob->map[i][j] == 'E' || glob->map[i][j] == 'N' || \
			glob->map[i][j] == 'S' || glob->map[i][j] == 'W')
			{
				(*vue) = glob->map[i][j];
				glob->start_x = j;
				glob->start_y = i;
			}
			j++;
		}
		i++;
	}
}

void	init_gun_textrs(t_glob *glob)
{
	int	i;

	i = 0;
	while (i < 52)
	{
		glob->txtrs.gun_txtr[i] = mlx_load_png(generate_path(i + 1));
		if (!glob->txtrs.gun_txtr[i])
			error_log("failed to load gun image");
		i++;
	}
}

void	init_func(t_glob *glob)
{
	char	vue;

	glob->end_x = 0;
	glob->end_y = 0;
	glob->old_mouse_posx = -1;
	glob->width = (longest_line(glob)) * BLOCK_ZIZE;
	glob->height = (map_size(glob)) * BLOCK_ZIZE;
	glob->image = NULL;
	glob->mlx = NULL;
	glob->start_x = 0;
	glob->start_y = 0;
	glob->vue_angle = 0;
	glob->frames = 0;
	glob->rays_angle = (float)(60 * (M_PI / 180));
	glob->angle_incr = (float)(60 * (M_PI / 180)) / WIDTH; 
	glob->rotation_speed = (float)(2 * (M_PI / 180));
	glob->redraw = 1;
	glob->num_rays = WIDTH;
	glob->door_closed = 1;
	glob->txtrs.gun_txtr = NULL;
	// glob->rays_long = malloc (sizeof(float) * glob->width);
	glob->ray = malloc (sizeof(t_ray) * glob->num_rays);
	glob->txtrs.gun_txtr = malloc (sizeof(mlx_texture_t) * 52);
	init_gun_textrs(glob);
	// creat_texture(glob);
	// glob->ray_intesection = malloc(sizeof(char) * (glob->width + 1));
	// glob->ray_intesection[glob->width] = '\0';
	init_player_pos(glob, &vue);
	glob->start_x = (glob->start_x * BLOCK_ZIZE) + ((float)BLOCK_ZIZE / 2);
	glob->start_y = (glob->start_y * BLOCK_ZIZE) + ((float)BLOCK_ZIZE / 2);
	wich_vue(vue, glob);
}
