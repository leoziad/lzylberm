/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:12:26 by robin             #+#    #+#             */
/*   Updated: 2022/05/25 16:13:04 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_in_builin(t_cmd_line **first, pid_t *pid, int ret)
{
	free(pid);
	free_all(first);
	ft_clean_env();
	exit (ret);
	return (ret);
}