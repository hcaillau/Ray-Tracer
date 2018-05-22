/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:38:48 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 17:15:18 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "types.h"

t_vec		color_to_vec(t_color c)
{
	t_vec	color;

	color = VEC_INIT(
		(t_float)((c & (0xFF << 16)) >> 16) / 255.0,
		(t_float)((c & (0xFF << 8)) >> 8) / 255.0,
		(t_float)(c & 0xFF) / 255.0);
	return (color);
}
