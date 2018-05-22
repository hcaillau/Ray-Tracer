/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:10:20 by hcaillau          #+#    #+#             */
/*   Updated: 2018/05/03 22:18:11 by hcaillau         ###   ########.fr       */
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

t_vec				light(t_inter it, t_vec v, t_rt *rt)
{
	t_vec			i[4];
	t_ray			r;
	int				j;

	i[0] = (t_vec){0.0, 0.0, 0.0, 0.0};
	j = 0;
	while (j < rt->objects.size)
	{
		i[3][0] = 1.0;
		i[3][0] = diffuse_light(&r, it, &j, rt);
		if (i[3][0] < 0.000001)
			continue;
		if (vec_dot(r.dir, it.normal) < 0
			&& it.obj->transparency > 0)
			it.normal = vec_opposite(it.normal);
		i[1][0] = vec_dot(it.normal, r.dir);
		i[2] = vec_scalar(rt->objects.objects_array[j].intensity,
							it.obj->phong[PHONG_KD]);
		i[0] = i[0] + vec_scalar(light_specular(it, i, v, &r), i[3][0]);
		j++;
	}
	return (i[0]);
}

t_float				diffuse_light(t_ray *r, t_inter it, int *j,
		t_rt *rt)
{
	t_inter				inter;
	t_ray				rayon;

	if (rt->objects.objects_array[*j].type == LIGHT_POINT)
	{
		r->dir = rt->objects.objects_array[*j].dir - it.point;
		vec_norm(r->dir);
		r->origin = it.point;
		rayon.origin = it.point;
		rayon.dir = r->dir;
		closest_intersect(rayon, 1.0, rt->objects, &inter);
	}
	else if (rt->objects.objects_array[*j].type == LIGHT_PAR)
	{
		r->origin = it.point;
		r->dir = vec_opposite(rt->objects.objects_array[*j].dir);
		vec_norm(r->dir);
		rayon.origin = it.point;
		rayon.dir = r->dir;
		closest_intersect(rayon, LONG_MAX, rt->objects, &inter);
	}
	if (inter.obj != NULL)
		return (transparent_shadow(inter, rayon, rt));
	return (1.0);
}

t_float				transparent_shadow(t_inter inter, t_ray rayon, t_rt *rt)
{
	t_ray				refr_ray;
	t_inter				transp_inter;

	if (inter.obj != NULL)
	{
		if (inter.obj->refraction >= 1.0 && inter.obj->transparency > 0)
		{
			transp_inter = inter;
			refr_ray = refract_ray(rayon, inter);
			closest_intersect(refr_ray, LONG_MAX, rt->objects, &inter);
			if (inter.obj != NULL)
			{
				j++;
				return (0.0);
			}
			else
				return (transp_inter.obj->transparency);
		}
		else
			j++;
		return (0.0);
	}
}

t_vec				light_specular(t_inter it, t_vec i[4], t_vec v, t_ray *r)
{
	t_vec	ret;

	ret = (t_vec){0.0, 0.0, 0.0, 0.0};
	if (i[1][0] > 0)
	{
		ret = vec_scalar(i[2], i[1][0]);
		if (it.obj->phong[PHONG_SHINI] > 0)
		{
			r->dir = vec_scalar(it.normal, vec_dot(it.normal, r->dir) * 2.0)
						- r->dir;
			i[1][0] = vec_dot(r->dir, v);
			if (i[1][0] > 0)
				ret += vec_scalar(i[2], (t_float)(pow(i[1][0] / (vec_len(r->dir)
							* vec_len(v)), it.obj->phong[PHONG_SHINI])));
		}
	}
	return (ret);
}
