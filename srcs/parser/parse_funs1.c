/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:30:20 by vparis            #+#    #+#             */
/*   Updated: 2018/04/27 15:28:53 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "rt.h"
#include "parser.h"
#include "ft_math.h"
#include "types.h"
#include "vec.h"

int		parse_t_width(void *data, char **strs)
{
	t_rt	*env;
	int		n;

	env = (t_rt *)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	return (canvas_set_width(env, n));
}

int		parse_t_height(void *data, char **strs)
{
	t_rt	*env;
	int		n;

	env = (t_rt *)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	return (canvas_set_height(env, n));
}

int		parse_t_background(void *data, char **strs)
{
	t_rt	*env;
	int		n[3];
	t_vec	color;

	env = (t_rt *)data;
	if (ft_atoi_s(strs[0], &n[0]) == ERROR
		|| ft_atoi_s(strs[1], &n[1]) == ERROR
		|| ft_atoi_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	color = VEC_INIT(
		(t_float)clamp_i32(n[0], 0, 255) / 255.0,
		(t_float)clamp_i32(n[1], 0, 255) / 255.0,
		(t_float)clamp_i32(n[2], 0, 255) / 255.0);
	return (canvas_set_bg_color(env, color));
}

int		parse_t_ang(void *data, char **strs)
{
	t_rt	*env;
	t_float	n[3];

	env = (t_rt *)data;
	if (ft_atof_s(strs[0], &n[0]) == ERROR
		|| ft_atof_s(strs[1], &n[1]) == ERROR
		|| ft_atof_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	return (camera_set_angle(env, VEC_INIT(n[0], n[1], n[2])));
}

int		parse_t_fov(void *data, char **strs)
{
	t_rt	*env;
	int		n;

	env = (t_rt *)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	return (camera_set_fov(env, (t_float)n));
}
