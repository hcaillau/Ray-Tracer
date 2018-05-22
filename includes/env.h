/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 23:03:33 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "types.h"
# include "objects.h"
# include "rt.h"
# include "ft_tpool.h"
# include "SDL.h"
# include "sdl_m.h"

# define THREADS		8
# define TASKS			32

typedef struct		s_env {
	t_tpool			*tp;
	t_sdl			sdl;
	t_rt			rt;
	int				show_fps;
	int				mode;
	t_float			speed_ang;
	t_float			speed_pos;
	t_object		*obj_edit;
}					t_env;

int					env_init(t_env *env, char *filename);
void				env_destroy(t_env *env);
void				loop(t_env *env);

/*
** bind.c
*/

int					manage_binds(SDL_Event *event, t_env *env, int *update);

/*
** bind_keyup.c
*/

int					manage_binds_up(SDL_Event *event, t_env *env, int *update);

/*
** bind_keydown.c
*/

int					manage_binds_down(t_env *env, int *update,
						const Uint8 *state);
int					manage_object(t_env *env, const Uint8 *state);

/*
** bind_mouse.c
*/

int					manage_binds_mouse(SDL_Event *event, t_env *env);

#endif
