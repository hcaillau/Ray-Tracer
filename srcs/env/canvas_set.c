/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:58:26 by valentin          #+#    #+#             */
/*   Updated: 2018/05/04 00:33:05 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "rt.h"

int		canvas_set_width(t_rt *rt, int width)
{
	if (width < 128 || width > 4096)
		return (ERROR);
	rt->canvas_update = 1;
	rt->canvas.width = width;
	rt->canvas.size = width * rt->canvas.height;
	return (SUCCESS);
}

int		canvas_set_height(t_rt *rt, int height)
{
	if (height < 128 || height > 2160)
		return (ERROR);
	rt->canvas_update = 1;
	rt->canvas.height = height;
	rt->canvas.size = rt->canvas.width * height;
	return (SUCCESS);
}

int		canvas_set_bg_color(t_rt *rt, t_vec color)
{
	rt->canvas_update = 1;
	rt->canvas.bg_color = color;
	return (SUCCESS);
}
