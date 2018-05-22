/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:29:52 by hcaillau          #+#    #+#             */
/*   Updated: 2018/05/03 22:34:14 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_perlin	*ft_setup_i(t_perlin *l, double *vec, int i)
{
	double	t;

	t = vec[i] + N;
	l->b_tmp[i][0] = ((int)t) & BM;
	l->b_tmp[i][1] = (l->b_tmp[i][0] + 1) & BM;
	l->r[i][0] = t - (int)t;
	l->r[i][1] = l->r[i][0] - 1.;
	return (l);
}

t_perlin	*ft_setup(t_perlin *l, double *vec)
{
	l = ft_setup_i(l, vec, 0);
	l = ft_setup_i(l, vec, 1);
	l = ft_setup_i(l, vec, 2);
	return (l);
}

double		s_curve(double t)
{
	return (t * t * (3. - 2. * t));
}

double		at3(double rx, double ry, double rz, double *q)
{
	return ((rx * q[0] + ry * q[1] + rz * q[2]));
}

double		lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}
