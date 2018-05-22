/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_limited_planes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcasubol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:42:44 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/03 18:02:14 by mcasubol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

static void			intersect_square(t_vec inter, t_object *obj, t_float *t)
{
	if (inter.x < 0 || inter.x > obj->side
		|| inter.z < 0 || inter.z > obj->side)
		*t = FLOAT_ZERO;
}

static void			intersect_disk(t_vec inter, t_object *obj, t_float *t)
{
	if (POW(inter.x) + POW(inter.z) > obj->radius2)
		*t = FLOAT_ZERO;
}

static void			intersect_ring(t_vec inter, t_object *obj, t_float *t)
{
	if (POW(inter.x) + POW(inter.z) > POW(obj->radius + obj->side)
		|| POW(inter.x) + POW(inter.z) < POW(obj->radius))
		*t = FLOAT_ZERO;
}

t_float				intersect_limited_planes(t_ray *ray, t_object *obj,
											t_float *t, t_inter *inter)
{
	t_vec			tmp_inter;

	*t = -(ray->origin.y / ray->dir.y);
	tmp_inter = ray->origin + ray->dir * *t;
	inter->t2[0] = *t;
	inter->t2[1] = FLOAT_MAX;
	if (obj->type == SQUARE)
		intersect_square(tmp_inter, obj, t);
	else if (obj->type == DISK)
		intersect_disk(tmp_inter, obj, t);
	else if (obj->type == RING)
		intersect_ring(tmp_inter, obj, t);
	return (SUCCESS);
}
