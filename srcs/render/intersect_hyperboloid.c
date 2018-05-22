/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_hyperboloid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcasubol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 18:56:53 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/03 18:57:06 by mcasubol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_hyperboloid(t_ray *ray, t_object *obj, t_float *t,
								t_inter *inter)
{
	double	abc[3];

	abc[0] = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z - obj->radius
			* ray->dir.y * ray->dir.y;
	abc[1] = 2.0 * (ray->origin.x * ray->dir.x + ray->dir.z
			* ray->origin.z - obj->radius * ray->dir.y * ray->origin.y);
	abc[2] = ray->origin.x * ray->origin.x + ray->origin.z
			* ray->origin.z - obj->radius * ray->origin.y * ray->origin.y - 1;
	return ((*t = solve_quadra(abc, inter)));
}

void		norm_hyperboloid(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)obj;
	(void)ray;
	inter->normal = VEC_INIT(inter->obj_coord.x, (-1)
			* inter->obj->radius * inter->obj_coord.y, inter->obj_coord.z);
}
