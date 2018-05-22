/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:10:06 by valentin          #+#    #+#             */
/*   Updated: 2018/05/04 00:07:04 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_math.h"
#include "libft.h"
#include "rt.h"
#include "parser.h"
#include "vec.h"

static void	set_ratio(t_rt *rt)
{
	if (rt->canvas.width > rt->canvas.height)
	{
		rt->canvas.ratio[0] =
		(t_float)rt->canvas.width / (t_float)rt->canvas.height;
		rt->canvas.ratio[1] = 1.0;
	}
	else if (rt->canvas.height > rt->canvas.width)
	{
		rt->canvas.ratio[0] = 1.0;
		rt->canvas.ratio[1] =
		(t_float)rt->canvas.height / (t_float)rt->canvas.width;
	}
	else
	{
		rt->canvas.ratio[0] = 1.0;
		rt->canvas.ratio[1] = 1.0;
	}
	rt->canvas.ratio[0] *= ft_tan(rt->camera.fov / 2.0);
	rt->canvas.ratio[1] *= ft_tan(rt->camera.fov / 2.0);
	rt->canvas_update = 1;
}

int			rt_reload(t_rt *rt)
{
	t_rt	tmp;

	if (rt_init(&tmp, rt->filename) == ERROR)
	{
		ft_putstr("Error : can't reload rt\n");
		return (ERROR);
	}
	rt_destroy(rt);
	ft_memcpy(rt, &tmp, sizeof(t_rt));
	return (SUCCESS);
}

/*
** Init all env at 0, init random, and parse file
*/

int			rt_init(t_rt *rt, char *filename)
{
	char	**file;

	ft_bzero(rt, sizeof(t_rt));
	if ((rt->filename = ft_strdup(filename)) == NULL)
		return (ERROR);
	objects_init(&rt->objects);
	if ((file = read_file(filename)) == NULL)
	{
		free(rt->filename);
		return (ERROR);
	}
	if (parse_file(rt, file) == ERROR)
	{
		ft_strsplit_free(file);
		free(rt->filename);
		return (ERROR);
	}
	set_ratio(rt);
	matrix_init_value();
	objects_gen_array(&rt->objects);
	ft_strsplit_free(file);
	return (SUCCESS);
}

/*
** Reset rt
*/

int			rt_destroy(t_rt *rt)
{
	objects_destroy(&rt->objects);
	free(rt->filename);
	ft_bzero(rt, sizeof(t_rt));
	return (SUCCESS);
}
