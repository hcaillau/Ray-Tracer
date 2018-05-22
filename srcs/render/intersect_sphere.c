/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:33:02 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 18:18:54 by mcasubol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_sphere(t_ray *ray, t_object *obj, t_float *t,
								t_inter *inter)
{
	t_float	abc[3];
	t_vec	d;
	t_vec	co;

	d = ray->dir;
	co = ray->origin;
	abc[0] = vec_dot(d, d);
	abc[1] = 2.0 * vec_dot(co, d);
	abc[2] = vec_dot(co, co) - obj->radius2;
	return ((*t = solve_quadra(abc, inter)));
}

void		norm_sphere(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)ray;
	(void)obj;
	inter->normal = vec_norm(-inter->obj_coord);
}

t_vec		map_sphere(t_vec inter)
{
	t_vec	uv;
	t_vec	n;

	n = vec_norm(inter);
	uv.x = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	uv.y = 0.5 - (asin(n.y) / M_PI);
	return (uv);
}
