/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_paraboloid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcasubol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 18:57:34 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/03 18:57:45 by mcasubol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_paraboloid(t_ray *ray, t_object *obj, t_float *t,
								t_inter *inter)
{
	double	abc[3];

	abc[0] = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	abc[1] = 2.0 * (ray->origin.x * ray->dir.x + ray->dir.z * ray->origin.z)
			- obj->radius * ray->dir.y;
	abc[2] = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z
			- obj->radius * ray->origin.y;
	return ((*t = solve_quadra(abc, inter)));
}

void		norm_paraboloid(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)ray;
	(void)obj;
	inter->normal = vec_norm(VEC_INIT(
		inter->obj_coord.x,
		(-1) * inter->obj->radius,
		inter->obj_coord.z));
}
