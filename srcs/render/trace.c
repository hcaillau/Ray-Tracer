/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:14:14 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 19:43:53 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"
#include "stdio.h"

void			compute_hit_normal(t_ray *ray, t_inter *inter)
{
	if (inter->obj->type == PLANE)
		norm_plane(ray, inter->obj, inter);
	else if (inter->obj->type == SPHERE)
		norm_sphere(ray, inter->obj, inter);
	else if (inter->obj->type == CYLINDER)
		norm_cylinder(ray, inter->obj, inter);
	else if (inter->obj->type == CONE)
		norm_cone(ray, inter->obj, inter);
	else if (inter->obj->type == PARABOLOID)
		norm_paraboloid(ray, inter->obj, inter);
	else if (inter->obj->type == HYPERBOLOID)
		norm_hyperboloid(ray, inter->obj, inter);
	else if (inter->obj->type == SQUARE
			|| inter->obj->type == DISK
			|| inter->obj->type == RING)
		norm_plane(ray, inter->obj, inter);
	inter->normal = vec_norm(matrix_mul_vec(inter->obj->obj_to_w,
		inter->normal));
}

t_float			intersect(t_ray *ray, t_object *obj, t_inter *inter)
{
	t_float		t;

	t = FLOAT_ZERO;
	if (obj->type == PLANE)
		intersect_plane(ray, obj, &t, inter);
	else if (obj->type == SPHERE)
		intersect_sphere(ray, obj, &t, inter);
	else if (obj->type == CYLINDER)
		intersect_cylinder(ray, obj, &t, inter);
	else if (obj->type == CONE)
		intersect_cone(ray, obj, &t, inter);
	else if (obj->type == PARABOLOID)
		intersect_paraboloid(ray, obj, &t, inter);
	else if (obj->type == HYPERBOLOID)
		intersect_hyperboloid(ray, obj, &t, inter);
	else if (obj->type == SQUARE
			|| obj->type == DISK
			|| obj->type == RING)
		intersect_limited_planes(ray, obj, &t, inter);
	return (t);
}

static void		init_tmp(t_hit *hit, t_object *objs, int i, t_ray *tmp)
{
	tmp->origin = hit->ray.origin;
	tmp->dir = hit->ray.dir;
	tmp->origin -= objs[i].pos;
	tmp->origin = matrix_mul_vec(objs[i].w_to_obj, tmp->origin);
	tmp->dir = matrix_mul_vec(objs[i].w_to_obj, tmp->dir);
}

static void		trace_it(t_hit *hit, t_object *obj, t_ray *tmp,
					t_float max_inter)
{
	t_float		t;

	if ((t = intersect(tmp, obj, &hit->inter)) > FLOAT_MIN)
	{
		if (t < hit->inter.t && t < max_inter)
		{
			if (obj->is_limited > 0)
			{
				if ((hit->inter.t2[0] < hit->inter.t
					|| hit->inter.t2[1] < hit->inter.t)
					&& is_cut(obj, hit, &t, tmp) == 0)
				{
					hit->inter.t = t;
					hit->inter.obj = obj;
				}
			}
			else
			{
				hit->inter.t = t;
				hit->inter.obj = obj;
			}
			hit->inter.obj_coord = (tmp->dir * hit->inter.t) + tmp->origin;
		}
	}
}

int				trace(t_rt *rt, t_hit *hit, t_float max_inter)
{
	t_object	*objs;
	int			i;
	t_ray		tmp;

	hit->inter.t = FLOAT_MAX;
	hit->inter.obj = NULL;
	objs = rt->objects.objects_array;
	i = 0;
	while (i < rt->objects.size)
	{
		init_tmp(hit, objs, i, &tmp);
		trace_it(hit, &objs[i], &tmp, max_inter);
		i++;
	}
	if (hit->inter.obj != NULL)
		hit->inter.point = (hit->ray.dir * hit->inter.t) + hit->ray.origin;
	return (hit->inter.obj == NULL ? ERROR : SUCCESS);
}
