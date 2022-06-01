/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:36:20 by robin             #+#    #+#             */
/*   Updated: 2022/05/25 15:37:32 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_built_in_show_export(void)
{
	t_env	**env;

	env = get_env_adress();
	ft_show_export(env);
}

int	ft_export_is_incorrect(char *s)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(s[0]) && s[0] != '_'))
		return (1);
	while (s[i] && s[i] != '=')
	{
		if ((!ft_isalnum(s[i]) && s[i] != '_'))
		{
			if (!(s[i] == '+' && s[i + 1] == '='))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_built_in_export(char **str)
{
	int	i;

	i = 1;
	exit_status = 0;
	if (*(str + 1) == NULL)
	{
		ft_built_in_show_export();
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

void	ft_show_export(t_env **env)
{
	t_env	*cur;
	int		len;

	cur = *env;
	while (cur)
	{
		len = ft_get_lenkey(cur->str);
		if (cur->declare == 1)
			printf("declare -x %.*s", len, cur->str);
		else
			printf("export %.*s", len, cur->str);
		if (len < (int)ft_strlen(cur->str))
			printf("=\"%s\"", cur->str + len + 1);
		printf("\n");
		cur = cur->next;
	}
}
