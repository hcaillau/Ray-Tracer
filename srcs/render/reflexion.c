/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcasubol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:11:24 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/03 19:11:26 by mcasubol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "types.h"
#include "objects.h"
#include "sdl_m.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_ray				reflected_ray(t_inter inter, t_vec ray)
{
	t_ray	ret;

	ret.origin = inter.point;
	ret.dir = inter.normal * (2.0 * vec_dot(inter.normal, ray)) - ray;
	return (ret);
}

t_vec				reflexion(t_rt *rt, t_hit *hit, int depth)
{
	t_vec	reflected_color;
	t_hit	reflect;

	reflected_color = VEC_ZERO;
	if (depth > 0)
	{
		reflect.ray = reflected_ray(hit->inter, -1.0 * hit->ray.dir);
		reflect.ray.refraction = hit->ray.refraction;
		reflected_color = compute_color(rt, &reflect, depth - 1);
	}
	return (reflected_color);
}
