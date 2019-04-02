#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/freeglut.h> // Req. libglut3-dev or freeglut3-dev
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <string>
#include <climits>
#include <chrono>
#include <thread>

#include "point.h"
#include "path.h"
#include "adn.h"
#include "population.h"

// Global variables for easy parameter's set
const int POPULATION_SIZE = 300;
const int POOL_SIZE = 300;
const float MUTATION_RATE = 0.05;
const bool ELITISM = true;
const int NUM_ELLIT = 5;
const int MAX_ITER = INT_MAX-100;

const std::vector<Point> circumference_points(int k){
    int i = k;
    std::vector<Point> vec_points;
    
    while(i > 0){
	Point A = Point(std::cos(2*3.1416*i/k), -std::sin(2*3.1416*i/k));
	vec_points.push_back(A);
	i--;
    }
    return vec_points;
}

std::random_device r_device2;
std::mt19937 gen2(r_device2());
float random_float_in(float a, float b){
    std::uniform_real_distribution<> dist_real(a, b);
    return dist_real(gen2);
}

const std::vector<Point> random_points(int k){
    std::vector<Point> vec_points;
    
    for(int i = 0; i < k; i++){
	float x = random_float_in(-1, 1);
	float y = random_float_in(-1, 1);	
	vec_points.push_back(Point(x, y));
    }
    return vec_points;
}

// Vector to store the path to print
std::vector<Point> to_draw;

// Set circumference points
const std::vector<Point> destinations = circumference_points(50);
// Set random points
// const std::vector<Point> destinations = random_points(1000);


// Initialize Random Population
Population pop = Population(POPULATION_SIZE, destinations);

// Some printing stuff----------------------------------
void initGL() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void idle() {
    glutPostRedisplay();
}
// -----------------------------------------------------


void display() {
    if(pop.generation_number < MAX_ITER){
	pop.next_generation();
//	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    to_draw = pop.get_best().get_rep().get_rep();

    // More printing stuff---------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);
    
    // Print vector of points------------------------------------------------------------------------------
    // This draws the lines behind points
    for(auto&& elem : to_draw){
    	glVertex2f(elem.x/1.75-0.5, elem.y/1.75);
    }
    // Draws line behind last and first point to close the graph
    glVertex2f(to_draw.back().x/1.75-0.5, to_draw.back().y/1.75);
    glVertex2f(to_draw.front().x/1.75-0.5, to_draw.front().y/1.75);    
    
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    // ----------------------------------------------------------------------------------------------------

    
    //--------------------------- Text Management ---------------------------------------------------------
    char _init_size[32];
    snprintf(_init_size, sizeof(_init_size)-1, "Initial size: %d \n", POPULATION_SIZE);

    glRasterPos2f(0.4f, 0.4f);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *)_init_size);

    char _pool_size[32];
    snprintf(_pool_size, sizeof(_pool_size)-1, "Pool size: %d \n", POOL_SIZE);

    glRasterPos2f(0.4f, 0.3f);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *)_pool_size);

    char _mutation_rate[32];
    snprintf(_mutation_rate, sizeof(_mutation_rate)-1, "Mutation rate: %.2f \n", MUTATION_RATE);

    glRasterPos2f(0.4f, 0.2f);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *)_mutation_rate);

    char _elitism[32];
    if(ELITISM){
	snprintf(_elitism, sizeof(_elitism)-1, "Elitism: TRUE \n");
    }
    else{
	snprintf(_elitism, sizeof(_elitism)-1, "Elitism: FALSE \n");
    }

    glRasterPos2f(0.4f, 0.1f);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *)_elitism);

    char _num_elit[32];
    snprintf(_num_elit, sizeof(_num_elit)-1, "Num. elitist: %d \n ", (ELITISM)?NUM_ELLIT:0);

    glRasterPos2f(0.4f, 0.0f);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *)_num_elit);

    char _fitness[32];
    snprintf(_fitness, sizeof(_fitness)-1, "Fitness(distance): %.3f \n ", pop.get_best().fitness);
    glColor3f(0.0f, 0.7f, 1.0f);
    glRasterPos2f(0.4f, -0.1f);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *)_fitness);
    glColor3f(1.0f, 1.0f, 1.0f);
    char _gen_number[32];
    snprintf(_gen_number, sizeof(_gen_number)-1, "Gen. num: %d / %d \n ", pop.generation_number, MAX_ITER);

    glRasterPos2f(0.4f, -0.2f);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *)_gen_number);
    //-----------------------------------------------------------------------------------------------------    

    
    // Print vector of points------------------------------------------------------------------------------
    // This draws the points in other color
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,1,1);
    glPointSize(5);
    glBegin(GL_POINTS);
    
    for(auto&& elem : to_draw){
	glVertex2f(elem.x/1.75-0.5, elem.y/1.75);
    }
    
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height){
    
    if (height == 0){
	height = 1;
    }
    
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (width >= height){
	gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    
    else{
	gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }    
}

int main(int argc, char** argv){
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    
    // Set the window's initial width & height
    glutInitWindowSize(800, 640);
    
    glutInitWindowPosition(50, 50); 
    glutCreateWindow("Travelling Salesman");
//    glutFullScreen();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    initGL();
    
    // Inifinite loop to draw, also used for the main algorithm loop 
    glutMainLoop();
    
    return 0;
}
