/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:58:26 by valentin          #+#    #+#             */
/*   Updated: 2018/04/18 14:16:56 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "rt.h"

t_vec	camera_get_origin(t_rt *rt)
{
	return (rt->camera.origin);
}

t_vec	camera_get_angle(t_rt *rt)
{
	return (rt->camera.angle);
}

t_float	camera_get_fov(t_rt *rt)
{
	return (rt->camera.fov);
}
