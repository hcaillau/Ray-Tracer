/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_set2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:56:49 by valentin          #+#    #+#             */
/*   Updated: 2018/05/02 19:13:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "objects.h"
#include "types.h"
#include "vec.h"

int		object_set_radius(t_object *obj, t_float n)
{
	obj->radius = clamp_f64(n, 0.001, 10000.0);
	obj->radius2 = obj->radius * obj->radius;
	return (SUCCESS);
}

int		object_set_matrix(t_object *obj, t_vec rot)
{
	t_vec	x[3];
	t_vec	y[3];
	t_vec	z[3];
	t_vec	tmp[3];
	t_vec	matrix[3];

	obj->rot = rot;
	matrix_id(matrix);
	matrix_id(tmp);
	matrix_rotz(z, rot.z);
	matrix_roty(y, rot.y);
	matrix_rotx(x, rot.x);
	matrix_mul_matrix(z, y, tmp);
	matrix_mul_matrix(x, tmp, matrix);
	matrix_equal_matrix(obj->obj_to_w, matrix);
	inverse_matrix(obj->obj_to_w, obj->w_to_obj);
	matrix_mul_matrix(obj->obj_to_w, obj->w_to_obj, matrix);
	return (SUCCESS);
}
