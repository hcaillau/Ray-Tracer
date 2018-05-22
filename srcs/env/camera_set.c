/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:58:26 by valentin          #+#    #+#             */
/*   Updated: 2018/05/01 19:33:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "ft_math.h"
#include "types.h"
#include "vec.h"
#include "rt.h"

int		camera_set_origin(t_rt *rt, t_vec v)
{
	rt->camera_update = 1;
	rt->camera.origin = v;
	return (SUCCESS);
}

int		camera_set_angle(t_rt *rt, t_vec v)
{
	rt->camera_update = 1;
	rt->camera.angle = VEC_INIT(
		fmod(v[0], 360.0),
		fmod(v[1], 360.0),
		fmod(v[2], 360.0));
	return (SUCCESS);
}

int		camera_set_fov(t_rt *rt, t_float fov)
{
	if (fov < 30.0 || fov > 120.0)
		return (ERROR);
	rt->camera_update = 1;
	rt->camera.fov = fov;
	return (SUCCESS);
}

void	camera_set_rot(t_camera *cam)
{
	t_vec	x[3];
	t_vec	y[3];
	t_vec	z[3];
	t_vec	tmp[3];

	matrix_rotz(z, cam->angle.z);
	matrix_roty(y, cam->angle.y);
	matrix_rotx(x, cam->angle.x);
	matrix_mul_matrix(z, y, tmp);
	matrix_mul_matrix(tmp, x, cam->rot);
}
