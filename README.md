## 3d Wireframe

This is a 3d wireframe renderer that allows for rotation in 3d space. Perspective projection is used to add realism. The provided tools for this project were a function to put a pixel on a screen and a key hook function for user input.  
  
![alt text](https://github.com/robertnowell/3d_wireframe/blob/master/images/giphy.gif "42fdf")

## Implementation

This program does the following:  

1. Reads input from a file formatted like the following:  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/42.png" 
alt="fdf" width="300" height="140" border="10"/>

2. Creates the "mesh" (a two dimensional array), each element of which is a three dimensional vector. Each vector represents a point in three dimensional space.
3. Creates the "points" (also a two dimensional array). Each element of the points array is a two dimensional vector, which is a perspective projection of a corresponding three dimensional vector from the mesh. This is where three dimensional space is projected into two dimensional space.  
4. Draws each element of the initial (i.e. prior to any rotation) points array on the screen, and also draws horizontal and vertical lines between the points.  
5. Makes a call to keyboard_event_function(), which allows the user to rotate the wireframe.  
6. In response to each user input, the program copies the "mesh" and alters each vector based on the x, y, and z rotation angles input by the user and then projects these points into the "points" array.
7. Outputs the image to the screen and then calls to the keyboard event function again.

The program operates in an infinite loop until an escape key (ESC) is received.  

### Details and Code

<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/main2.png" 
alt="main" width="400" height="400" border="10"/>

In lines 91-111 of the main function error checks the file and file descriptor and counts the file's rows and columns, using lseek() to reset the file offset.  
  
Next initialize_view() is called to initialize the struct t_view which is relied upon in this program. t_view is defined in includes/wireframe.h and looks like this:  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/t_view.png" 
alt="t_view" width="300" height="300" border="10"/>  
mlx and win are variables which allow for the presentation of visual output to the user. Proportionality is the degree of perspective projection applied (its default value is somewhat arbitrary). x_angle, y_angle, and z_angle store the value of the rotation (in radians) for each axis and are initialized to zero in initialize_view() in main.c:  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/initialize_view.png" 
alt="initialize_view" width="550" height="300" border="10"/>  
Mesh and points are created here, making calls to functions in create.c. SIZE is the size of the window created and is a macro defined in wireframe.h. It can be changed there and is set to 1000 by default.  
Once t_view is initialized, the main function makes a call to draw_points(), which exists in draw.c, and finally the main function calls keyboard_event_function via mlx_hook. mlx_hook was a provided function for this project, as was mlx_loop.   
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/keyboard_event_function.png" 
alt="keyboard_event_function" width="350" height="450" border="10"/>  
In keyboard_event()

## Installation

Provide code examples and explanations of how to get the project.

## Author

Robert Nowell

## Acknowledgement

This project was completed at School 42, Fremont.
