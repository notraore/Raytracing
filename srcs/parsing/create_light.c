/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:01:18 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/28 12:01:20 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			add_new_light(t_light **list, t_light *new_light)
{
	t_light	*tmp;

	if (!(*list))
	{
		(*list) = new_light;
		return ;
	}
	tmp = (*list);
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new_light;
	(*list) = tmp;
}

void			create_light(t_env *e, t_json *json)
{
	t_light		*light;
	t_json		*tmp;

	if (!(light = ft_memalloc(sizeof(t_light))))
		exit_rt(1);
	if (!(light->type = ft_strdup("light")))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			light->origin = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			light->color = parse_color(tmp->member);
		else
			ft_printf("light %d as a bad attribut\n", light->id);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	add_new_light(&e->light, light);
}
