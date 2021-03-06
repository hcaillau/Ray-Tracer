/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:23:03 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 23:34:39 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "libft.h"
#include "sdl_m.h"

static int		sdl_init2(t_sdl *sdl, int width, int height)
{
	if ((sdl->window = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI)) == NULL)
	{
		ft_putstr("Window could not be created ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	if (sdl_create_screen(sdl, width, height) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int				sdl_init(t_sdl *sdl, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		ft_putstr("SDL could not initialize ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	if (sdl_init2(sdl, width, height) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int				sdl_reset(t_sdl *sdl)
{
	if (sdl->image != NULL)
	{
		free(sdl->image);
		sdl->image = NULL;
	}
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyRenderer(sdl->renderer);
	return (SUCCESS);
}

int				sdl_destroy(t_sdl *sdl)
{
	sdl_reset(sdl);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	return (SUCCESS);
}

int				sdl_render(t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->texture, NULL, (void *)sdl->image, sdl->size_line);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
	return (SUCCESS);
}
