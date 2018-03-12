/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/02/17 17:19:35 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_new_member(t_json **list, t_json *new_member)
{
	t_json	*tmp;

	if (!(*list)->name)
	{
		free((*list));
		(*list) = new_member;
		return ;
	}
	tmp = (*list);
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new_member;
	(*list) = tmp;
}

int		create_object(t_json *object, char *str, int i)
{
	t_json *member;

	object->member = new_object();
	while (str[++i] && str[i] != '}')
	{
		if (str[i] == '"')
		{
			member = new_object();
			i += get_content(&member->name, str, i) + 1;
			char_is_valid(str[i], ':');
			while (str[i] && !(str[i] == '"' || str[i] == '{'))
				i++;
			if (str[i] == '{')
				i = create_object(member, str, i);
			else
				i += get_content(&member->content, str, i);
			add_new_member(&object->member, member);
		}
	}
	char_is_valid(str[i], '}');
	return (i);
}

void	create_tree(t_env *e, char **str)
{
	t_json	*json;

	if ((*str)[0] == '{')
	{
		json = new_object();
		create_object(json, (*str), 0);
		if (!json->member->name)
		{
			ft_putendl("This file does not describe a scene");
			ft_kill("Please check the .rt format in \"README.txt\".");
		}
		get_object(e, json);
		free(json);
	}
	else
		exit_parser(1);
}

char	*ft_strjoin_free(char **s1, char **s2)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strnew(ft_strlen(*s1) + ft_strlen(*s2));
	i = 0;
	j = 0;
	while ((*s1) && (*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	if ((*s1))
		ft_memdel((void **)s1);
	while ((*s2) && (*s2)[j])
	{
		str[i] = (*s2)[j];
		j++;
		i++;
	}
	if ((*s2))
		ft_memdel((void **)s2);
	return (str);
}

int		parsing(t_env *e, char *src_file)
{
	t_parsing	p;

	if (open_close(src_file, e))
		return (0);
	if ((p.fd = open(src_file, O_RDONLY)) < 0)
		return (0);
	ft_putstr("Wait for parsing...\n");
	while (get_next_line(p.fd, &p.buff) == 1)
	{
		p.tmp = e->stock;
		e->stock = ft_strjoin_free(&p.tmp, &p.buff);
		ft_strdel(&p.tmp);
	}
	close(p.fd);
	return (1);
}
