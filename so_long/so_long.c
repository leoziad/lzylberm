/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:29:10 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/15 18:37:37 by lzylberm         ###   ########.fr       */
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
	t_data	tmp_img;
	int		x = 0;
	int		y = 0;
	int		width = 32;
	int		height = 32;
	
	if (keycode == 49)
	{
		tmp_img.img = mlx_new_image(vars->mlx, 1920, 1080);
		tmp_img.addr = mlx_get_data_addr(tmp_img.img, &tmp_img.bits_per_pixel, &tmp_img.line_length, &tmp_img.endian);
		while (x <= 1919)
		{
			while (y <= 1079)
			{
				my_mlx_pixel_put(&tmp_img, x, y, 0xA00000FF);
				y++;
			}
			y = 0;
			x++;
		}
		mlx_put_image_to_window(vars->mlx, vars->win, tmp_img.img, 0, 0);
	}
	else if (keycode == 13)
	{
		tmp_img.img = mlx_xpm_file_to_image(vars->mlx, "./sprites/reptile.xpm", &width, &height);
		tmp_img.addr = mlx_get_data_addr(tmp_img.img, &tmp_img.bits_per_pixel, &tmp_img.line_length, &tmp_img.endian);
		mlx_put_image_to_window(vars->mlx, vars->win, tmp_img.img, 0, 0);
	}
	else if (keycode == 0)
	{
		tmp_img.img = mlx_xpm_file_to_image(vars->mlx, "./sprites/reptile.xpm", &width, &height);
		tmp_img.addr = mlx_get_data_addr(tmp_img.img, &tmp_img.bits_per_pixel, &tmp_img.line_length, &tmp_img.endian);
		mlx_put_image_to_window(vars->mlx, vars->win, tmp_img.img, 32, 0);
	}
	else if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (1);
}

void	create_map(char *line, t_map **map, int i)
{
	int	x;
	int	y;
	int	index;

	map[i] = malloc(sizeof(t_map) * 15);
	index = 0;
	x = 0;
	y = i * 32;
	while (line[index])
	{
		printf("line[index] = %c\n", line[index]);
		if (line[index] == '1')
		{
			map[i][index].x = x; 
			map[i][index].y = y; 
			map[i][index].sprite = "./sprites/wall.xpm"; 
		}
		else if (line[index] == '0')
		{
			map[i][index].x = x;
			map[i][index].y = y;
			map[i][index].sprite = "./sprites/floor.xpm";
		}
		else if (line[index] == 'C')
		{
			map[i][index].x = x;
			map[i][index].y = y;
			map[i][index].sprite = "./sprites/gold.xpm";
		}
		index++;
		x += 32;
	}
	map[i][index].sprite = NULL;
}

void	parse_map(char *argv, t_vars *vars)
{
	int		fd;
	int		ret;
	char	*line;
	int		i;
	int	x = 0;
	int	y = 0;
	int	width;

	fd = open(argv, O_RDONLY);
	printf("file opened\n");
	i = 0;
	if (fd == -1)
	{
		write(0, "Map error\n", 10);
		exit(0);
	}
	ret = get_next_line(fd, &line);
	printf("line = %s\n", line);
	width = ft_strlen(line) * 32;
	printf("width = %d\n", width);
	while (ret == 1)
	{
		printf("gnl called\n");
		create_map(line, vars->map, i);
		i++;
		ret = get_next_line(fd, &line);
	}
	printf("map created\n");
	vars->map[i] = NULL;
	printf("height = %d\n", i * 32);
	vars->win = mlx_new_window(vars->mlx, width, i * 32, "so_long");
	printf("window created\n");
	vars->img.img = mlx_new_image(vars->mlx, width, i * 32);
	printf("original img init\n");
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	printf("original img addr init\n");
	while (x <= width - 1)
	{
		while (y <= (i * 32) - 1)
		{
			my_mlx_pixel_put(&vars->img, x, y, 0xA000FF00);
			y++;
		}
		y = 0;
		x++;
	}
	printf("original img created\n");
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	printf("original img put to win\n");
}

void	put_sprites(t_vars *vars)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 32;
	while (i < 5)
	{
		printf("vars.map[i] = %p\n", vars->map[i]);
		while (vars->map[i][j].sprite)
		{
			printf("vars.map[i][j].sprite = %s\n", vars->map[i][j].sprite);
			vars->img.img = mlx_xpm_file_to_image(vars->mlx, vars->map[i][j].sprite, &size, &size);
			printf("xpm to image\n");
			vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
			printf("img addr set\n");
			printf("vars.map[i][j].x = %d\n", vars->map[i][j].x);
			printf("vars.map[i][j].y = %d\n", vars->map[i][j].y);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, vars->map[i][j].x, vars->map[i][j].y);
			printf("img put to win\n");
			j++;
		}
		i++;
		j = 0;
	}
}

/*int	main(void)
{
	int		x = 0;
	int		y = 0;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	while (x <= 1919)
	{
		while (y <= 1079)
		{
			my_mlx_pixel_put(&vars.img, x, y, 0xA000FF00);
			y++;
		}
		y = 0;
		x++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);

	return (0);
}*/

char	**check_map(char *argv)
{
	char	**map_val;
	int		fd;

}

int	main(int argc, char **argv)
{
	t_vars	*vars = malloc(sizeof(t_vars));

	vars->mlx = mlx_init();
	if (argc == 2)
	{
		vars->map = malloc(sizeof(t_map *) * 6);
		parse_map(argv[1], vars);
		printf("map parsed\n");
		put_sprites(vars);
		printf("sprites put\n");
	}
	mlx_key_hook(vars->win, key_hook, &vars);
	printf("key_hook init\n");
	mlx_loop(vars->mlx);

	free(vars);
	return (0);
}
