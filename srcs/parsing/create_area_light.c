/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_area_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:35:23 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/21 15:35:24 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			fill_area_light_infos(t_json *tmp,
				t_object *al_object, t_light *al_light)
{
	if (!(ft_strcmp(tmp->name, "coord_1")) && tmp->member)
	{
		al_object->point = parse_point(tmp->member);
		al_light->point = al_object->point;
	}
	else if (!(ft_strcmp(tmp->name, "coord_2")) && tmp->member)
	{
		al_object->point_2 = parse_point(tmp->member);
		al_light->point_2 = al_object->point_2;
	}
	else if (!(ft_strcmp(tmp->name, "coord_3")) && tmp->member)
	{
		al_object->point_3 = parse_point(tmp->member);
		al_light->point_3 = al_object->point_3;
	}
	else if (!(ft_strcmp(tmp->name, "coord_4")) && tmp->member)
	{
		al_object->point_4 = parse_point(tmp->member);
		al_light->point_4 = al_object->point_4;
	}
	else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
	{
		al_object->color = parse_color(tmp->member);
		al_light->color = al_object->color;
	}
}

void			area_light_norme(t_env *e,
				t_object *al_object, t_light *al_light)
{
	al_object->ambient = 1;
	add_new_light(&e->light, al_light);
	add_new_object(&e->object, al_object);
	init_area_size(al_object, al_light);
}

void			create_area_light(t_env *e, t_json *json)
{
	t_light		*al_light;
	t_object	*al_object;
	t_json		*tmp;

	al_object = NULL;
	if (!((al_light = ft_memalloc(sizeof(t_light))) &&
		(al_light->type = ft_strdup("area_light")) &&
		(al_object = init_material()) &&
		(al_object->type = ft_strdup("area_light"))))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord_1") && ft_strcmp(tmp->name, "coord_2")
			&& ft_strcmp(tmp->name, "coord_3") && ft_strcmp(tmp->name, "color")
			&& ft_strcmp(tmp->name, "coord_4")) && tmp->member)
			fill_area_light_infos(tmp, al_object, al_light);
		else
			ft_printf("{R}WARNING:{E} area_light as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	area_light_norme(e, al_object, al_light);
}
