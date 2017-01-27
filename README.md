## 3d Wireframe

This is a 3d wireframe renderer that allows for rotation in 3d space. Perspective projection is used to add realism. The provided tools for this project were a function to put a pixel on a screen and a key hook function for user input.  
  
![alt text](https://github.com/robertnowell/3d_wireframe/blob/master/images/giphy.gif "42fdf")

## Implementation

This program does the following:  

1. Reads input from a file formatted like the following:
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/42.png" 
alt="fdf" width="300" height="140" border="10"/>

2. Creates the "mesh" (a two dimensional array), each element of which is a three dimensional vector. Each vector represents a point in three dimensional space.  
3. Creates "points" (also a two dimensional array). Each element of the points array is a two dimensional vector, which is a perspective projection of a corresponding three dimensional vector from the mesh. This is where three dimensional space is projected into two dimensional space.  
4. Draws each element of the initial (i.e. prior to any rotation) points array on the screen, and also draws horizontal and vertical lines between the points.  
5. Makes a call to keyboard_event_function(), which allows the user to rotate the wireframe.  
6. In response to each user input, the program copies the "mesh" and alters each vector based on the x, y, and z rotation angles input by the user and then projects these points into the "points" array.
7. Outputs the image to the screen and then calls to the keyboard event function again.

The program operates in an infinite loop until an escape key (ESC) is received.  

### Details and Code

<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/main.png" 
alt="fdf" width="400" height="400" border="10"/>

In lines 91-111 of the main function error checks the file and file descriptor and counts the file's rows and columns, using lseek() to reset the file offset.  
  
Next initialize_view() is called to initialize the struct t_view which is relied upon in this program. t_view looks like this:  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/t_view.png" 
alt="fdf" width="300" height="300" border="10"/>
Show what the library does as concisely as possible, developers should be able to figure out **how** your project solves their problem by looking at the code example. Make sure the API you are showing off is obvious, and that your code is short and concise.

## Motivation

A short description of the motivation behind the creation and maintenance of the project. This should explain **why** the project exists.

## Installation

Provide code examples and explanations of how to get the project.

## Author

Robert Nowell

## Acknowledgement

This project was completed at School 42, Fremont.
