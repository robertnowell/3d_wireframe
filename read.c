#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include "./includes/libft.h"
#include "./includes/lib3d.h"
#include "./includes/mlx.h"

#define WHITE 0x00FFFFFF
#define Y mesh[row][col].y
#define X mesh[row][col].x
#define Z mesh[row][col].z

//essentially, we create the mesh from the file, and then create and display points (and appropriate edges between them) from the mesh
//when we rotate, we create a copy of the mesh, rotate it, and then create and display points from the copy (original mesh remains constant)

//i and j variables
//better name for mesh?
//

//rot_x alters y and z value of each vector in the mesh based on specified rotation angle (mesh values accessed through X, Y, and Z macros for readability)
void rot_x(t_vec3 **mesh, t_view v, float angle)
{
	float y_prime;
	float z_prime;
	int row;
	int col;

	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
		{
			y_prime = Y * cos(angle) - Z * sin(angle);
			z_prime = Z * cos(angle) + Y * sin(angle);
			Y = y_prime;
			Z = z_prime;
		}
	}
}

//rot_y alters x and z value of each vector in the mesh based on specified rotation angle (mesh values accessed through X, Y, and Z macros for readability)
void rot_y(t_vec3 **mesh, t_view v, float angle)
{
	float x_prime;
	float z_prime;
	int row;
	int col;

	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
		{
			x_prime = X * cos(angle) - Z * sin(angle);
			z_prime = Z * cos(angle) + X * sin(angle);
			Z = z_prime;
			X = x_prime;
		}
	}
}

//rot_z alters x and y value of each vector in the mesh based on specified rotation angle (mesh values accessed through X, Y, and Z macros for readability)
void rot_z(t_vec3 **mesh, t_view v, float angle)
{
	float x_prime;
	float y_prime;
	int row;
	int col;

	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
		{
			x_prime = X * cos(angle) - Y * sin(angle);
			y_prime = X * sin(angle) + Y * cos(angle);
			X = x_prime;
			Y = y_prime;
		}
	}
}



















//draw edges draws horizontal and vertical lines between adjacent points
void draw_edges(t_view v)
{
	int row;
	int col;
	t_vec2 **points;

	points = v.points;
	for (row = 0; row < v.rowcount-2; row++)
	{
		for (col = 0; col < v.columncount - 1; col++)
		{
			draw_line_bes(points[row][col], points[row][col+1], v);
			draw_line_bes(points[row][col], points[row+1][col], v);
		}
		draw_line_bes(points[row][col], points[row+1][col], v);
	}
	for (col = 0; col < v.columncount - 1; col++)
		draw_line_bes(points[row][col], points[row][col+1], v);
}

//puts pixels from 2d array of vectors points to output display
void put_points(t_view v)
{
	int row;
	int col;

	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
			mlx_pixel_put(v.mlx, v.win, v.points[row][col].x, v.points[row][col].y, WHITE);
	}
	draw_edges(v);
}

//creates 2d array of 2d vectors called points which holds the two-d representation of three-d mesh.
t_vec2 **ft_create_points(t_view v, t_vec3 **mesh)
{
	t_vec2 **points;
	int row;
	int col;

	points = (t_vec2**)malloc(sizeof(t_vec2 *) * v.rowcount);
	row = 0;
	for (row = 0; row < v.rowcount; row++)
		points[row] = (t_vec2 *)malloc(sizeof(t_vec2) * v.columncount);
	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
			points[row][col] = vec2(X + v.size/2 + v.proportionality*X*Z, Y + v.size/2 + v.proportionality*Y*Z);
	}
	return points;
}

//counts number of rows (lines) in the input file
int count_rows(int fd)
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
		for (i = 0; buf[i]; i++)
		{
			if (buf[i] == '\n')
				count++;
		}
	}
	return (count);
}

//counts number of columns in the input file
int count_columns(int fd)
{
	int ret;
	char buf;
	char line[1000];
	int count = 0;
	int i;

	if (!fd)
		return 0;
	while ((ret = read(fd, &buf, 1)))
	{
		if (buf == '\n')
			break;
		line[i] = buf;
		i++;
	}
	for (i = 0; line[i]; i++)
	{
		if (line[i] > ' ' && line[i - 1] <= ' ')
			count++;		
	}
	return (count);
}

//copies 2d array of 3d vectors called mesh
t_vec3 **copy_mesh(t_vec3 **mesh, t_view v)
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

//copies original mesh, alters the copy based on rotation key events, and then creates and outputs the image to the screen
void create_image(t_view v)
{
	t_vec3 **tmp_mesh;
	tmp_mesh = copy_mesh(v.mesh, v);

	rot_x(tmp_mesh, v, v.x_angle);
	rot_y(tmp_mesh, v, v.y_angle);
	rot_z(tmp_mesh, v, v.z_angle);

	v.points = ft_create_points(v, tmp_mesh);
	put_points(v);
}

//this function handles keyboard input from user
int keyboard_event_function(int keycode, t_view *v)
{
	float angle = M_PI/96;

	if (keycode == 87)
		v->x_angle += angle;
	else if (keycode == 84)
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
	create_image(*v);
	mlx_key_hook(v->win, keyboard_event_function, v);
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
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("file error\n");
		return (-1);
	}
	int rowcount = count_rows(fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);

	char *line;
	int i = 0;
	int j = 0;
	int linei = 0;
	int columncount;

	columncount = count_columns(fd);
	printf("rowcount=%d\n", rowcount);
	printf("columncount: %d\n", columncount);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	t_view view;

	view.rowcount = rowcount;
	view.columncount = columncount;
	view.size = 1600;
	int mod = view.size/(columncount+rowcount);

	t_vec3 **mesh;
	mesh = (t_vec3 **)malloc(sizeof(t_vec3*) * rowcount + 1);
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

	put_points(view);
	mlx_hook(view.win, 2, 0, keyboard_event_function, &view);
	mlx_loop(view.mlx);
}
