/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:38:32 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/01/11 15:38:35 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include "../libft/libft.h"
# include "rt.h"

typedef struct s_color		t_color;
typedef struct s_getcolor	t_getcolor;

struct					s_color
{
	double	b;
	double	g;
	double	r;
};

t_color					set_color(double b, double g, double r);
t_color					c_c_mult(t_color *a, t_color *b);
t_color					c_c_add(t_color *a, t_color *b);
t_color					c_c_subs(t_color *a, t_color *b);
t_color					c_double_add(t_color *a, double b);
t_color					c_double_pow(t_color *a, double b);
t_color					c_double_mult(t_color *a, double b);
t_color					c_double_div(t_color *a, double b);
t_color					c_c_subs(t_color *a, t_color *b);
t_color					normalize_color(t_color *color);

#endif
