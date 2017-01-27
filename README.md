## 3d Wireframe

This is a 3d wireframe renderer that allows for rotation in 3d space. Perspective projection is used to add realism. The provided tools for this project were a function to put a pixel on a screen and a key hook function for user input.  
  
![alt text](https://github.com/robertnowell/3d_wireframe/blob/master/images/giphy.gif "42fdf")

## Implementation

This program does the following:  

1. Read input from a particularly formatted file, like the following:  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/42.png" 
alt="fdf" width="300" height="140" border="10" /></a>

2. Create a two dimensional "mesh" (it's an array), each element of which is a three dimensional vector. Each vector represents a point in three dimensional space.  
3. Create a two dimensional "points" array which is a perspective projection of the three dimensional mesh. Each element of the points array is a two dimensional vector.  
4. Draw the initial (i.e. prior to any rotation) points array on the screen.  
5. Make a call to keyboard_event_function(), which allows the user to rotate the wireframe.  
6. In response to each user input, copy the "mesh" and alter each vector based on the x, y, and z rotation angles which the user input.
7. Recreate the points array, output the image to the screen and then call to the keyboard event function again.

Show what the library does as concisely as possible, developers should be able to figure out **how** your project solves their problem by looking at the code example. Make sure the API you are showing off is obvious, and that your code is short and concise.

## Motivation

A short description of the motivation behind the creation and maintenance of the project. This should explain **why** the project exists.

## Installation

Provide code examples and explanations of how to get the project.

## Author

Robert Nowell

## Acknowledgement

This project was completed at School 42, Fremont.
