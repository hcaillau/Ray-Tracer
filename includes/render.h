/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:52:10 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 22:54:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"
# include "env.h"

# define FLOAT_ZERO			0.0
# define FLOAT_MAX			1e6
# define FLOAT_MIN			1e-5
# define BIAIS				1e-6
# define MAX_DEPTH			4
# define REFRACTION_DEFAULT	1.0
# define POW(x) ((x)*(x))
# define B 0x100
# define BM 0xff
# define N 0x1000

typedef	struct		s_perlin
{
	int				b_tmp[3][2];
	double			r[3][2];
	double			tab_2[3];
	int				*p;
	int				**b;
	double			*tab;
}					t_perlin;

typedef struct		s_algo {
	t_env			*env;
	int				start;
	int				end;
}					t_algo;

typedef struct		s_inter {
	t_float			t;
	t_float			t2[2];
	t_object		*obj;
	t_vec			point;
	t_vec			obj_coord;
	t_vec			point_biais;
	t_vec			normal;
}					t_inter;

typedef struct		s_ray {
	t_vec			origin;
	t_vec			dir;
	t_float			refraction;
}					t_ray;

typedef struct		s_hit {
	t_ray			ray;
	t_inter			inter;
}					t_hit;

void				render_compute(t_env *env);
int					render_update(t_env *env);
int					rt(void *data);
t_object			*get_hit_object(t_rt *rt, int x, int y);
void				compute_primary_ray(int x, int y, t_rt *rt, t_ray *ray);
t_vec				apply_filter(t_rt *rt, t_vec color);

/*
** inter
*/

int					trace(t_rt *rt, t_hit *hit, t_float max_inter);
void				compute_hit_normal(t_ray *ray, t_inter *inter);
void				compute_hit_biais(t_inter *inter);

t_float				solve_quadra(t_float abc[3], t_inter *inter);

t_float				intersect_sphere(t_ray *ray, t_object *obj, t_float *t,
						t_inter *inter);
void				norm_sphere(t_ray *ray_hit, t_object *obj, t_inter *inter);

t_float				intersect_plane(t_ray *ray, t_object *obj, t_float *t,
						t_inter *inter);
void				norm_plane(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_cone(t_ray *ray, t_object *obj, t_float *t,
						t_inter *inter);
void				norm_cone(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_cylinder(t_ray *ray, t_object *obj, t_float *t,
						t_inter *inter);
void				norm_cylinder(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_paraboloid(t_ray *ray, t_object *obj, t_float *t,
						t_inter *inter);
void				norm_paraboloid(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_hyperboloid(t_ray *ray, t_object *obj,
						t_float *t, t_inter *inter);
void				norm_hyperboloid(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_limited_planes(t_ray *ray, t_object *obj,
						t_float *t, t_inter *inter);

t_vec				compute_color(t_rt *rt, t_hit *hit, int depth);

int					is_cut(t_object *obj, t_hit *hit, t_float *t,
						t_ray *simple);

/*
** Light effect : reflexion and refraction
*/

t_ray				reflected_ray(t_inter inter, t_vec ray);
t_vec				reflexion(t_rt *rt, t_hit *hit, int depth);

t_vec				refract(t_rt *rt, t_hit *hit, int depth);
t_ray				refract_ray(t_ray ray, t_inter inter);
t_float				fresnel(t_ray ray, t_inter inter);

/*
** Compute light intensity
*/

t_vec				light(t_inter it, t_vec v, t_rt *rt);
t_float				diffuse_light(t_ray *r, t_inter it, int *j, t_rt *rt);
t_vec				light_specular(t_inter it, t_vec i[4], t_vec v, t_ray *r);
void				surface_color(t_hit *hit, t_vec intensity, t_vec *color);
void				light_effect(t_hit *hit, t_vec *color, int depth, t_rt *rt);
t_vec				specular(t_hit *hit, t_vec reflect_ray,
						t_vec intensity_local, t_float dot);
t_float				transparent_shadow(t_inter inter, t_ray rayon, t_rt *rt);

/*
** Perturbations
*/

t_vec				color_perturbation(t_inter inter);
t_vec				marble1(t_float t, t_inter inter);
t_vec				marble2(t_float t, t_inter inter);
t_vec				normal_perturbation(t_inter	inter);
t_vec				chess(t_inter inter);
t_vec				chess_plane(t_inter inter);
t_vec				normal_perturbation(t_inter	inter);
t_vec				water_perturbation(t_vec n, t_inter inter);
t_vec				wave_perturbation(t_vec n, t_inter inter);
double				noise3(double vec[3]);
t_perlin			*ft_init(t_perlin *l, double g3[B + B + 2][3]);
t_perlin			*ft_q(t_perlin *l, int m, int n, double g3[B + B + 2][3]);
double				*ft_q_all(t_perlin *l, double sy, double g3[B + B + 2][3]);
int					**ft_b(t_perlin *l);
t_perlin			*ft_setup_i(t_perlin *l, double *vec, int i);
t_perlin			*ft_setup(t_perlin *l, double *vec);
double				s_curve(double t);
double				at3(double rx, double ry, double rz, double *q);
double				lerp(double t, double a, double b);
void				ft_free_bl(t_perlin *l, int **b);
double				ft_lerp(double s1, double *tab);
t_perlin			*ft_rndm(t_perlin *l, double g3[B + B + 2][3], int i);
int					*ft_init_p(t_perlin *l, int i, int j, int k);

/*
** Textures
*/

t_vec				map_sphere(t_vec inter);
t_vec				texture_color(t_inter inter);

#endif
