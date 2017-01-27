#include "wireframe.h"
//essentially, we create the mesh from the file, and then create and display points (and appropriate edges between them) from the mesh
//when we rotate, we create a copy of the mesh, rotate it, and then create and display points from the copy (original mesh remains constant)

/*
**copies original mesh (**array representation of input file), 
**alters copy based on rotation key events,
**creates and displays updated image
*/
void create_image(t_view v)
{
	t_vec3 **tmp_mesh;
	tmp_mesh = create_mesh_copy(v.mesh, v);

	rot_x(tmp_mesh, v, v.x_angle);
	rot_y(tmp_mesh, v, v.y_angle);
	rot_z(tmp_mesh, v, v.z_angle);

	v.points = ft_create_points(v, tmp_mesh);
	draw_points(v);
}




//handles keyboard input from user
int keyboard_event_function(int keycode, t_view *v)
{
	float angle = M_PI/96;

	switch(keycode) {
		case (87) :
			v->x_angle += angle;
			break;
		case (84) :
			v->x_angle -= angle;
			break;
		case (83) :
			v->y_angle += angle;
			break;
		case (85) :
			v->y_angle -= angle;
			break;
		case (88) :
			v->z_angle += angle;
			break;
		case (86) :
			v->z_angle -= angle;
			break;
		case (53) :
			exit (0);
		case (15) :
			v->x_angle = 0;
			v->y_angle = 0;
			v->z_angle = 0;
	}
	mlx_clear_window(v->mlx, v->win);
	create_image(*v);
	mlx_key_hook(v->win, keyboard_event_function, v);
	return (0);
}




//initializes t_view struct view which holds all variables necessary for image creation and rotation
t_view initialize_view(int rowcount, int columncount, char *line, int fd)
{
	t_view view;

	view.rowcount = rowcount;
	view.columncount = columncount;
	view.size = 1600;
	view.mesh = create_mesh(rowcount, columncount, line, fd, view.size);
	view.mlx = mlx_init();
	view.distance = 100;
	view.win = mlx_new_window(view.mlx, view.size, view.size, "mlx 42");
	view.proportionality = 0.0012;
	view.x_angle = 0;
	view.y_angle = 0;
	view.z_angle = 0;
	view.points = ft_create_points(view, view.mesh);
	return view;
}




//reads from file, initializes t_view struct, displays initial image, calls to key hook management function
int main(int argc, char **argv)
{
	int fd;
	char *line;
	int rowcount;
	int columncount;

	if (argc != 2)
	{
		ft_putstr("usage: ./filename test_map_file\n");
		return 0;
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("file error\n");
		return (-1);
	}
	rowcount = count_rows(fd);
	lseek(fd, 0, SEEK_SET);
	columncount = count_columns(fd);
	lseek(fd, 0, SEEK_SET);

	t_view view = initialize_view(rowcount, columncount, line, fd);
	draw_points(view);
	mlx_hook(view.win, 2, 0, keyboard_event_function, &view);
	mlx_loop(view.mlx);
}
