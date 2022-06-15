/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:07:30 by robin             #+#    #+#             */
/*   Updated: 2022/05/25 16:07:45 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	ft_delete_env(char *str)
{
	return (env_modif(str, DELETE));
}

void	ft_delete_env_call(t_env **env, char *key)
{
	t_env	*cpy;
	t_env	*prev;
	int		len;

	len = ft_get_lenkey(key);
	prev = NULL;
	cpy = *env;
	while (cpy)
	{
		if (len == ft_get_lenkey(cpy->str) && !ft_strncmp(cpy->str, key, len))
		{
			if (prev == NULL)
				*env = cpy->next;
			else
				prev->next = cpy->next;
			ft_free_env_elem(cpy);
			return ;
		}
		prev = cpy;
		cpy = cpy->next;
	}
}