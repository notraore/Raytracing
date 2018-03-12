/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:45:22 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 17:19:49 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_complex(t_env *e, t_json *json)
{
	if (!(ft_strcmp(json->name, "quad")) && json->member)
		create_quad(e, json);
	else if (!(ft_strcmp(json->name, "glass")) && json->member)
		create_glass(e, json);
	else if (!(ft_strcmp(json->name, "cube")) && json->member)
		create_cube(e, json);
	else if (!(ft_strcmp(json->name, "area_light")) && json->member)
		create_area_light(e, json);
	else if (!(ft_strcmp(json->name, "pyramide")) && json->member)
		create_pyramide(e, json);
	else if (!(ft_strcmp(json->name, "paraboloid")) && json->member)
		create_paraboloid(e, json);
	else
		parse_scene(e, json);
}

void	get_object_condition(t_env *e, t_json *tmp)
{
	if (!(ft_strcmp(tmp->name, "triangle")) && tmp->member)
		create_triangle(e, tmp);
	else if (!(ft_strcmp(tmp->name, "cylinder")) && tmp->member)
		create_cylinder(e, tmp);
	else if (!(ft_strcmp(tmp->name, "cone")) && tmp->member)
		create_cone(e, tmp);
	else if (!(ft_strcmp(tmp->name, "light")) && tmp->member)
		create_light(e, tmp);
	else if (!(ft_strcmp(tmp->name, "disk")) && tmp->member)
		create_disk(e, tmp);
	else
		get_complex(e, tmp);
}

void	get_object(t_env *e, t_json *json)
{
	t_json	*tmp;

	while (json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "sphere")) && tmp->member)
			create_sphere(e, tmp);
		else if (!(ft_strcmp(tmp->name, "plane")) && tmp->member)
			create_plane(e, tmp);
		else
			get_object_condition(e, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
}
