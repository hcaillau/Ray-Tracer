/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:31:17 by valentin          #+#    #+#             */
/*   Updated: 2018/05/03 22:32:30 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "rt.h"

int			trim_content(char **dest)
{
	char	*tmp;

	if ((tmp = ft_strtrim(*dest)) == NULL)
		return (ERROR);
	free(*dest);
	*dest = tmp;
	return (SUCCESS);
}

int			parse_file(t_rt *env, char **file)
{
	if (parse_data(env, file) == ERROR)
	{
		ft_putendl("Invalid file");
		return (ERROR);
	}
	return (SUCCESS);
}

char		**read_file(char *filename)
{
	char	*map_str;
	char	**map_cut;

	if (check_map(filename) == ERROR)
	{
		ft_putendl("Invalid file");
		return (NULL);
	}
	if ((map_str = read_map(filename)) == NULL)
		return (NULL);
	map_cut = cut_map(map_str);
	free(map_str);
	if (map_cut == NULL)
		return (NULL);
	return (map_cut);
}
