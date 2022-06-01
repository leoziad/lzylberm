/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 09:07:59 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 15:58:54 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(char const *str, char c)
{
	int	index;

	index = 0;
	while (str[index] != '\0' && str[index] != c)
		index++;
	return (index);
}

static int	ft_word_count(char const *str, char c)
{
	int		len;
	int		word_count;

	word_count = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && *str == c)
			str++;
		len = ft_word_len(str, c);
		str = str + len;
		if (len != 0)
			word_count++;
	}
	return (word_count);
}

static char	*ft_worddup(char const *src, int len)
{
	char	*dest;
	int		index;

	index = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (index < len)
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		index_a;
	int		index_b;
	int		w_len;

	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	index_a = 0;
	index_b = 0;
	while (index_b < ft_word_count(s, c))
	{
		while (s[index_a] != '\0' && s[index_a] == c)
			index_a++;
		w_len = ft_word_len(&s[index_a], c);
		tab[index_b] = ft_worddup(&s[index_a], w_len);
		if (tab[index_b] == NULL)
			return (NULL);
		index_a = index_a + w_len;
		index_b++;
	}
	tab[ft_word_count(s, c)] = ((void *)0);
	return (tab);
}
