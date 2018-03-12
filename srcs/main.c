/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/23 18:52:24 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		default_env(t_env *e)
{
	e->width = WIN_X;
	e->height = WIN_Y;
	e->distance = (WIN_X + WIN_Y) / 2;
	e->pixelize = 0;
	e->is_delete = 0;
	e->is_copy = 0;
	e->camera.origin = set_vector(0, 0, -e->distance);
	e->lookat = set_vector(0, 0, 0);
	e->indice = R_VOID;
	e->perlin.a = 0.01;
	e->perlin.b = 0.02;
	e->perlin.c = 0.05;
	e->perlin.d = 0.5;
	e->strechx = 1;
	e->strechy = 1;
	e->recursion = 3;
	e->strechx = 10;
}

void		init_permtab(t_env *e)
{
	static int	permtab[256] = {151, 160, 137, 91, 90, 15, 131, 13, 201, 95,
	96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240,
	21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252,
	219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20,
	125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77,
	146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41,
	55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73,
	209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159,
	86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
	5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16,
	58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
	154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19,
	98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
	251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145,
	235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84,
	204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222,
	114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180};

	ft_memcpy((void*)e->p, (void*)permtab, 1024);
	ft_memcpy((void*)&e->p[256], (void*)permtab, 1024);
}

void		load_text_loading(t_env *e)
{
	if (!((e->img_bat = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/battery.xpm", &(e->mlx.l_size), &e->mlx.endian))))
		ft_kill("Texture error");
	if (!((e->barre_bat = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/bar.xpm", &(e->mlx.l_size), &e->mlx.endian))))
		ft_kill("Texture error");
	if (!((e->sonic_u = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/sonic_fu.xpm", &(e->mlx.l_size), &e->mlx.endian))))
		ft_kill("Texture error");
	if (!((e->sonic_d = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/sonic_fd.xpm", &(e->mlx.l_size), &e->mlx.endian))))
		ft_kill("Texture error");
}

void		display_window(t_env *e)
{
	e->mlx.mlx_ptr = mlx_init();
	e->mlx.win_ptr = mlx_new_window(e->mlx.mlx_ptr, e->width, e->height, "RT");
	e->mlx.img_ptr = mlx_new_image(e->mlx.mlx_ptr, e->width, e->height);
	e->mlx.data = (unsigned char*)mlx_get_data_addr(e->mlx.img_ptr,
		&e->mlx.bpp, &e->mlx.l_size, &e->mlx.endian);
	load_text_loading(e);
	load_texture(e);
	if (!e->object)
	{
		ft_printf("Scene can't be empty.\n");
		return ;
	}
	check_load(e);
	init_camera(e);
	camera_transformation(e);
	init_stereo(e);
	ft_putstr("Parsing done!\nWait for render...\n");
	ft_pthread(e, ray_tracer_void);
	ft_putstr("Render done!\n");
	mlx_hook(e->mlx.win_ptr, 2, (1L << 0), key_functions, e);
	mlx_hook(e->mlx.win_ptr, 17, (1L << 17), proper_exit, e);
	mlx_mouse_hook(e->mlx.win_ptr, mouse, e);
	mlx_loop(e->mlx.mlx_ptr);
	mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
}

int			main(int argc, char **argv)
{
	t_env	*e;

	if (!(e = (t_env*)ft_memalloc(sizeof(t_env))))
		exit_rt(1);
	init_permtab(e);
	default_env(e);
	if (argc != 2)
		ft_print_err(argc);
	if (parsing(e, argv[1]) && e->stock)
	{
		create_tree(e, &e->stock);
		ft_strdel(&e->stock);
		display_window(e);
	}
	return (0);
}
