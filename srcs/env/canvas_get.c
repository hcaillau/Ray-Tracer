/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:29:16 by valentin          #+#    #+#             */
/*   Updated: 2018/04/18 14:19:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "rt.h"

int		canvas_get_width(t_rt *rt)
{
	return (rt->canvas.width);
}

int		canvas_get_height(t_rt *rt)
{
	return (rt->canvas.height);
}

t_vec	canvas_get_bg_color(t_rt *rt)
{
	return (rt->canvas.bg_color);
}
