/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:02:05 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/16 18:03:25 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("entered move up\n");
	while (i < vars->height - 1)
	{
		while (j < vars->width)
		{
			if (vars->map[i][j].sprite == vars->sprites.player)
			{
				printf("player found\n");
				if (vars->map[i - 1][j].sprite == vars->sprites.wall)
					return ;
				else
				{
					vars->map[i - 1][j].sprite = vars->sprites.player;
					vars->map[i][j].sprite = vars->sprites.floor;
					put_sprites(vars);
					return ;
				}
			}
			printf("j = %d\n", j);
			j++;
		}
		j = 0;
		printf("i = %d\n", i);
		i++;
	}
}

void	move_left(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("entered move left\n");
	while (i < vars->height - 1)
	{
		while (j < vars->width)
		{
			if (vars->map[i][j].sprite == vars->sprites.player)
			{
				printf("player found\n");
				if (vars->map[i][j - 1].sprite == vars->sprites.wall)
					return ;
				else
				{
					vars->map[i][j - 1].sprite = vars->sprites.player;
					vars->map[i][j].sprite = vars->sprites.floor;
					put_sprites(vars);
					return ;
				}
			}
			printf("j = %d\n", j);
			j++;
		}
		j = 0;
		printf("i = %d\n", i);
		i++;
	}
}

void	move_right(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("entered move right\n");
	while (i < vars->height - 1)
	{
		while (j < vars->width)
		{
			if (vars->map[i][j].sprite == vars->sprites.player)
			{
				printf("player found\n");
				if (vars->map[i][j + 1].sprite == vars->sprites.wall)
					return ;
				else
				{
					vars->map[i][j + 1].sprite = vars->sprites.player;
					vars->map[i][j].sprite = vars->sprites.floor;
					put_sprites(vars);
					return ;
				}
			}
			printf("j = %d\n", j);
			j++;
		}
		j = 0;
		printf("i = %d\n", i);
		i++;
	}
}

void	move_down(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("entered move down\n");
	while (i < vars->height - 1)
	{
		while (j < vars->width)
		{
			if (vars->map[i][j].sprite == vars->sprites.player)
			{
				printf("player found\n");
				if (vars->map[i + 1][j].sprite == vars->sprites.wall)
					return ;
				else
				{
					vars->map[i + 1][j].sprite = vars->sprites.player;
					vars->map[i][j].sprite = vars->sprites.floor;
					put_sprites(vars);
					return ;
				}
			}
			printf("j = %d\n", j);
			j++;
		}
		j = 0;
		printf("i = %d\n", i);
		i++;
	}
}
