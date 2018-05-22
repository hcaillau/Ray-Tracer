/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 18:51:24 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 22:00:56 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_cylinder(t_ray *ray, t_object *obj, t_float *t,
								t_inter *inter)
{
	t_float	abc[3];

	abc[0] = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	abc[1] = 2.0 * ray->dir.x * ray->origin.x + 2.0 * ray->dir.z
			* ray->origin.z;
	abc[2] = ray->origin.x * ray->origin.x + ray->origin.z
			* ray->origin.z - obj->radius2;
	return ((*t = solve_quadra(abc, inter)));
}

void		norm_cylinder(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)ray;
	(void)obj;
	inter->normal = vec_norm(VEC_INIT(
		inter->obj_coord.x,
		0.0,
		inter->obj_coord.z));
}
