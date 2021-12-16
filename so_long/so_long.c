/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:29:10 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/16 18:39:04 by lzylberm         ###   ########.fr       */
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
	printf("key hook entered\n");
	printf("map height = %d\n", vars->height);
	if (keycode == 13)
		move_up(vars);
	else if (keycode == 0)
		move_left(vars);
	else if (keycode == 1)
		move_down(vars);
	else if (keycode == 2)
		move_right(vars);
	else if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	*vars = malloc(sizeof(t_vars));

	vars->mlx = mlx_init();
	if (argc == 2)
	{
		init_sprites(vars);
		get_size(argv[1], vars);
		printf("got size\n");
		printf("map width = %d\n", vars->width);
		printf("map height = %d\n", vars->height);
		vars->map = malloc(sizeof(t_map *) * vars->height);
		printf("vars->map alloc\n");
		parse_map(argv[1], vars);
		printf("map parsed\n");
		put_sprites(vars);
		printf("sprites put\n");
	}
	mlx_key_hook(vars->win, key_hook, vars);
	printf("key_hook init\n");
	mlx_loop(vars->mlx);

	free(vars);
	return (0);
}
