/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:48:43 by robin             #+#    #+#             */
/*   Updated: 2022/05/25 15:50:02 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_built_in_env_fd(char **str, int fd)
{
	t_env	**env;

	if (*str == NULL)
		return (0);
	env = get_env_adress();
	ft_built_in_show_env_fd(env, fd);
	return (0);
}

void	ft_built_in_show_env_fd(t_env **env, int fd)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_is_equal(cur->str))
		{
			ft_putstr_fd(cur->str, fd);
			ft_putchar_fd('\n', fd);
		}
		cur = cur->next;
	}
}