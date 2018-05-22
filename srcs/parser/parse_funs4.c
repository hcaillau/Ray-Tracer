/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:12:06 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 19:13:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "ft_math.h"
#include "rt.h"
#include "objects.h"
#include "types.h"

int		parse_t_reflexion(void *data, char **strs)
{
	t_object	*obj;
	t_float		n;

	obj = (t_object *)data;
	if (ft_atof_s(strs[0], &n) == ERROR)
		return (ERROR);
	object_set_reflexion(obj, n);
	return (SUCCESS);
}

int		parse_t_refraction(void *data, char **strs)
{
	t_object	*obj;
	t_float		n;

	obj = (t_object *)data;
	if (ft_atof_s(strs[0], &n) == ERROR)
		return (ERROR);
	object_set_refraction(obj, n);
	return (SUCCESS);
}

int		parse_t_transparency(void *data, char **strs)
{
	t_object	*obj;
	t_float		n;

	obj = (t_object *)data;
	if (ft_atof_s(strs[0], &n) == ERROR)
		return (ERROR);
	object_set_transparency(obj, n);
	return (SUCCESS);
}
