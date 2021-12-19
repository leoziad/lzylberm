/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:29:10 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/19 17:37:09 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{	
	if (keycode == 13)
		move_up(vars);
	else if (keycode == 0)
		move_left(vars);
	else if (keycode == 1)
		move_down(vars);
	else if (keycode == 2)
		move_right(vars);
	else if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (1);
}

void	put_default(t_vars *vars)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 32;
	while (i < vars->height - 1)
	{
		while (vars->map[i][j].sprite)
		{
			vars->img.img = mlx_xpm_file_to_image(vars->mlx, vars->sprites.floor, &size, &size);
			vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, vars->map[i][j].x, vars->map[i][j].y);
			j++;
		}
		i++;
		j = 0;
	}
}

int	main(int argc, char **argv)
{
	t_vars	*vars = malloc(sizeof(t_vars));

	vars->mlx = mlx_init();
	if (argc == 2)
	{
		init_sprites(vars);
		get_size(argv[1], vars);
		vars->map = malloc(sizeof(t_map *) * vars->height);
		parse_map(argv[1], vars);
		put_default(vars);
		put_sprites(vars);
	}
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_loop(vars->mlx);

	free(vars);
	return (0);
}
