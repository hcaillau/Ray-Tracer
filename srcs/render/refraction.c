/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:11:46 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/03 19:42:44 by vparis           ###   ########.fr       */
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

t_vec			refract(t_rt *rt, t_hit *hit, int depth)
{
	t_vec		refracted_color;
	t_hit		refract;

	refracted_color = VEC_ZERO;
	refract.inter = hit->inter;
	if (hit->inter.obj->refraction >= 1.0 && hit->inter.obj->transparency > 0)
	{
		refract.ray = refract_ray(hit->ray, hit->inter);
		refracted_color = compute_color(rt, &refract, depth - 1);
	}
	return (refracted_color);
}

t_ray			refract_ray(t_ray ray, t_inter inter)
{
	t_float		n;
	t_float		c1;
	t_float		c2;
	t_ray		ret;

	n = ray.refraction / inter.obj->refraction;
	ray.dir = vec_norm(ray.dir);
	c1 = vec_dot(-1 * ray.dir, inter.normal);
	c2 = 1.0 - (n * n * (1.0 - (c1 * c1)));
	if (c2 < 0)
	{
		ret.origin = VEC_ZERO;
		return (ret);
	}
	c2 = sqrt(c2);
	ret.dir = ray.dir * n;
	ret.dir = ret.dir + inter.normal * (n * c1 - c2);
	ret.origin = inter.point;
	ret.refraction = inter.obj->refraction;
	return (ret);
}

/*
** rs = 0, rp = 1, kr = 3
*/

t_float			fresnel(t_ray ray, t_inter inter)
{
	t_float		n;
	t_float		cosi;
	t_float		cost;
	t_float		sint;
	t_float		coeff[3];

	n = ray.refraction / inter.obj->refraction;
	cosi = vec_dot(-1 * ray.dir, inter.normal);
	sint = n * sqrt(1 - cosi * cosi);
	if (sint >= 1)
		coeff[2] = 1;
	else
	{
		cost = sqrt(1 - sint * sint);
		coeff[0] = ((inter.obj->refraction * cosi) - (ray.refraction * cost))
			/ ((inter.obj->refraction * cosi) + (ray.refraction * cost));
		coeff[1] = ((ray.refraction * cost) - (inter.obj->refraction * cosi))
			/ ((ray.refraction * cost) + (inter.obj->refraction * cosi));
		coeff[2] = (coeff[0] * coeff[0] + coeff[1] * coeff[1]) / 2.0;
	}
	return (coeff[2]);
}
