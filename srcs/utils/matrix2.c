/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:35:58 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 19:37:12 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "ft_math.h"
#include <math.h>
#include "vec.h"

void			matrix_id(t_vec m[3])
{
	m[0] = VEC_INIT(1.0, 0.0, 0.0);
	m[1] = VEC_INIT(0.0, 1.0, 0.0);
	m[2] = VEC_INIT(0.0, 0.0, 1.0);
}

void			inverse_matrix(t_vec m[3], t_vec inv[3])
{
	t_float	det;
	t_vec	comat[3];
	t_vec	transpo[3];

	det = matrix_det(m);
	comatrix(m, comat);
	transpose_matrix(comat, transpo);
	inv[0] = (1.0 / det) * transpo[0];
	inv[1] = (1.0 / det) * transpo[1];
	inv[2] = (1.0 / det) * transpo[2];
}

void			transpose_matrix(t_vec m[3], t_vec tr[3])
{
	tr[0] = VEC_INIT(m[0][0], m[1][0], m[2][0]);
	tr[1] = VEC_INIT(m[0][1], m[1][1], m[2][1]);
	tr[2] = VEC_INIT(m[0][2], m[1][2], m[2][2]);
}

void			comatrix(t_vec m[3], t_vec ret[3])
{
	ret[0] = VEC_INIT(m[1][1] * m[2][2] - m[2][1] * m[1][2],
					m[1][2] * m[2][0] - m[1][0] * m[2][2],
					m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	ret[1] = VEC_INIT(m[2][1] * m[0][2] - m[0][1] * m[2][2],
					m[0][0] * m[2][2] - m[0][2] * m[2][0],
					m[0][1] * m[2][0] - m[0][0] * m[2][1]);
	ret[2] = VEC_INIT(m[0][1] * m[1][2] - m[1][1] * m[0][2],
					m[0][2] * m[1][0] - m[0][0] * m[1][2],
					m[0][0] * m[1][1] - m[0][1] * m[1][0]);
}

t_float			matrix_det(t_vec m[3])
{
	t_float	det;

	det = (m[0][0] * m[1][1] * m[2][2])
		+ (m[1][0] * m[2][1] * m[0][2])
		+ (m[2][0] * m[0][1] * m[1][2])
		- (m[0][2] * m[1][1] * m[2][0])
		- (m[1][2] * m[2][1] * m[0][0])
		- (m[2][2] * m[0][1] * m[1][0]);
	return (det);
}
