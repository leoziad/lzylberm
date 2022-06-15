/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_export_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:51:15 by robin             #+#    #+#             */
/*   Updated: 2022/05/25 15:51:17 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_built_in_export_fd(char **str, int fd)
{
	int	i;

	i = 1;
	exit_status = 0;
	if (*(str + 1) == NULL)
	{
		ft_built_in_show_export_fd(fd);
		return (0);
	}
	while (str[i] != NULL)
	{
		if (ft_export_is_incorrect(str[i]))
		{
			exit_status = 1;
			printf("minishell: export: '%s': not a valid identifier\n", str[i]);
		}
		else if (env_modif(str[i], ADD) == 50)
			return (50);
		i++;
	}
	return (0);
}

void	ft_show_export_fd(t_env **env, int fd)
{
	t_env	*cur;
	int		len;

	cur = *env;
	while (cur)
	{
		len = ft_get_lenkey(cur->str);
		if (cur->declare == 1)
			ft_putstr_fd("declare -x ", fd);
		else
			ft_putstr_fd("export ", fd);
		ft_putstr_minus_fd(cur->str, len, fd);
		if (len < (int)ft_strlen(cur->str))
		{
			ft_putchar_fd('=', fd);
			ft_putchar_fd('"', fd);
			ft_putstr_fd(cur->str + len + 1, fd);
			ft_putchar_fd('"', fd);
		}
		ft_putchar_fd('\n', fd);
		cur = cur->next;
	}
}

void	ft_built_in_show_export_fd(int fd)
{
	t_env	**env;

	env = get_env_adress();
	ft_show_export_fd(env, fd);
}

void	ft_putstr_minus_fd(char *s, int len, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && i < len)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
