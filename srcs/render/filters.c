/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:00:47 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 15:14:33 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "types.h"
#include "env.h"
#include "rt.h"
#include "vec.h"

t_vec	apply_filter(t_rt *rt, t_vec color)
{
	if (rt->blackwhite)
	{
		color = color * VEC_INIT(0.21, 0.72, 0.07);
		color[0] = color[0] + color[1] + color[2];
		color[1] = color[0];
		color[2] = color[0];
	}
	else if (rt->sepia)
	{
		color = VEC_INIT(
			0.393 * color[0] + 0.769 * color[1] + 0.189 * color[2],
			0.349 * color[0] + 0.686 * color[1] + 0.168 * color[2],
			0.272 * color[0] + 0.534 * color[1] + 0.131 * color[2]);
	}
	return (color);
}
