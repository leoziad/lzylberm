/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:44:03 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/16 18:39:12 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_sprites(t_vars *vars)
{
	vars->sprites.wall = ft_strdup("./sprites/wall.xpm");
	vars->sprites.floor = ft_strdup("./sprites/floor.xpm");
	vars->sprites.collectible = ft_strdup("./sprites/gold.xpm");
	vars->sprites.player = ft_strdup("./sprites/reptile.xpm");
	vars->sprites.exit = ft_strdup("./sprites/exit.xpm");
}

void	get_size(char *argv, t_vars *vars)
{
	int	fd;
	int	width;
	int	height;
	char	c;

	width = 0;
	height = 2;
	fd = open(argv, O_RDONLY);
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		width++;
	}
	vars->width = width;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			height++;
	}
	vars->height = height;
	close(fd);
}

void	create_map(char *line, t_vars *vars, int i)
{
	int	x;
	int	y;
	int	index;

	vars->map[i] = malloc(sizeof(t_map) * (vars->width + 1));
	printf("vars->map[i] alloc\n");
	index = 0;
	x = 0;
	y = i * 32;
	while (line[index])
	{
		printf("line[index] = %c\n", line[index]);
		if (line[index] == '1')
		{
			vars->map[i][index].x = x;
			vars->map[i][index].y = y;
			vars->map[i][index].sprite = vars->sprites.wall;
		}
		else if (line[index] == '0')
		{
			vars->map[i][index].x = x;
			vars->map[i][index].y = y;
			vars->map[i][index].sprite = vars->sprites.floor;
		}
		else if (line[index] == 'C')
		{
			vars->map[i][index].x = x;
			vars->map[i][index].y = y;
			vars->map[i][index].sprite = vars->sprites.collectible;
		}
		else if (line[index] == 'P')
		{
			vars->map[i][index].x = x;
			vars->map[i][index].y = y;
			vars->map[i][index].sprite = vars->sprites.player;
		}
		else if (line[index] == 'E')
		{
			vars->map[i][index].x = x;
			vars->map[i][index].y = y;
			vars->map[i][index].sprite = vars->sprites.exit;
		}
		index++;
		x += 32;
	}
	vars->map[i][index].sprite = NULL;
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
		create_map(line, vars, i);
		free(line);
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
	while (i < vars->height - 1)
	{
//		printf("vars.map[i] = %p\n", vars->map[i]);
		while (vars->map[i][j].sprite)
		{
//			printf("vars.map[i][j].sprite = %s\n", vars->map[i][j].sprite);
			vars->img.img = mlx_xpm_file_to_image(vars->mlx, vars->map[i][j].sprite, &size, &size);
//			printf("xpm to image\n");
			vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
//			printf("img addr set\n");
//			printf("vars.map[i][j].x = %d\n", vars->map[i][j].x);
//			printf("vars.map[i][j].y = %d\n", vars->map[i][j].y);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, vars->map[i][j].x, vars->map[i][j].y);
//			printf("img put to win\n");
			j++;
		}
		i++;
		j = 0;
	}
}
