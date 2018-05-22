/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:01:46 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 17:38:10 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef unsigned long	t_id;
typedef unsigned int	t_color;

typedef int				t_int;
typedef unsigned int	t_uint;
typedef double			t_float;
typedef t_float			t_vec __attribute__((ext_vector_type(4),aligned(32)));

/*
** types.c
*/

t_id					gen_id(void);
t_color					rgb_to_color(t_uint r, t_uint g, t_uint b);
t_color					vec_to_color(t_vec color);
void					get_fps(int show_fps, int refresh);

#endif
