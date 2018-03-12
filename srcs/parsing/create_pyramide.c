/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:40:46 by Etienne           #+#    #+#             */
/*   Updated: 2018/02/12 13:40:48 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object		*triangle_init(t_object *pyramide)
{
	t_object *new;

	new = init_material();
	if (!(new->type = ft_strdup("triangle")))
		exit_rt(1);
	new->point = pyramide->point;
	new->point_2 = pyramide->point_2;
	new->point_3 = pyramide->point_3;
	new->color = pyramide->color;
	add_new_object(&pyramide->sub_object, new);
	new = init_material();
	if (!(new->type = ft_strdup("triangle")))
		exit_rt(1);
	new->point = pyramide->point;
	new->point_2 = pyramide->point_2;
	new->point_3 = pyramide->point_4;
	new->color = pyramide->color;
	add_new_object(&pyramide->sub_object, new);
	return (new);
}

void			create_child_pyramide(t_object *pyramide)
{
	t_object *triangle;

	triangle = triangle_init(pyramide);
	triangle = init_material();
	if (!(triangle->type = ft_strdup("triangle")))
		exit_rt(1);
	triangle->point = pyramide->point;
	triangle->point_2 = pyramide->point_3;
	triangle->point_3 = pyramide->point_4;
	triangle->color = pyramide->color;
	add_new_object(&pyramide->sub_object, triangle);
	triangle = init_material();
	if (!(triangle->type = ft_strdup("triangle")))
		exit_rt(1);
	triangle->point = pyramide->point_2;
	triangle->point_2 = pyramide->point_3;
	triangle->point_3 = pyramide->point_4;
	triangle->color = pyramide->color;
	add_new_object(&pyramide->sub_object, triangle);
}

void			pyramide_attribut(t_object *pyramide, t_json *tmp)
{
	if (!(ft_strcmp(tmp->name, "coord_1")) && tmp->member)
		pyramide->point = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "coord_2")) && tmp->member)
		pyramide->point_2 = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "coord_3")) && tmp->member)
		pyramide->point_3 = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "coord_4")) && tmp->member)
		pyramide->point_4 = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
		pyramide->color = parse_color(tmp->member);
	else if (!(ft_strcmp(tmp->name, "material")))
		parse_material(tmp, pyramide);
	else
		ft_printf("{R}WARNING:{E} pyramide as a bad attribut\n");
}

void			create_pyramide(t_env *e, t_json *json)
{
	t_object	*pyramide;
	t_json		*tmp;

	pyramide = init_material();
	if (!(pyramide->type = ft_strdup("pyramide")))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		pyramide_attribut(pyramide, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	create_child_pyramide(pyramide);
	add_new_object(&e->object, pyramide);
}
