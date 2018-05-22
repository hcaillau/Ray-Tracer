/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_set3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:56:49 by valentin          #+#    #+#             */
/*   Updated: 2018/05/03 17:15:16 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "objects.h"
#include "types.h"
#include "vec.h"
#include "sdl_m.h"

int		object_set_reflexion(t_object *obj, t_float n)
{
	obj->reflexion = clamp_f64(n, 0.0, 1.0);
	return (SUCCESS);
}

int		object_set_refraction(t_object *obj, t_float n)
{
	obj->refraction = clamp_f64(n, 0.0, 10.0);
	return (SUCCESS);
}

int		object_set_transparency(t_object *obj, t_float n)
{
	obj->transparency = clamp_f64(n, 0.0, 1.0);
	return (SUCCESS);
}

int		object_set_perturbation(t_object *obj, int n)
{
	if (n < 0 || n > 10)
		return (ERROR);
	obj->perturbation = n;
	return (SUCCESS);
}

int		object_set_texture(t_object *obj, int n)
{
	SDL_Surface	*surf;

	if (n < 0 || n > 10)
		return (ERROR);
	if (n == 0)
		obj->texture.pixels = NULL;
	else
	{
		surf = sdl_get_texture(n - 1);
		obj->texture.pixels = (t_u8 *)surf->pixels;
		obj->texture.width = surf->w;
		obj->texture.height = surf->h;
		obj->texture.format = surf->format->BytesPerPixel;
	}
	return (SUCCESS);
}
