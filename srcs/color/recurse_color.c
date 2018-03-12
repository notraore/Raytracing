/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:17:11 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 15:35:57 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	get_area_color(t_env *e)
{
	t_object	*area_light;
	t_vector	ray_current_range;
	double		current_range;
	double		indice;
	t_color		c;

	area_light = e->object;
	while (area_light->id != e->id_object)
		area_light = area_light->next;
	ray_current_range = v_v_subs(&area_light->center, &e->current_node);
	current_range = magnitude(&ray_current_range);
	indice = 1 - (current_range / area_light->range_max * 0.6);
	indice *= 1.6;
	indice = (indice > 1) ? 1 : indice;
	indice = (indice < 0.5) ? 0.5 : indice;
	c = set_color(1, 1, 1);
	return (c_double_mult(&c, indice));
}

void	fresnel(t_env *e, t_rayon ray, double *kr)
{
	t_physic pl;

	pl.cos1 = dot_product(&ray.rayon, &ray.normal);
	pl.etai = e->indice;
	pl.etat = e->object_indice;
	if (pl.cos1 > 0)
	{
		pl.etai = e->object_indice;
		pl.etat = e->indice;
	}
	pl.ior = pl.etai / pl.etat;
	pl.sin2 = pl.ior * sqrtf(1.0 - pl.cos1 * pl.cos1);
	if (pl.sin2 >= 1)
		*kr = 1;
	else
	{
		pl.cos2 = sqrtf(1.0 - pl.sin2 * pl.sin2);
		pl.cos1 = fabs(pl.cos1);
		pl.rs = ((pl.etat * pl.cos1) - (pl.etai * pl.cos2)) /
			((pl.etat * pl.cos1) + (pl.etai * pl.cos2));
		pl.rp = ((pl.etai * pl.cos1) - (pl.etat * pl.cos2)) /
			((pl.etai * pl.cos1) + (pl.etat * pl.cos2));
		*kr = (pl.rs * pl.rs + pl.rp * pl.rp) / 2;
	}
}

void	shoot_new_color(t_env *e, t_color *c, double coef)
{
	t_color shade;

	shade = get_color(e);
	shade = c_double_mult(&shade, coef);
	*c = c_c_add(c, &shade);
}

void	recurse_color(t_env *e, t_rayon ray, t_color *c)
{
	double	kr;

	while (--(e->rebound) > 0)
	{
		if (e->reflect && !e->refract)
		{
			if (cast_reflect_ray(e, ray))
				shoot_new_color(e, c, 1 - e->absorbtion);
		}
		else if (e->refract && !e->reflect)
		{
			if (cast_refract_ray(e, ray))
				shoot_new_color(e, c, 1 - e->absorbtion);
		}
		else if (e->reflect && e->refract)
		{
			fresnel(e, ray, &kr);
			if (kr < 1 && cast_refract_ray(e, ray))
				shoot_new_color(e, c, (1 - e->absorbtion) * (1 - kr));
			if (cast_reflect_ray(e, ray))
				shoot_new_color(e, c, (1 - e->absorbtion) * kr);
		}
	}
}
