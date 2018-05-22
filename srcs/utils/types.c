/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:47:21 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 17:38:26 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include "types.h"
#include "libft.h"
#include "vec.h"

t_color		rgb_to_color(t_uint r, t_uint g, t_uint b)
{
	t_color	c;

	c = 0;
	c |= (b & 0xFF);
	c |= (g & 0xFF) << 8;
	c |= (r & 0xFF) << 16;
	return (c);
}

t_color		vec_to_color(t_vec color)
{
	t_uint	x;
	t_uint	y;
	t_uint	z;

	x = (unsigned char)(clamp_f32(color[0], 0.0, 1.0) * 255.);
	y = (unsigned char)(clamp_f32(color[1], 0.0, 1.0) * 255.);
	z = (unsigned char)(clamp_f32(color[2], 0.0, 1.0) * 255.);
	return (rgb_to_color(x, y, z));
}

/*
** Takes the array id, return unique ID
*/

t_id		gen_id(void)
{
	struct timeval	t;
	t_id			id;
	t_id			u_id;

	u_id = (t_id)rand();
	gettimeofday(&t, NULL);
	id = ((t.tv_sec * 1000 * 1000) + (t.tv_usec * 1000)) << 42;
	id |= (u_id % 16777216) << 24;
	return (id);
}

void		get_fps(int show_fps, int refresh)
{
	static struct timeval	last = {0, 0};
	double					fps;
	struct timeval			new;

	if (show_fps == 0)
		return ;
	gettimeofday(&new, NULL);
	if (refresh == 1)
	{
		fps = (new.tv_sec - last.tv_sec) * 1000 + (new.tv_usec - last.tv_usec)
			/ 1000.;
		ft_putstr("FPS : ");
		ft_putnbr((int)(1000. / fps));
		ft_putchar('\n');
	}
	last.tv_usec = new.tv_usec;
	last.tv_sec = new.tv_sec;
}
