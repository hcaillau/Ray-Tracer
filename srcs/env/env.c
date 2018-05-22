/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:54:18 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 23:04:06 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "env.h"

#include "sdl_m.h"

int		env_init(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(t_env));
	srand(time(NULL));
	if (sdl_init_textures() == ERROR)
	{
		ft_putstr("Error : can't load textures\n");
		return (ERROR);
	}
	if (rt_init(&env->rt, filename) == ERROR)
	{
		ft_putstr("Error : can't init rt\n");
		return (ERROR);
	}
	if (sdl_init(&env->sdl, env->rt.canvas.width, env->rt.canvas.height)
		== ERROR)
	{
		ft_putstr("Error : can't init sdl\n");
		return (ERROR);
	}
	if ((env->tp = tp_create(THREADS, TP_ON_START)) == NULL)
		return (ERROR);
	env->speed_ang = 1.0;
	env->speed_pos = 2.0;
	return (SUCCESS);
}

void	env_destroy(t_env *env)
{
	sdl_destroy_textures();
	tp_destroy(&env->tp);
	sdl_destroy(&env->sdl);
	rt_destroy(&env->rt);
}
