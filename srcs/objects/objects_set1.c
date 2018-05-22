/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_set1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:56:49 by valentin          #+#    #+#             */
/*   Updated: 2018/04/27 15:29:13 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "objects.h"
#include "types.h"
#include "vec.h"

int		object_set_pos(t_object *obj, t_vec pos)
{
	obj->pos = pos;
	return (SUCCESS);
}

int		object_set_dir(t_object *obj, t_vec dir)
{
	obj->dir = dir;
	obj->dir = vec_norm(obj->dir);
	return (SUCCESS);
}

int		object_set_intensity(t_object *obj, t_vec intensity)
{
	obj->intensity = VEC_INIT(
		clamp_f64(intensity[0], 0.0, 10.0),
		clamp_f64(intensity[1], 0.0, 10.0),
		clamp_f64(intensity[2], 0.0, 10.0));
	return (SUCCESS);
}

int		object_set_color(t_object *obj, t_vec color)
{
	obj->color = VEC_INIT(
		(t_float)clamp_i32(color[0], 0, 255) / 255.0,
		(t_float)clamp_i32(color[1], 0, 255) / 255.0,
		(t_float)clamp_i32(color[2], 0, 255) / 255.0);
	return (SUCCESS);
}

int		object_set_phong(t_object *obj, t_float phong[PHONGS])
{
	obj->phong[PHONG_SHINI] = round(
								clamp_f64(phong[PHONG_SHINI], 0.0, 1200.0));
	obj->phong[PHONG_KD] = clamp_f64(phong[PHONG_KD], 0.0, 1.0);
	obj->phong[PHONG_KS] = clamp_f64(phong[PHONG_KS], 0.0, 1.0);
	return (SUCCESS);
}
