/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:09:01 by vparis            #+#    #+#             */
/*   Updated: 2018/05/04 00:38:48 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "rt.h"
#include "objects.h"

t_parse_type	*get_parse_funs(void)
{
	static t_parse_type	parse_type[] = {
		ADD_TYPE(width, 1, "0"), ADD_TYPE(height, 1, "0"),
		ADD_TYPE(background, 3, "0"), ADD_TYPE(fov, 1, "1"),
		ADD_TYPE(ang, 3, "1"), ADD_TYPE(origin, 3, "1"),
		ADD_TYPE(pos, 3, "2 3 4 5 6 7 8 9 10 12"),
		ADD_TYPE(dir, 3, "13"),
		ADD_TYPE(side, 1, "9 10"),
		ADD_TYPE(radius, 1, "3 4 5 6 7 8 9 10"),
		ADD_TYPE(color, 3, "2 3 4 5 6 7 8 9 10"),
		ADD_TYPE(intensity, 3, "11 12 13"),
		ADD_TYPE(phong, 3, "2 3 4 5 6 7 8 9 10"),
		ADD_TYPE(texture, 5, "3"),
		ADD_TYPE(reflexion, 1, "2 3 4 5 6 7 8 9 10"),
		ADD_TYPE(refraction, 1, "2 3 4 5 6 7 8 9 10"),
		ADD_TYPE(transparency, 1, "2 3 4 5 6 7 8 9 10"),
		ADD_TYPE(perturbation, 1, "2 3 4 5 6 7 8 9 10"),
		ADD_TYPE(rot, 3, "2 3 4 5 6 7 8 9 10"),
		ADD_TYPE(limited, 7, "2 3 4 5 6 7 8 9 10"),
		{NULL, NULL, NULL, 0}};

	return (parse_type);
}

static int		check_counter_details(int counter[OBJECT_DETAILS_SIZE],
									int type)
{
	int				i;
	int				n;
	t_parse_type	*types;

	i = 0;
	n = 0;
	types = get_parse_funs();
	while (types[i].name != NULL)
	{
		if (check_line_object(types[i].types, type) == SUCCESS)
		{
			if (counter[i] != 1)
				return (ERROR);
			n += 1;
		}
		i++;
	}
	return (n == 0 ? ERROR : SUCCESS);
}

static int		parse_global_need_space(int *i, int type, t_object **obj,
					int counter[OBJECT_DETAILS_SIZE])
{
	ft_bzero(counter, OBJECT_DETAILS_SIZE * sizeof(int));
	if (type == CANVAS || type == CAMERA)
		*obj = NULL;
	else if ((*obj = object_new(type)) == NULL)
		return (ERROR);
	*i = 0;
	return (SUCCESS);
}

int				parse_global(t_rt *env, char **str, int type)
{
	int				i;
	int				r;
	t_object		*obj;
	char			**tmp;
	int				counter[OBJECT_DETAILS_SIZE];

	if (parse_global_need_space(&i, type, &obj, counter) == ERROR)
		return (-1);
	while (*(str + i) != NULL)
	{
		if ((tmp = check_line(*(str + i), type, &r)) == NULL)
			break ;
		if (counter[r] == 1 || parse_details(env, r, tmp[1], obj) == ERROR)
		{
			ft_strsplit_free(tmp);
			free(obj);
			return (-1);
		}
		counter[r] += 1;
		ft_strsplit_free(tmp);
		i++;
	}
	if (obj != NULL)
		object_add(&(env->objects), obj);
	return (check_counter_details(counter, type) == SUCCESS ? i : -1);
}
