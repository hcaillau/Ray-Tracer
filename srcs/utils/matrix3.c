/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:36:06 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 19:37:37 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "ft_math.h"
#include <math.h>
#include "vec.h"

void			matrix_rotx(t_vec ret[3], double teta)
{
	double	angle;

	angle = DEG_TO_RAD * teta;
	ret[0] = VEC_INIT(1.0, 0.0, 0.0);
	ret[1] = VEC_INIT(0.0, cos(angle), sin(angle));
	ret[2] = VEC_INIT(0.0, -sin(angle), cos(angle));
}

void			matrix_roty(t_vec ret[3], double teta)
{
	double	angle;

	angle = DEG_TO_RAD * teta;
	ret[0] = VEC_INIT(cos(angle), 0.0, -sin(angle));
	ret[1] = VEC_INIT(0.0, 1.0, 0.0);
	ret[2] = VEC_INIT(sin(angle), 0.0, cos(angle));
}

void			matrix_rotz(t_vec ret[3], double teta)
{
	double	angle;

	angle = DEG_TO_RAD * teta;
	ret[0] = VEC_INIT(cos(angle), sin(angle), 0.0);
	ret[1] = VEC_INIT(-sin(angle), cos(angle), 0.0);
	ret[2] = VEC_INIT(0.0, 0.0, 1.0);
}
