/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/23 17:58:26 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	pixel_vp_init(t_grid *g, t_env *e)
{
	g->xx = g->x;
	g->yy = g->y;
	g->vpx = v_double_mult(&e->camera.x_vector, g->x);
	g->vpy = v_double_mult(&e->camera.y_vector, g->y);
	g->vp_point = v_v_add(&e->viewplane_point_up_left, &g->vpx);
	g->vp_point = v_v_subs(&g->vp_point, &g->vpy);
	e->camera.rayon = v_v_subs(&g->vp_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
}

void	pxl_tracer(t_env *e, int sample)
{
	t_grid		g;
	t_color		color;

	g.y = e->begin;
	while (g.y < e->fin)
	{
		g.x = 0;
		while (g.x < e->width)
		{
			e->rebound = e->recursion;
			color = set_color(0, 0, 0);
			pixel_vp_init(&g, e);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				color = get_render_mode(e);
			while (g.y++ < g.yy + sample)
			{
				g.x = g.x != g.xx ? g.x - sample : g.x;
				while (g.x < g.xx + sample)
					print_color(&color, e, g.x++, g.y);
			}
			g.y = g.yy;
		}
		g.y += sample;
	}
}

void	*stereo_tracer_void(void *e)
{
	stereo_tracer(e);
	return (NULL);
}
