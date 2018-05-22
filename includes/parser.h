/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:29:55 by valentin          #+#    #+#             */
/*   Updated: 2018/05/03 22:33:16 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rt.h"
# include "objects.h"

/*
** Max map filsize : 4Mo
*/

# define BUFF_SIZE				(4 * 1024 * 1024)
# define BUFF_READ				4096

/*
** Max numbers
*/

# define OBJECT_SIZE			32
# define OBJECT_DETAILS_SIZE	32

/*
** Tokens
*/

# define T_COMMENT		'#'
# define T_OPEN			'{'
# define T_CLOSE		'}'
# define T_SEPAR		'='

# define ADD_OBJECT(obj, req)		{#obj, (obj), (req)}
# define ADD_TYPE(type, args, req)	{#type, &parse_t_ ## type, req, (args)}

typedef struct	s_parse_type {
	char		*name;
	int			(*f)(void *data, char **strs);
	char		*types;
	size_t		size;
}				t_parse_type;

typedef struct	s_parse_objects {
	char		*name;
	int			id;
	int			required;
}				t_parse_objects;

/*
** reader.c
*/

int				check_map(char *str);
char			*read_map(char *filename);
char			**cut_map(char *map);
int				trim_content(char **dest);

/*
** parser.c
*/

int				parse_file(t_rt *rt, char **file);
char			**read_file(char *filename);

/*
** parse_data.c
*/

int				parse_data(t_rt *rt, char **data);

/*
** parse_type.c & parse_type_2.c
*/

t_parse_type	*get_parse_funs(void);
int				parse_global(t_rt *rt, char **str, int type);
int				check_line_object(char *lst, int type);
char			**check_line(char *str, int type, int *r);

/*
** parse_details.c
*/

int				parse_details(t_rt *rt, int id, char *line, t_object *obj);

/*
** parse_funsX.c
*/

int				parse_t_width(void *data, char **strs);
int				parse_t_height(void *data, char **strs);
int				parse_t_background(void *data, char **strs);
int				parse_t_ang(void *data, char **strs);
int				parse_t_origin(void *data, char **strs);
int				parse_t_fov(void *data, char **strs);
int				parse_t_pos(void *data, char **strs);
int				parse_t_dir(void *data, char **strs);
int				parse_t_radius(void *data, char **strs);
int				parse_t_color(void *data, char **strs);
int				parse_t_intensity(void *data, char **strs);
int				parse_t_phong(void *data, char **strs);
int				parse_t_reflexion(void *data, char **strs);
int				parse_t_refraction(void *data, char **strs);
int				parse_t_transparency(void *data, char **strs);
int				parse_t_perturbation(void *data, char **strs);
int				parse_t_rot(void *data, char **strs);
int				parse_t_side(void *data, char **strs);
int				parse_t_limited(void *data, char **strs);
int				parse_t_texture(void *data, char **strs);

#endif
