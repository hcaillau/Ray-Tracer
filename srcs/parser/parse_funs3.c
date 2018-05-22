/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 20:45:34 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 17:44:00 by mcasubol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "ft_math.h"
#include "rt.h"
#include "objects.h"
#include "types.h"
#include "vec.h"

int		parse_t_origin(void *data, char **strs)
{
	t_rt	*env;
	t_float	n[3];

	env = (t_rt *)data;
	if (ft_atof_s(strs[0], &n[0]) == ERROR
		|| ft_atof_s(strs[1], &n[1]) == ERROR
		|| ft_atof_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	return (camera_set_origin(env, VEC_INIT(n[0], n[1], n[2])));
}

int		parse_t_phong(void *data, char **strs)
{
	t_object	*obj;
	t_float		phong[PHONGS];
	int			shini;

	obj = (t_object *)data;
	if (ft_atoi_s(strs[0], &shini) == ERROR
		|| ft_atof_s(strs[1], &phong[PHONG_KD]) == ERROR
		|| ft_atof_s(strs[2], &phong[PHONG_KS]) == ERROR)
		return (ERROR);
	phong[PHONG_SHINI] = (t_float)shini;
	object_set_phong(obj, phong);
	return (SUCCESS);
}

int		parse_t_perturbation(void *data, char **strs)
{
	t_object	*obj;
	int			n;

	obj = (t_object *)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	object_set_perturbation(obj, n);
	return (SUCCESS);
}

int		parse_t_rot(void *data, char **strs)
{
	t_object	*obj;
	t_float		n[3];

	obj = (t_object *)data;
	if (ft_atof_s(strs[0], &n[0]) == ERROR
		|| ft_atof_s(strs[1], &n[1]) == ERROR
		|| ft_atof_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	return (object_set_matrix(obj, VEC_INIT(n[0], n[1], n[2])));
}

int		parse_t_side(void *data, char **strs)
{
	t_object	*obj;
	t_float		n;

	obj = (t_object*)data;
	if (ft_atof_s(strs[0], &n) == ERROR)
		return (ERROR);
	obj->side = n;
	return (SUCCESS);
}
