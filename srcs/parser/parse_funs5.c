/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:30:18 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/03 18:10:53 by hcaillau         ###   ########.fr       */
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

int				parse_t_limited(void *data, char **strs)
{
	t_object	*obj;
	int			n;
	t_float		o[3];
	t_float		p[3];

	obj = (t_object*)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	obj->is_limited = n;
	if (ft_atof_s(strs[1], &o[0]) == ERROR
		|| ft_atof_s(strs[2], &p[0]) == ERROR
		|| ft_atof_s(strs[3], &o[1]) == ERROR
		|| ft_atof_s(strs[4], &p[1]) == ERROR
		|| ft_atof_s(strs[5], &o[2]) == ERROR
		|| ft_atof_s(strs[6], &p[2]) == ERROR)
		return (ERROR);
	obj->lower_limit = VEC_INIT(o[0], o[1], o[2]);
	obj->upper_limit = VEC_INIT(p[0], p[1], p[2]);
	return (SUCCESS);
}

int				parse_t_texture(void *data, char **strs)
{
	t_object	*obj;
	int			n;
	t_float		off[2];
	t_float		scale[2];

	obj = (t_object *)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	if (ft_atof_s(strs[1], &off[0]) == ERROR
		|| ft_atof_s(strs[2], &off[1]) == ERROR
		|| ft_atof_s(strs[3], &scale[0]) == ERROR
		|| ft_atof_s(strs[4], &scale[1]) == ERROR)
		return (ERROR);
	obj->texture.off = VEC_INIT(clamp_f64(off[0], 0.0, 1.0),
								clamp_f64(off[1], 0.0, 1.0),
														0.0);
	obj->texture.scale = VEC_INIT(scale[0], scale[1], 0.0);
	return (object_set_texture(obj, n));
}
