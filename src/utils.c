/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:53:30 by ncourtoi          #+#    #+#             */
/*   Updated: 2024/12/31 15:59:01 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_words(const char *str, char c)
{
	int	i;
	int	occ;

	i = 0;
	occ = 0;
	while (*str)
	{
		if (*str != c && occ == 0)
		{
			occ = 1;
			i++;
		}
		else if (*str == c)
			occ = 0;
		str++;
	}
	return (i);
}

char	*word_dup(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	check_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0' && str[i] != '\n'
			&& str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

char	**ft_split(char *str, char c)
{
	int		i;
	int		j;
	int		index;
	char	**split;

	split = malloc((count_words(str, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(str))
	{
		if (str[i] != c && index < 0)
			index = i;
		else if ((str[i] == c || i == ft_strlen(str)) && index >= 0)
		{
			split[j++] = word_dup(str, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
