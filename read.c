#include "./includes/mlx.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "./includes/libft.h"
#include "./includes/lib3d.h"
#define WHITE 0x00FFFFFF
#include <sys/types.h>

#include <fcntl.h>

// typedef struct	s_view
// {
// 	void *mlx;
// 	void *win;
// 	int rowcount;
// 	int columncount;
// 	int		distance;
// 	int size;
// 	float proportionality;
// 	t_vec3 **mesh;
// 	t_vec2 **points;
// 	float x_angle;
// 	float y_angle;
// 	float z_angle;
// }				t_view;

void rot_x(t_vec3 ***mesh, t_view v, float angle)
{
	int i;
	int j;
	float y_prime;
	float z_prime;

	j = 0;
	i = 0;

	while (i < v.rowcount - 1)
	{
		j = 0;
		while (j <= v.columncount - 1)
		{
			y_prime = (*mesh)[i][j].y * cos(angle) \
			- (*mesh)[i][j].z * sin(angle);
			z_prime = (*mesh)[i][j].z * cos(angle) \
			+ (*mesh)[i][j].y * sin(angle);
			(*mesh)[i][j].y = y_prime;
			(*mesh)[i][j].z = z_prime;
			j++;
		}
		i++;
	}
}

void rot_y(t_vec3 ***mesh, t_view v, float angle)
{
	int i;
	int j;
	float x_prime;
	float z_prime;

	i = 0;
	j = 0;

	while (i < v.rowcount - 1)
	{
		j = 0;
		while (j <= v.columncount - 1)
		{
			x_prime = (*mesh)[i][j].x * cos(angle) \
			- (*mesh)[i][j].z * sin(angle);
			z_prime = (*mesh)[i][j].z * cos(angle) \
			+ (*mesh)[i][j].x * sin(angle);

			(*mesh)[i][j].z = z_prime;
			(*mesh)[i][j].x = x_prime;
			j++;

		}
		i++;
	}
}

void rot_z(t_vec3 ***mesh, t_view v, float angle)
{
	int i;
	int j;
	float x_prime;
	float y_prime;

	i = 0;
	j = 0;
	
	while (i < v.rowcount - 1)
	{
		j = 0;
		while (j <= v.columncount - 1)
		{
			x_prime = (*mesh)[i][j].x * cos(angle) \
			- (*mesh)[i][j].y * sin(angle);
			y_prime = (*mesh)[i][j].x * sin(angle) \
			+ (*mesh)[i][j].y * cos(angle);
			(*mesh)[i][j].x = x_prime;
			(*mesh)[i][j].y = y_prime;
			j++;

		}
		i++;
	}
}

void ft_draw_edges(t_view v)
{
	int i;
	int j;
	t_vec2 **points;

	points = v.points;
	i = 0;
	while (i < v.rowcount-2)
	{
		j = 0;
		while (j < v.columncount - 1)
		{
			draw_line_bes(points[i][j], points[i][j+1], v);
			draw_line_bes(points[i][j], points[i+1][j], v);
			j++;
		}
		draw_line_bes(points[i][j], points[i+1][j], v);
		i++;
	}
	j = 0; 
	while (j < v.columncount - 1)
	{
		draw_line_bes(points[i][j], points[i][j+1], v);
		j++;
	}	
}

void ft_put_points(t_view v)
{
	int i;
	int j;

	i = 0;
	while (i < v.rowcount - 1)
	{
		j = 0;
		while (j <= v.columncount - 1)
		{
			mlx_pixel_put(v.mlx, v.win, \
				v.points[i][j].x, v.points[i][j].y, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	ft_draw_edges(v);
}

t_vec2 **ft_create_points(t_view v, t_vec3 **mesh)
{
	t_vec2 **points;
	int i;
	int j;

	points = (t_vec2**)malloc(sizeof(t_vec2 *) * v.rowcount);
	i = 0;
	while (i < v.rowcount)
	{
		points[i] = (t_vec2 *)malloc(sizeof(t_vec2) * v.columncount);
		i++;
	}
	i = 0;
	while (i < v.rowcount - 1)
	{
		j = 0;
		while (j <= v.columncount - 1)
		{
			points[i][j] = vec2(mesh[i][j].x + v.size/2 + \
		v.proportionality*mesh[i][j].x*mesh[i][j].z, \
		mesh[i][j].y + v.size/2 + v.proportionality*mesh[i][j].y*mesh[i][j].z);
			j++;
		}
		i++;
	}
	return points;
}

int ft_linecount(int fd)
{
	int ret;
	char *buf;
	int count = 0;
	int i;

	if ((ret = read(fd, buf, 1) > 0))
	{
		count++;
		if (*buf == '\n')
			count++;
	}
	while ((ret = read(fd, buf, 1)))
	{
		i = 0;
		while (buf[i])
		{
			if (buf[i] == '\n')
				count++;
			i++;
		}
	}
	return (count);
}

int ft_columncount(int fd)
{
	int i;
	int count;
	char line[1000];
	char buf;
	int ret;

	count = 0;
	i = 0;
	if (!fd)
		return 0;
	while ((ret = read(fd, &buf, 1)))
	{
		if (buf == '\n')
			break;
		line[i] = buf;
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] > ' ' && line[i - 1] <= ' ')
			count++;		
		i++;
	}
	return (count);
}

void print_vec3(t_vec3 v)
{
	ft_putstr("( ");
	ft_putnbr(v.x);
	ft_putstr(", ");
	ft_putnbr(v.y);
	ft_putstr(", ");
	ft_putnbr(v.z);
	ft_putstr(" )");
}

t_vec3 **ft_copy_mesh(t_vec3 **mesh, t_view v)
{
	int i = 0;
	int j;
	t_vec3 **tmp_mesh;

	tmp_mesh = (t_vec3 **)malloc(sizeof(t_vec3*) * v.rowcount + 1);
	while (i < v.rowcount)
	{
		tmp_mesh[i] = (t_vec3*)malloc(sizeof(t_vec3) * v.columncount + 1);
		i++;
	}
	i = 0;
	while ((i < v.rowcount - 1))
	{
		j = 0;
		while (j < v.columncount)
		{
			tmp_mesh[i][j] = mesh[i][j];
			j++;
		}
		i++;
	}
	return tmp_mesh;
}

void ft_create_image(t_view v)
{
	t_vec3 **tmp_mesh;
	tmp_mesh = ft_copy_mesh(v.mesh, v);

	rot_x(&tmp_mesh, v, v.x_angle);
	rot_y(&tmp_mesh, v, v.y_angle);
	rot_z(&tmp_mesh, v, v.z_angle);

	v.points = ft_create_points(v, tmp_mesh);
	ft_put_points(v);
}

int persp_key_function(int keycode, t_view *v)
{
	float angle = M_PI/96;

	v->x_angle = keycode == 87 ? v->x_angle + angle : v->x_angle;
	if (keycode == 84)
		v->x_angle -= angle;
	else if (keycode == 83)
		v->y_angle += angle;
	else if (keycode == 85)
		v->y_angle -= angle;
	else if (keycode == 88)
		v->z_angle += angle;
	else if (keycode == 86)
		v->z_angle -= angle;
	else if (keycode == 53)
		exit (0);
	else if (keycode == 15)
	{
		v->x_angle = 0;
		v->y_angle = 0;
		v->z_angle = 0;
	}
	mlx_clear_window(v->mlx, v->win);
	ft_create_image(*v);
	mlx_key_hook(v->win, persp_key_function, v);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: ./filename test_map_file\n");
		return 0;
	}
	int fd;
	// ft_putnbr(fd);
	// ft_putendl("=fd");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("file error\n");
		return (-1);
	}
	int rowcount = ft_linecount(fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);

	char *line;
	int i = 0;
	int j = 0;
	int linei = 0;
	int columncount;

	columncount = ft_columncount(fd);
	printf("rowcount=%d\n", rowcount);
	printf("columncount: %d\n", columncount);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	t_view view;
	t_vec3 **mesh;
	mesh = (t_vec3 **)malloc(sizeof(t_vec3*) * rowcount + 1);
	view.rowcount = rowcount;
	view.columncount = columncount;
	view.size = 1600;
	int mod = view.size/(columncount+rowcount);

	while ((i < rowcount - 1))
	{
		if (!line)
			get_next_line(fd, &line);
		linei = 0;
		mesh[i] = (t_vec3*)malloc(sizeof(t_vec3) * columncount + 1);
		j = 0;
		while (j < columncount)
		{
			mesh[i][j] = vec3(mod*(j-columncount/2), mod*(i-rowcount/2), mod/5*ft_atoi(&line[linei]));
			j++;
			while (line[linei] > ' ')
				linei++;
			while (line[linei] == ' ')
				linei++;
		}
		i++;
		line = NULL;
	}
	view.mesh = mesh;
	view.mlx = mlx_init();
	view.distance = 100;
	view.win = mlx_new_window(view.mlx, view.size, view.size, "mlx 42");
	view.proportionality = 0.0015;
	view.x_angle = 0;
	view.y_angle = 0;
	view.z_angle = 0;
	view.points = ft_create_points(view, view.mesh);

	ft_put_points(view);
	mlx_hook(view.win, 2, 0, persp_key_function, &view);
	// mlx_key_hook(view.win, persp_key_function, &view);
	mlx_loop(view.mlx);
}
