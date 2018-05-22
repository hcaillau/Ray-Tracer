/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:16:18 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 19:48:29 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "objects.h"
#include "env.h"
#include "rt.h"
#include "render.h"

t_object	*get_hit_object(t_rt *rt, int x, int y)
{
	t_hit	cam;
	t_id	id;

	id = 0;
	compute_primary_ray(x, y, rt, &cam.ray);
	if (trace(rt, &cam, FLOAT_MAX) == SUCCESS)
		id = cam.inter.obj->id;
	else
		return (NULL);
	return (object_get(&rt->objects, id));
}

int			render_update(t_env *env)
{
	if (objects_gen_array(&(env->rt.objects)) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
