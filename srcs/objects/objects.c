/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:46:39 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 23:42:31 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "objects.h"

void		objects_init(t_objects *objects)
{
	ft_bzero(objects, sizeof(t_objects));
}

void		objects_destroy(t_objects *objects)
{
	t_obj_lst	*iter;
	t_obj_lst	*tmp;

	iter = objects->objects_lst;
	while (iter != NULL)
	{
		tmp = iter->next;
		free(iter->object);
		free(iter);
		iter = tmp;
	}
	objects->objects_lst = NULL;
	objects->size = 0;
	if (objects->objects_array != NULL)
	{
		free(objects->objects_array);
		objects->objects_array = NULL;
	}
}

t_obj_lst	*objects_get_iter(t_objects *objects)
{
	return (objects->objects_lst);
}
