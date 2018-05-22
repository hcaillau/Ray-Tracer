/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:43:13 by vparis            #+#    #+#             */
/*   Updated: 2018/05/01 17:38:52 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include "types.h"

/*
** Max map filsize : 4Mo
*/

# define BMP_BUFF		4096
# define FILE_NAME		"saved_img/rt_XXX.bmp"

int				write_header(int fd, int size[2]);
int				write_dibheader(int fd, int size[2]);
int				write_img(int fd, int size[2], t_color *map);
void			write_int(int fd, int n, int bytes);
int				save_img(t_color *image, int width, int height);

#endif
