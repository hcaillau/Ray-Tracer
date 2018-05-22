/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 18:58:22 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/03 22:21:04 by hcaillau         ###   ########.fr       */
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

t_ray		reflected_ray(t_inter inter, t_vec ray)
{
	t_ray	ret;

	ret.origin = inter.point;
	ret.dir = vec_scalar(inter.normal, 2 * vec_dot(inter.normal, ray));
	ret.dir = ret.dir - ray;
	return (ret);
}

t_uint		reflect(t_ray ray, t_rt *rt, int depth, t_inter inter)
{
	t_uint	reflected_color;
	t_ray	refl_ray;

	reflected_color = 0;
	if (depth > 0)
	{
		refl_ray = reflected_ray(inter, vec_opposite(ray.dir));
		refl_ray.refraction = ray.refraction;
		reflected_color = compute_color(refl_ray, depth - 1, rt);
	}
	return (reflected_color);
}

t_uint		refract(t_ray ray, t_rt *rt, int depth, t_inter inter)
{
	t_uint	refracted_color;
	t_ray	refracted_ray;

	refracted_color = 0;
	if (inter.obj->refraction >= 1.0 || inter.obj->transparency > 0)
	{
		refracted_ray = refract_ray(ray, inter);
		refracted_color = compute_color(refracted_ray, depth - 1, rt);
	}
	return (refracted_color);
}

t_ray		refract_ray(t_ray ray, t_inter inter)
{
	t_float	n;
	t_float	c1;
	t_float	c2;
	t_ray	ret;

	n = ray.refraction / inter.obj->refraction;
	vec_norm(ray.dir);
	c1 = vec_dot(vec_opposite(ray.dir), inter.normal);
	c2 = 1.0 - (n * n * (1.0 - (c1 * c1)));
	if (c2 < 0)
	{
		ret.origin = (t_vec){0.0, 0.0, 0.0, 0.0};
		return (ret);
	}
	c2 = sqrt(c2);
	ret.dir = vec_scalar(ray.dir, n);
	ret.dir = ret.dir + vec_scalar(inter.normal, (n * c1 - c2));
	ret.origin = inter.point;
	ret.refraction = inter.obj->refraction;
	return (ret);
}

t_float		fresnel(t_ray ray, t_inter inter)
{
	t_float	n;
	t_float	cosi;
	t_float	cost;
	t_float	sint;
	t_float	r[3];

	n = ray.refraction / inter.obj->refraction;
	cosi = vec_dot(vec_opposite(ray.dir), inter.normal);
	sint = n * sqrt(1 - cosi * cosi);
	if (sint >= 1)
		r[2] = 1;
	else
	{
		cost = sqrt(1 - sint * sint);
		r[0] = ((inter.obj->refraction * cosi) - (ray.refraction * cost))
			/ ((inter.obj->refraction * cosi) + (ray.refraction * cost));
		r[1] = ((ray.refraction * cost) - (inter.obj->refraction * cosi))
			/ ((ray.refraction * cost) + (inter.obj->refraction * cosi));
		r[2] = (r[0] * r[0] + r[1] * r[1]) / 2;
	}
	return (kr);
}
