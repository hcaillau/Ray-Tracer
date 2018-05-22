/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_perturbation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:07:32 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/03 22:47:55 by hcaillau         ###   ########.fr       */
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

t_vec		normal_perturbation(t_inter inter)
{
	t_vec	n;

	n = vec_norm(matrix_mul_vec(inter.obj->w_to_obj, inter.normal));
	if (inter.obj->type == PLANE && inter.obj->perturbation == WATER)
		return (water_perturbation(n, inter));
	if (inter.obj->perturbation == WAVE)
		return (wave_perturbation(n, inter));
	return (inter.normal);
}

t_vec		water_perturbation(t_vec n, t_inter inter)
{
	t_vec	tmp1;
	t_vec	tmp2;
	t_float	v[3];
	t_float	epsi;

	epsi = 1.0;
	v[0] = n.x + inter.obj_coord.x + epsi;
	v[1] = n.y * 50 + 100 * inter.obj_coord.y;
	v[2] = n.z + inter.obj_coord.z;
	tmp1.x = noise3(v);
	v[0] = n.x + inter.obj_coord.x - epsi;
	tmp2.x = noise3(v);
	v[0] = n.x + inter.obj_coord.x;
	v[1] = n.y * 50 + 100 * inter.obj_coord.y + epsi;
	tmp1.y = noise3(v);
	v[1] = n.y * 50 + 100 * inter.obj_coord.y - epsi;
	tmp2.y = noise3(v);
	v[1] = n.y + inter.obj_coord.y;
	v[2] = n.z + inter.obj_coord.z + epsi;
	tmp1.z = noise3(v);
	v[2] = n.z + inter.obj_coord.z - epsi;
	tmp2.z = noise3(v);
	tmp1 = tmp2 - tmp1;
	return (vec_norm(tmp1 + n));
}

t_vec		wave_perturbation(t_vec n, t_inter inter)
{
	return (vec_norm(matrix_mul_vec(inter.obj->obj_to_w,
							VEC_INIT(n.x + sin(inter.obj_coord.x),
									n.y,
									n.z))));
}
