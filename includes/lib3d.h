#ifndef LIB3D_H
# define LIB3D_H

# include <math.h>

/*
** t_vec2 is a 2d vector with a float x value 
** and a float y value
*/

typedef	struct
{
	float	x;
	float	y;
}			t_vec2;

t_vec2		vec2(float x, float y);
t_vec2		vec2_rotate(t_vec2 v, float a);

/*
**	Macro versions of simple operations for vec2.
*/

# define VEC2_ADD(l, r) (vec2_init(l.x + r.x, l.y + r.y))
# define VEC2_SUB(l, r) (vec2_init(l.x - r.x, l.y - r.y))
# define VEC2_MULT(l, r) (vec2_init(l.x * r.x, l.y * r.y))
# define VEC2_DIV(l, r) (vec2_init(l.x / r.x, l.y / r.y))
# define VEC2_DOT(l, r) (l.x * r.x + l.y * r.y)
# define VEC2_SCALE(v, s) (vec2_init(v.x * s, v.y * s))
# define VEC2_LENGTH(v) (sqrtf(v.x * v.x + v.y * v.y))
# define VEC2_NORMALIZE(v) (VEC2_SCALE(v, 1 / VEC2_LENGTH(v)))


/*
** t_vec3 is a 3d vector with float x, y, and z values
*/

typedef struct
{
	float x;
	float y;
	float z;
}		t_vec3;

t_vec3		vec3(float x, float y, float z);
t_vec2		vec3f_perspective_proj(t_vec3 v, float focal_dist);
t_vec3		vec3f_cross(t_vec3 l, t_vec3 r);

# define VEC3F_ADD(l, r) (vec3f_init(l.x + r.x, l.y + r.y, l.z + r.z))
# define VEC3F_SUB(l, r) (vec3f_init(l.x - r.x, l.y - r.y, l.z - r.z))
# define VEC3F_MULT(l, r) (vec3f_init(l.x * r.x, l.y * r.y, l.z * r.z))
# define VEC3F_DIV(l, r) (vec3f_init(l.x / r.x, l.y / r.y, l.z / r.z))
# define VEC3F_DOT(l, r) (l.x * r.x + l.y * r.y + l.z *r.z)
# define VEC3F_SCALE(v, s) (vec3f_init(v.x * s, v.y * s, v.z * s))
# define VEC3F_LENGTH(v) (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z))
# define VEC3F_NORMALIZE(v) (VEC3F_SCALE(v, 1 / VEC3F_LENGTH(v)))


typedef struct	s_view
{
	void *mlx;
	void *win;
	int rowcount;
	int columncount;
	int		distance;
	int size;
	float proportionality;
	t_vec3 **mesh;
	t_vec2 **points;
	float x_angle;
	float y_angle;
	float z_angle;
}				t_view;

void draw_line_bes(t_vec2 vec1, t_vec2 vec2, t_view v);
int ft_abs(int a);


#endif
