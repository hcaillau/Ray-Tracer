/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:09:01 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 22:32:11 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "rt.h"

static size_t	ft_strcountc(char *str, char c)
{
	size_t	i;
	size_t	r;

	i = 0;
	r = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			r++;
		i++;
	}
	return (r);
}

static char		**get_line(char *str)
{
	char	**tmp;
	int		i;

	if (ft_strcountc(str, T_SEPAR) != 1)
		return (NULL);
	if ((tmp = ft_strsplit(str, T_SEPAR)) == NULL)
		return (NULL);
	if (tmp[0] == NULL || tmp[1] == NULL || tmp[2] != NULL)
	{
		ft_strsplit_free(tmp);
		return (NULL);
	}
	i = 0;
	while (tmp[i] != NULL)
	{
		if (trim_content(&tmp[i]) == ERROR)
		{
			ft_strsplit_free(tmp);
			return (NULL);
		}
		i++;
	}
	return (tmp);
}

int				check_line_object(char *lst, int type)
{
	char	*type_str;
	char	**r_str;
	int		r;
	int		i;

	r = ERROR;
	if ((type_str = ft_itoa(type)) == NULL)
		return (r);
	if ((r_str = ft_strsplit_whitespaces(lst)) == NULL)
	{
		free(type_str);
		return (r);
	}
	i = 0;
	while (r_str[i] != NULL)
	{
		if (ft_strcmp(type_str, r_str[i++]) == 0)
		{
			r = SUCCESS;
			break ;
		}
	}
	ft_strsplit_free(r_str);
	free(type_str);
	return (r);
}

static int		check_line_type(char **line, t_parse_type *data, int type)
{
	if (check_line_object(data->types, type) == ERROR)
		return (ERROR);
	if (ft_strcmp(line[0], data->name) != 0)
		return (ERROR);
	return (SUCCESS);
}

char			**check_line(char *str, int type, int *r)
{
	char			**tmp;
	t_parse_type	*parse_funs;
	int				i;

	if ((tmp = get_line(str)) == NULL)
		return (NULL);
	parse_funs = get_parse_funs();
	i = 0;
	while (parse_funs[i].name != NULL)
	{
		if (check_line_type(tmp, &(parse_funs[i]), type) == SUCCESS)
		{
			*r = i;
			break ;
		}
		i++;
	}
	if (parse_funs[i].name == NULL)
	{
		ft_strsplit_free(tmp);
		tmp = NULL;
	}
	return (tmp);
}
