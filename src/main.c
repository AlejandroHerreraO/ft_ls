/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:58:56 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/21 14:53:57 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

static int	aux_error_mode(int **mode)
{
	ft_printf("ft_ls: illegal option -- %c\n",	(char)mode[0][5]);
	free(*mode);
	return (0);
}

static void	check(char *str, int *mode)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'l')
			mode[0] = 1;
		else if (str[i] == '1')
			mode[0] = 2;
		else if (str[i] == 'a')
			mode[1] = 1;
		else if (str[i] == 'R')
			mode[2] = 1;
		else if (str[i] == 't')
			mode[3] = 2;
		else if (str[i] == 'r')
			mode[3] = -mode[3];
		else
		{
			mode[5] = str[i];
			return ;
		}
		i++;
	}
}

static int	*get_mode(char **av, int *i, int ac)
{
	int	*mode;

	mode = (int *)malloc(6 * sizeof(int));
	mode[0] = 0;
	mode[1] = 0;
	mode[2] = 0;
	mode[3] = 1;
	mode[4] = 0;
	mode[5] = -1;
	while (av[*i] && av[*i][0] == '-' && av[*i][1])
	{
		check(av[*i], mode);
		*i = *i + 1;
		if (mode[5] != -1)
			return (mode);
	}
	if (ac > *i + 1)
		mode[4] = 1;
	return (mode);
}

int			main(int ac, char **av)
{
	int	i;
	int	*mode;
	int l;

	i = 1;
	mode = get_mode(av, &i, ac);
	l = 0;
	if (mode[5] != -1)
		return (aux_error_mode(&mode));
	if (ac == i)
	{
		av[i] = ft_strdup(".");
		av[i + 1] = NULL;
		l = i;
	}
	while (av[i])
	{
		ls(av[i], mode);
		i++;
	}
	if (l != 0)
		ft_strdel(&av[l]);
	free(mode);
	return (0);
}
