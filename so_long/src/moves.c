/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:02:05 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/19 17:37:07 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_exit(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < vars->height - 1)
	{
		while (j < vars->width)
		{
			if (vars->map[i][j].sprite == vars->sprites.collectible)
				return (0);	
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	move_up(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < vars->height - 1)
	{
		while (j < vars->width)
		{
			if (vars->map[i][j].sprite == vars->sprites.player)
			{
				if (vars->map[i - 1][j].sprite == vars->sprites.wall)
					return ;
				else if (vars->map[i - 1][j].sprite == vars->sprites.exit && check_exit(vars))
					exit(0);
				else
				{
					vars->map[i - 1][j].sprite = vars->sprites.player;
					vars->map[i][j].sprite = vars->sprites.floor;
					put_sprites(vars);
					return ;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	move_left(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < vars->height - 1)
	{
		while (j < vars->width)
		{
			if (vars->map[i][j].sprite == vars->sprites.player)
			{
				if (vars->map[i][j - 1].sprite == vars->sprites.wall)
					return ;
				else if (vars->map[i][j - 1].sprite == vars->sprites.exit && check_exit(vars))
					exit(0);
				else
				{
					vars->map[i][j - 1].sprite = vars->sprites.player;
					vars->map[i][j].sprite = vars->sprites.floor;
					put_sprites(vars);
					return ;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	move_right(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < vars->height - 1)
	{
		while (j < vars->width)
		{
			if (vars->map[i][j].sprite == vars->sprites.player)
			{
				if (vars->map[i][j + 1].sprite == vars->sprites.wall)
					return ;
				else if (vars->map[i][j + 1].sprite == vars->sprites.exit && check_exit(vars))
					exit(0);
				else
				{
					vars->map[i][j + 1].sprite = vars->sprites.player;
					vars->map[i][j].sprite = vars->sprites.floor;
					put_sprites(vars);
					return ;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	move_down(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < vars->height - 1)
	{
		while (j < vars->width)
		{
			if (vars->map[i][j].sprite == vars->sprites.player)
			{
				if (vars->map[i + 1][j].sprite == vars->sprites.wall)
					return ;
				else if (vars->map[i + 1][j].sprite == vars->sprites.exit && check_exit(vars))
					exit(0);
				else
				{
					vars->map[i + 1][j].sprite = vars->sprites.player;
					vars->map[i][j].sprite = vars->sprites.floor;
					put_sprites(vars);
					return ;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
}
