/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:04:33 by hcaillau          #+#    #+#             */
/*   Updated: 2018/05/03 19:21:25 by mcasubol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

static t_vec	get_text_color(t_obj_text *text, int coord)
{
	t_vec		color;

	coord = coord * text->format;
	color = VEC_INIT(
		(t_float)text->pixels[coord] / 255.0,
		(t_float)text->pixels[coord + 1] / 255.0,
		(t_float)text->pixels[coord + 2] / 255.0);
	return (color);
}

static t_vec	uv_mapping(t_inter inter)
{
	t_vec		ret;

	ret = VEC_INIT(0.0, 0.0, 0.0);
	if (inter.obj->type == SPHERE)
		ret = map_sphere(inter.obj_coord);
	return (ret);
}

static int		uv_to_texture_coord(t_vec px, t_obj_text t)
{
	int			coord;
	t_float		u;
	t_float		v;

	u = (t_float)t.width * px.x;
	v = (t_float)t.height * px.y;
	if (t.scale.x > 0.0)
		u /= t.scale.x;
	if (t.scale.y > 0.0)
		v /= t.scale.y;
	if (t.off.x > 0.0 || t.off.y > 0.0)
	{
		u += t.off.x * (t_float)t.width;
		v += t.off.y * (t_float)t.height;
	}
	coord = (int)u + (int)v * t.width;
	coord = coord % (t.width * t.height);
	return (coord);
}

t_vec			texture_color(t_inter inter)
{
	t_vec		color;
	t_vec		px;
	int			coord;

	px = uv_mapping(inter);
	coord = uv_to_texture_coord(px, inter.obj->texture);
	color = get_text_color(&inter.obj->texture, coord);
	return (color);
}
