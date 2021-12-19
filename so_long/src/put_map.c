/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:44:03 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/19 17:37:05 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_sprites(t_vars *vars)
{
	vars->sprites.wall = ft_strdup("./sprites/wall.xpm");
	vars->sprites.floor = ft_strdup("./sprites/floor.xpm");
	vars->sprites.collectible = ft_strdup("./sprites/collectible.xpm");
	vars->sprites.player = ft_strdup("./sprites/player.xpm");
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
	index = 0;
	x = 0;
	y = i * 32;
	while (line[index])
	{
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
	i = 0;
	if (fd == -1)
	{
		write(0, "Map error\n", 10);
		exit(0);
	}
	ret = get_next_line(fd, &line);
	width = ft_strlen(line) * 32;
	while (ret == 1)
	{
		create_map(line, vars, i);
		free(line);
		i++;
		ret = get_next_line(fd, &line);
	}
	vars->map[i] = NULL;
	vars->win = mlx_new_window(vars->mlx, width, i * 32, "so_long");
	vars->img.img = mlx_new_image(vars->mlx, width, i * 32);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
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
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
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
		while (vars->map[i][j].sprite)
		{
			vars->img.img = mlx_xpm_file_to_image(vars->mlx, vars->map[i][j].sprite, &size, &size);
			vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, vars->map[i][j].x, vars->map[i][j].y);
			j++;
		}
		i++;
		j = 0;
	}
}
