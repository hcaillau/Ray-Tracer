/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:19:51 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 19:14:17 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "objects.h"

int			object_is_light(t_object *object)
{
	return (object->type == LIGHT_AMBIENT || object->type == LIGHT_POINT
		|| object->type == LIGHT_PAR);
}

static void	object_fill_array(t_objects *objects, t_object *tmp)
{
	t_obj_lst	*iter;
	int			i;
	int			j;

	iter = objects_get_iter(objects);
	i = 0;
	j = objects->size - 1;
	while (iter != NULL)
	{
		if (object_is_light(iter->object))
		{
			ft_memcpy(&tmp[i], iter->object, sizeof(t_object));
			i++;
		}
		else
		{
			ft_memcpy(&tmp[j], iter->object, sizeof(t_object));
			j--;
		}
		iter = iter->next;
	}
}

int			objects_gen_array(t_objects *objects)
{
	if (objects->is_update == 0)
		return (SUCCESS);
	objects->is_update = 0;
	if (objects->objects_array != NULL)
		free(objects->objects_array);
	if ((objects->objects_array =
		(t_object *)malloc(objects->size * sizeof(t_object))) == NULL)
		return (ERROR);
	object_fill_array(objects, objects->objects_array);
	objects->last_size = objects->size;
	return (SUCCESS);
}
