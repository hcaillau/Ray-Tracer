/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:31:31 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 22:43:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "ft_math.h"
#include "objects.h"
#include "rt.h"
#include "types.h"
#include "vec.h"

int		parse_t_pos(void *data, char **strs)
{
	t_object	*obj;
	t_float		n[3];
	t_vec		pos;

	obj = (t_object *)data;
	if (ft_atof_s(strs[0], &n[0]) == ERROR
		|| ft_atof_s(strs[1], &n[1]) == ERROR
		|| ft_atof_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	pos = VEC_INIT(n[0], n[1], n[2]);
	object_set_pos(obj, pos);
	return (SUCCESS);
}

int		parse_t_dir(void *data, char **strs)
{
	t_object	*obj;
	t_float		n[3];
	t_vec		pos;

	obj = (t_object *)data;
	if (ft_atof_s(strs[0], &n[0]) == ERROR
		|| ft_atof_s(strs[1], &n[1]) == ERROR
		|| ft_atof_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	pos = VEC_INIT(n[0], n[1], n[2]);
	object_set_dir(obj, pos);
	return (SUCCESS);
}

int		parse_t_radius(void *data, char **strs)
{
	t_object	*obj;
	t_float		size;

	obj = (t_object *)data;
	if (ft_atof_s(strs[0], &size) == ERROR)
		return (ERROR);
	object_set_radius(obj, size);
	return (SUCCESS);
}

int		parse_t_color(void *data, char **strs)
{
	t_object	*obj;
	int			n[3];
	t_vec		pos;

	obj = (t_object *)data;
	if (ft_atoi_s(strs[0], &n[0]) == ERROR
		|| ft_atoi_s(strs[1], &n[1]) == ERROR
		|| ft_atoi_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	pos = VEC_INIT((t_float)n[0], (t_float)n[1], (t_float)n[2]);
	object_set_color(obj, pos);
	return (SUCCESS);
}

int		parse_t_intensity(void *data, char **strs)
{
	t_object	*obj;
	t_float		n[3];
	t_vec		pos;

	obj = (t_object *)data;
	if (ft_atof_s(strs[0], &n[0]) == ERROR
		|| ft_atof_s(strs[1], &n[1]) == ERROR
		|| ft_atof_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	pos = VEC_INIT(n[0], n[1], n[2]);
	object_set_intensity(obj, pos);
	return (SUCCESS);
}
