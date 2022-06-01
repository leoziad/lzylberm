/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:00:42 by robin             #+#    #+#             */
/*   Updated: 2022/05/25 16:01:12 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_init_env(t_env **env_list)
{
	char	*s;

	s = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (s == NULL)
		return (50);
	if (push_front("SHLVL=1", env_list, 1) == 50)
	{
		clean_env_list(env_list);
		return (50);
	}
	if (push_front(s, env_list, 1) == 50)
	{
		free(s);
		clean_env_list(env_list);
		return (50);
	}
	free(s);
	if (push_front("OLDPWD", env_list, 1) == 50)
	{
		clean_env_list(env_list);
		return (50);
	}
	return (0);
}
