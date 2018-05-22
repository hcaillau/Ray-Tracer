/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:59:48 by hcaillau          #+#    #+#             */
/*   Updated: 2018/05/03 22:46:51 by hcaillau         ###   ########.fr       */
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

t_vec		color_perturbation(t_inter inter)
{
	t_float		t;
	t_float		v[3];
	t_vec		color;

	color = inter.obj->color;
	if (inter.obj->perturbation == CHESS)
	{
		if (inter.obj->type == PLANE)
			return (color = chess_plane(inter));
		else
			return (color = chess(inter));
	}
	if (inter.obj->perturbation == MARBLE1
		|| inter.obj->perturbation == MARBLE2)
	{
		v[0] = inter.obj_coord.x;
		v[1] = inter.obj_coord.y;
		v[2] = inter.obj_coord.z;
		t = noise3(v);
		if (inter.obj->perturbation == MARBLE1)
			return (color = marble1(t, inter));
		else
			return (color = marble2(t, inter));
	}
	return (color);
}

t_vec		chess_plane(t_inter inter)
{
	if ((inter.obj_coord.x < 0 && inter.obj_coord.z < 0)
		|| (inter.obj_coord.x > 0 && inter.obj_coord.z > 0))
	{
		if ((int)fabs(inter.obj_coord.x) % 10 < 5
			&& ((int)fabs(inter.obj_coord.z) % 10 < 5))
			return (VEC_INIT(0.0, 0.0, 0.0));
		if (!((int)fabs(inter.obj_coord.x) % 10 < 5
			|| ((int)fabs(inter.obj_coord.z) % 10 < 5)))
			return (VEC_INIT(0.0, 0.0, 0.0));
	}
	if ((inter.obj_coord.x > 0 && inter.obj_coord.z < 0) ||
		(inter.obj_coord.x < 0 && inter.obj_coord.z > 0))
	{
		if ((int)fabs(inter.obj_coord.x) % 10 >= 5 &&
			((int)fabs(inter.obj_coord.z) % 10 < 5))
			return (VEC_INIT(0.0, 0.0, 0.0));
		if ((int)fabs(inter.obj_coord.x) % 10 < 5 &&
			((int)fabs(inter.obj_coord.z) % 10 >= 5))
			return (VEC_INIT(0.0, 0.0, 0.0));
	}
	return (inter.obj->color);
}

t_vec		chess(t_inter inter)
{
	if ((inter.obj_coord.x < 0 && inter.obj_coord.y < 0)
		|| (inter.obj_coord.x > 0 && inter.obj_coord.y > 0))
	{
		if ((int)fabs(inter.obj_coord.x) % 10 < 5
			&& ((int)fabs(inter.obj_coord.y) % 10 < 5))
			return (VEC_INIT(0.0, 0.0, 0.0));
		if (!((int)fabs(inter.obj_coord.x) % 10 < 5
			|| ((int)fabs(inter.obj_coord.y) % 10 < 5)))
			return (VEC_INIT(0.0, 0.0, 0.0));
	}
	if ((inter.obj_coord.x > 0 && inter.obj_coord.y < 0)
		|| (inter.obj_coord.x < 0 && inter.obj_coord.y > 0))
	{
		if ((int)fabs(inter.obj_coord.x) % 10 >= 5
			&& ((int)fabs(inter.obj_coord.y) % 10 < 5))
			return (VEC_INIT(0.0, 0.0, 0.0));
		if ((int)fabs(inter.obj_coord.x) % 10 < 5
			&& ((int)fabs(inter.obj_coord.y) % 10 >= 5))
			return (VEC_INIT(0.0, 0.0, 0.0));
	}
	return (inter.obj->color);
}

t_vec		marble1(t_float t, t_inter inter)
{
	t_float	x;
	t_vec	color;

	x = 0.0;
	color = VEC_INIT(0.0, 0.0, 0.0);
	x = sin(inter.obj_coord[0]
		+ cos(inter.obj_coord[1] + 8.0 * t * M_PI) + 6.0 * t * M_PI);
	x = sqrt(x + 1) * 0.7071;
	color.y = (0.7 + 0.7 * x) * inter.obj->color.y;
	x = sqrt(x);
	color.x = (0.7 + 0.3 * x) * inter.obj->color.x;
	color.z = (0.3 + 0.8 * x) * inter.obj->color.z;
	return (color);
}

t_vec		marble2(t_float t, t_inter inter)
{
	t_float	x;
	t_vec	color;

	x = sin(inter.obj_coord[0] + 3.0 * t * M_PI);
	x = sqrt(x + 1) * 0.7071;
	color.y = (0.7 + 0.7 * x) * inter.obj->color.y;
	x = sqrt(x);
	color.x = (0.7 + 0.3 * x) * inter.obj->color.x;
	color.z = (0.3 + 0.8 * x) * inter.obj->color.z;
	return (color);
}
