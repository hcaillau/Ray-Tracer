/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:56:40 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/03 19:44:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

static int	in_limit(t_vec inter, t_object *obj)
{
	t_vec	low;
	t_vec	up;

	low = obj->lower_limit;
	up = obj->upper_limit;
	if (inter.x > low.x && inter.x < up.x
		&& inter.y > low.y && inter.y < up.y
		&& inter.z > low.z && inter.z < up.z)
		return (1);
	return (0);
}

int			is_cut(t_object *obj, t_hit *hit, t_float *t, t_ray *simple)
{
	t_vec	inter[2];
	int		i;

	i = -1;
	*t = FLOAT_ZERO;
	while (++i < 2)
		inter[i] = (obj->is_limited == 1)
			? simple->origin + simple->dir * hit->inter.t2[i]
			: hit->ray.origin + hit->ray.dir * hit->inter.t2[i];
	if (in_limit(inter[0], obj))
		*t = (in_limit(inter[1], obj))
		? fminf(hit->inter.t2[0], hit->inter.t2[1]) : hit->inter.t2[0];
	else if (in_limit(inter[1], obj))
		*t = hit->inter.t2[1];
	if (*t > FLOAT_MIN)
		return (0);
	if (hit->inter.t2[0] < hit->inter.t2[1])
		return (in_limit(inter[1], obj)
		&& ((*t = hit->inter.t2[1]) > FLOAT_MIN)) ? (0) : (1);
	else
	{
		return (in_limit(inter[0], obj)
		&& ((*t = hit->inter.t2[0]) > FLOAT_MIN)) ? (0) : (1);
	}
	return (1);
}
