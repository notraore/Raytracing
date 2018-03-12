/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:35:23 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/12/21 15:35:24 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		triangle_intersection(t_env *e, t_object *triangle, t_object *t)
{
	t_poly	p;

	p.v1_2 = v_v_subs(&t->point_2, &t->point);
	p.v1_3 = v_v_subs(&t->point_3, &t->point);
	p.v1_2 = normalize(&p.v1_2);
	p.v1_3 = normalize(&p.v1_3);
	triangle->normal = v_v_mult(&p.v1_2, &p.v1_3);
	if (!plane_intersection(e, triangle))
		return (0);
	p.v3_1 = v_v_subs(&t->point, &t->point_3);
	p.v2_3 = v_v_subs(&t->point_3, &t->point_2);
	p.v1_node = v_v_subs(&triangle->node, &t->point);
	p.v2_node = v_v_subs(&triangle->node, &t->point_2);
	p.v3_node = v_v_subs(&triangle->node, &t->point_3);
	p.cp_1 = v_v_mult(&p.v1_2, &p.v1_node);
	p.cp_2 = v_v_mult(&p.v2_3, &p.v2_node);
	p.cp_3 = v_v_mult(&p.v3_1, &p.v3_node);
	if (dot_product(&triangle->normal, &p.cp_1) < 0 ||
	dot_product(&triangle->normal, &p.cp_2) < 0 ||
	dot_product(&triangle->normal, &p.cp_3) < 0)
		return (0);
	return (1);
}
