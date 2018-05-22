/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_queue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:46:39 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 14:45:51 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "objects.h"

t_object	*object_new(int type)
{
	t_object	*tmp;

	if ((tmp = (t_object *)malloc(sizeof(t_object))) == NULL)
		return (NULL);
	ft_bzero(tmp, sizeof(t_object));
	tmp->type = type;
	tmp->id = gen_id();
	return (tmp);
}

int			object_add(t_objects *objects, t_object *object)
{
	t_obj_lst	*tmp;

	if ((tmp = (t_obj_lst *)malloc(sizeof(t_obj_lst))) == NULL)
		return (ERROR);
	tmp->object = object;
	tmp->next = objects->objects_lst;
	objects->objects_lst = tmp;
	objects->size += 1;
	objects->is_update = 1;
	return (SUCCESS);
}

int			object_del(t_objects *objects, t_id id)
{
	t_obj_lst	*iter;
	t_obj_lst	*tmp;

	tmp = NULL;
	iter = objects->objects_lst;
	while (iter != NULL && iter->object->id != id)
	{
		tmp = iter;
		iter = iter->next;
	}
	if (iter == NULL)
		return (ERROR);
	if (tmp == NULL)
		objects->objects_lst = iter->next;
	else
		tmp->next = iter->next;
	objects->size -= 1;
	objects->is_update = 1;
	free(iter);
	return (SUCCESS);
}

t_object	*object_get(t_objects *objects, t_id id)
{
	t_obj_lst	*iter;

	iter = objects->objects_lst;
	while (iter != NULL && iter->object->id != id)
		iter = iter->next;
	if (iter == NULL)
		return (NULL);
	return (iter->object);
}
