/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:31:18 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/15 16:45:00 by lzylberm         ###   ########.fr       */
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

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	**map;
}				t_vars;

int		get_next_line(int fd, char **line);
size_t	ft_strlen(char *str);

#endif
