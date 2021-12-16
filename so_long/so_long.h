/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:31:18 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/16 18:39:09 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_map {
	int		x;
	int		y;
	char	*sprite;
}				t_map;

typedef struct	s_sprites {
	char	*wall;
	char	*floor;
	char	*collectible;
	char	*player;
	char	*exit;
}				t_sprites;
typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		img;
	char		**rules;
	t_map		**map;
	t_sprites	sprites;
	int			width;
	int			height;
}				t_vars;

int		get_next_line(int fd, char **line);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *src);
void	init_sprites(t_vars *vars);
void	get_size(char *argv, t_vars *vars);
void	parse_map(char *argv, t_vars *vars);
void	put_sprites(t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	move_up(t_vars *vars);
void	move_down(t_vars *vars);
void	move_left(t_vars *vars);
void	move_right(t_vars *vars);

#endif
